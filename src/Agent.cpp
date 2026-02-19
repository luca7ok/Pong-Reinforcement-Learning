#include "Agent.h"

#include <ATen/ops/mse_loss.h>
#include <torch/optim/adam.h>
#include <torch/types.h>

#include <random>

#include "RL_Structs.h"

Agent::Agent(int inputSize, int hiddenSize, int outputSize, int capacity, int _batchSize,
             float learningRate, float _gamma, float _epsilon, float _epsilonDecay,
             float _epsilonMin, int _targetUpdateFreq)
    : policyNetwork{inputSize, hiddenSize, outputSize},
      targetNetwork{inputSize, hiddenSize, outputSize},
      memory{capacity},
      optimizer{policyNetwork.parameters(), torch::optim::AdamOptions(learningRate)},
      batchSize(_batchSize),
      gamma(_gamma),
      epsilon(_epsilon),
      epsilonDecay(_epsilonDecay),
      epsilonMin(_epsilonMin),
      learnStepCounter(0),
      targetUpdateFreq(_targetUpdateFreq) {
    updateTargetNetwork();
}

int Agent::selectAction(const RL::StackedState& gameState) {
    static std::random_device randomDevice;
    static std::mt19937 rng(randomDevice());
    std::uniform_real_distribution<> distribution(0.0, 1.0);

    if (distribution(rng) < epsilon) {
        std::uniform_int_distribution<> actionDistribution(0, 2);
        return actionDistribution(rng);
    }
    return policyNetwork.predictAction(gameState);
}

void Agent::storeExperience(const RL::Experience& experience) {
    memory.push(experience);
}

void Agent::updateTargetNetwork() {
    auto policyParameters = policyNetwork.named_parameters();
    auto targetParameters = targetNetwork.named_parameters();

    for (auto& val : policyParameters) {
        auto name = val.key();
        auto* targetParameter = targetParameters.find(name);
        if (targetParameter != nullptr) {
            targetParameter->set_data(val.value().clone());
        }
    }
}

void Agent::decayEpsilon() {
    if (epsilon > epsilonMin) {
        epsilon *= epsilonDecay;
    }
}

void Agent::learn() {
    if (memory.getSize() < batchSize) {
        return;
    }

    std::vector<RL::Experience> batch = memory.sample(batchSize);
    std::vector<float> stateVec, nextStateVec, rewardVec, doneVec;
    std::vector<int> actionVec;

    for (const auto& experience : batch) {
        for (const auto& state : experience.state) {
            stateVec.insert(stateVec.end(), {state.ballX, state.ballY, state.ballVelocity.x,
                                             state.ballVelocity.y, state.paddleY, state.enemyY});
        }

        for (const auto& nextState : experience.nextState) {
            nextStateVec.insert(nextStateVec.end(),
                                {nextState.ballX, nextState.ballY, nextState.ballVelocity.x,
                                 nextState.ballVelocity.y, nextState.paddleY, nextState.enemyY});
        }

        actionVec.push_back(experience.action);
        rewardVec.push_back(experience.reward);
        doneVec.push_back(experience.done ? 0.f : 1.f);
    }

    auto states = torch::tensor(stateVec).view({batchSize, 24});
    auto nextStates = torch::tensor(nextStateVec).view({batchSize, 24});
    auto actions = torch::tensor(actionVec, torch::kInt64).view({batchSize, 1});
    auto rewards = torch::tensor(rewardVec).view({batchSize, 1});
    auto masks = torch::tensor(doneVec).view({batchSize, 1});

    auto qValues = policyNetwork.forward(states).gather(1, actions);
    auto maxResult = targetNetwork.forward(nextStates).max(1);
    auto nextQValues = std::get<0>(maxResult).unsqueeze(1).detach();
    auto expectedQValues = rewards + gamma * nextQValues * masks;

    auto loss = torch::mse_loss(qValues, expectedQValues);
    optimizer.zero_grad();
    loss.backward();
    optimizer.step();

    learnStepCounter++;
    if (learnStepCounter % targetUpdateFreq == 0) {
        updateTargetNetwork();
    }
}

float Agent::getEpsilon() const {
    return epsilon;
}

void Agent::setEpsilon(float newEpsilon) {
    epsilon = newEpsilon;
}

void Agent::save(const std::string& path) {
    policyNetwork.save(path);
}

void Agent::load(const std::string& path) {
    policyNetwork.load(path);
}

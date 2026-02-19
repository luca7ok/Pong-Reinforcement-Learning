#pragma once

#include <torch/optim/adam.h>

#include "NeuralNetwork.h"
#include "RL_Structs.h"
#include "ReplayBuffer.h"

namespace RL = RL_Structs;

class Agent {
private:
    NeuralNetwork policyNetwork;
    NeuralNetwork targetNetwork;
    ReplayBuffer memory;
    torch::optim::Adam optimizer;

    int batchSize;
    float gamma;
    float epsilon;
    float epsilonDecay;
    float epsilonMin;
    int learnStepCounter;
    int targetUpdateFreq;

public:
    Agent(int inputSize, int hiddenSize, int outputSize, int capacity, int batchSize,
          float learningRate, float gamma, float epsilon, float epsilonDecay, float epsilonMin,
          int targetUpdateFreq);

    ~Agent() = default;

    int selectAction(const RL::GameState& gameState);

    void storeExperience(const RL::Experience& experience);

    void learn();

    void updateTargetNetwork();

    void decayEpsilon();

    float getEpsilon() const;

    void setEpsilon(float newEpsilon);

    void save(const std::string& path);

    void load(const std::string& path);
};
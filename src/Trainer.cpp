#include "Trainer.h"

#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

#include "Agent.h"
#include "Constants.h"
#include "Game.h"
#include "RL_Structs.h"

Trainer::Trainer(int _episodes) : episodes{_episodes} {};

void Trainer::run() {
    clearCheckpoints();
    if (!std::filesystem::exists("models")) {
        std::filesystem::create_directories("models");
    }

    Agent agent{C::INPUT_LAYER_SIZE,
                C::HIDDEN_LAYER_SIZE,
                C::OUTPUT_LAYER_SIZE,
                C::MAX_BUFFER_CAPACITY,
                C::BATCH_SIZE,
                C::LEARNING_RATE,
                C::GAMMA,
                C::EPSILON,
                C::EPSILON_DECAY,
                C::EPSILON_MIN,
                C::TARGET_UPDATE_FREQ};
    Game game;
    game.setShouldRender(false);

    int actionMap[] = {0, -1, 1};

    for (int episode = 1; episode <= episodes; episode++) {
        game.reset();

        RL::GameState initialState = game.getGameState();
        RL::StackedState stackedState = {initialState, initialState, initialState, initialState};
        float totalReward = 0;
        bool done = false;

        while (!done) {
            int actionIndex = agent.selectAction(stackedState);
            int gameAction = actionMap[actionIndex];

            float accumulatedReward = 0.f;
            RL::GameState lastState;
            bool isDone = false;

            for (int i = 0; i < C::SKIP_FRAMES; i++) {
                auto [stepState, stepReward, stepDone] = game.step(gameAction);
                accumulatedReward += stepReward;
                lastState = stepState;
                isDone = stepDone;

                if (isDone) {
                    break;
                }
            }

            RL::StackedState nextStackedStat = stackedState;
            for (int i = 0; i < 3; i++) {
                nextStackedStat[i] = nextStackedStat[i + 1];
            }
            nextStackedStat[3] = lastState;

            agent.storeExperience(
                {stackedState, actionIndex, accumulatedReward, nextStackedStat, isDone});
            agent.learn();

            stackedState = nextStackedStat;
            totalReward += accumulatedReward;
            done = isDone;
        }

        agent.decayEpsilon();

        if (episode % 25 == 0) {
            std::cout << "Episode " << episode << ", reward: " << totalReward
                      << ", epsilon: " << agent.getEpsilon() << '\n';
        }

        if (episode % 100 == 0) {
            std::string checkpointPath =
                "checkpoints/checkpoints_" + std::to_string(episode) + ".pt";
            agent.save(checkpointPath);
        }
    }
    std::string modelPath = getNextModelPath(episodes);
    agent.save(modelPath);
    std::cout << "Training complete\n";
}

void Trainer::clearCheckpoints() {
    if (std::filesystem::exists("checkpoints")) {
        for (const auto& entry : std::filesystem::directory_iterator("checkpoints")) {
            if (entry.path().filename().string() != ".gitkeep") {
                std::filesystem::remove_all(entry.path());
            }
        }
    } else {
        std::filesystem::create_directories("checkpoints");
    }
}

int Trainer::getLatestModelVersion() {
    int maxVersion = 0;

    std::regex versionPattern(R"(v(\d+)(?:_\d+)?\.pt)");
    std::smatch match;

    if (std::filesystem::exists("models")) {
        for (const auto& model : std::filesystem::directory_iterator("models")) {
            std::string filename = model.path().filename().string();
            if (std::regex_match(filename, match, versionPattern)) {
                int version = std::stoi(match[1]);
                if (version > maxVersion) {
                    maxVersion = version;
                }
            }
        }
    }

    return maxVersion;
}

std::string Trainer::getNextModelPath(int episodes) {
    int nextVersion = getLatestModelVersion() + 1;
    return "models/v" + std::to_string(nextVersion) + "_" + std::to_string(episodes) + ".pt";
}
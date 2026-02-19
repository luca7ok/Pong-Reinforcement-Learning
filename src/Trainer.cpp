#include "Trainer.h"

#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

#include "Agent.h"
#include "Game.h"

void Trainer::run() {
    clearChecpoints();
    if (!std::filesystem::exists("assets/models")) {
        std::filesystem::create_directories("assets/models");
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

    for (int episode = 1; episode <= C::EPISODES; episode++) {
        game.reset();

        RL::GameState state = game.getGameState();
        float totalReward = 0;
        bool done = false;

        while (!done) {
            int actionIndex = agent.selectAction(state);
            int gameAction = actionMap[actionIndex];

            auto [nextState, reward, isDone] = game.step(gameAction);
            done = isDone;

            agent.storeExperience({state, actionIndex, reward, nextState, isDone});
            agent.learn();

            state = nextState;
            totalReward += reward;
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
    std::string modelPath = getNextModelPath();
    agent.save(modelPath);
    std::cout << "Training complete\n";
}

void Trainer::clearChecpoints() {
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

std::string Trainer::getNextModelPath() {
    int maxVersion = 0;
    std::regex versionPattern(R"(v(\d+)\.pt)");
    std::smatch match;

    if (std::filesystem::exists("assets/models")) {
        for (const auto& model : std::filesystem::directory_iterator("assets/models")) {
            std::string filename = model.path().filename().string();
            if (std::regex_match(filename, match, versionPattern)) {
                int version = std::stoi(match[1]);
                if (version > maxVersion) {
                    maxVersion = version;
                }
            }
        }
    }

    return "assets/models/v" + std::to_string(maxVersion + 1) + ".pt";
}
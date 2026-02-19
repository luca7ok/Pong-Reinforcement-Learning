#include <torch/torch.h>

#include <iostream>

#include "Game.h"
#include "Trainer.h"

int main(int argc, char* argv[]) {
    bool trainingMode = false;
    if (argc > 1 && std::string(argv[1]) == "train") {
        trainingMode = true;
    }

    try {
        if (trainingMode) {
            std::cout << "Start training\n";
            Trainer trainer;
            trainer.run();

        } else {
            std::string latestModel = Trainer::getLatestModelPath();

            if (latestModel.empty()) {
                std::cout << "No model found. Playing in manual mode\n";
                Game game;
                game.setShouldRender(true);
                game.run(nullptr);

            } else {
                std::cout << "Loading model: " << latestModel << '\n';
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
                agent.load(latestModel);
                agent.setEpsilon(0.f);

                Game game;  
                game.setShouldRender(true);
                game.run(&agent);
            }
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
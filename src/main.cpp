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
            Trainer trainer;
            trainer.run();

        } else {
            Game game;
            game.setShouldRender(true);
            

            game.run();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
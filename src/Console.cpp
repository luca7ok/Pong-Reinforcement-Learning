#include "Console.h"

#include <cstdlib>
#include <filesystem>
#include <ios>
#include <limits>
#include <regex>

#include "Constants.h"
#include "Game.h"
#include "Trainer.h"

void ConsoleUI::run() {
    while (true) {
#if defined(_WIN32)
        std::system("cls");
#else
        std::system("clear");
#endif
        printMenu();

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            return;
        }

        int option;
        std::stringstream ss(input);

        if (!(ss >> option)) {
            std::cout << "\nInvalid input\n";
            std::cout << "Press enter to continue...";
            std::cin.get();
            continue;
        }

        switch (option) {
            case 0:
                return;
            case 1:
                trainModel();
                break;
            case 2:
                playerVsHardcodedAI();
                break;
            case 3:
                trainedVsHardcodedAI();
                break;

            default:
                std::cout << "\nInvalid option\n";
                std::cout << "Press enter to continue...";
                std::cin.get();
                break;
        }
    }
}

void ConsoleUI::printMenu() {
    std::cout << "\nChoose an option:\n";
    std::cout << "[1] Train model\n";
    std::cout << "[2] Play hardcoded AI\n";
    std::cout << "[3] Play trained AI vs Hardcoded AI\n";
    std::cout << "[0] Exit\n";
    std::cout << "Your option: ";
}

void ConsoleUI::trainModel() {
    std::cout << "\nNumber of episodes: ";

    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "\nInvalid input\n";
        std::cout << "Press enter to continue...";
        std::cin.get();
        return;
    }

    int episodes;
    std::stringstream ss(input);

    if (!(ss >> episodes) || episodes <= 0) {
        std::cout << "\nInvalid input\n";
        std::cout << "Press enter to continue...";
        std::cin.get();
        return;
    }

    Trainer trainer(episodes);
    trainer.run();
}

void ConsoleUI::playerVsHardcodedAI() {
    Game game;
    game.setShouldRender(true);
    game.run(nullptr);
}

void ConsoleUI::trainedVsHardcodedAI() {
    std::vector<std::string> models = getModels();

    if (models.empty()) {
        std::cout << "\nNo trained models\n";
        std::cout << "Press enter to continue...";
        std::cin.get();
        return;
    }

    std::cout << "\nAvailable models:\n";
    for (int i = 0; i < models.size(); i++) {
        std::cout << "[" << (i + 1) << "] " << models[i] << "\n";
    }
    std::cout << "\nChoose a model: ";

    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "\nInvalid input\n";
        std::cout << "Press enter to continue...";
        std::cin.get();
        return;
    }

    int option;
    std::stringstream ss(input);

    if (!(ss >> option) || option < 1 || option > models.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInvalid option\n";
        std::cout << "Press enter to continue...";
        std::cin.get();
        return;
    }

    std::string selectedModel = models[option - 1];
    std::cout << "Loading model: " << selectedModel << '\n';

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
    agent.load(C::MODELS_PATH + selectedModel);
    agent.setEpsilon(0.f);

    Game game;
    game.setShouldRender(true);
    game.run(&agent);
}

std::vector<std::string> ConsoleUI::getModels() const {
    std::vector<std::string> models;
    std::regex versionPattern(R"(v\d+(?:_\d+)?\.pt)");

    if (std::filesystem::exists("models")) {
        for (const auto& model : std::filesystem::directory_iterator("models")) {
            std::string filename = model.path().filename().string();
            if (std::regex_match(filename, versionPattern)) {
                models.push_back(filename);
            }
        }
    }

    std::sort(models.begin(), models.end(), [](const std::string& a, const std::string& b) {
        std::regex r(R"(v(\d+))");
        std::smatch matchA, matchB;
        std::regex_search(a, matchA, r);
        std::regex_search(b, matchB, r);
        return std::stoi(matchA[1]) < std::stoi(matchB[1]);
    });

    return models;
}
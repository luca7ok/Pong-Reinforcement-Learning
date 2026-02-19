#pragma once

class ConsoleUI {
private:
    void printMenu();

    void trainModel();

    void playerVsHardcodedAI();

    void trainedVsHardcodedAI();

    std::vector<std::string> getModels() const;

public:
    void run();
};
#pragma once

class Trainer {
private:
    void clearChecpoints();
    std::string getNextModelPath();

public:
    void run();
};
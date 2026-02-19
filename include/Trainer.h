#pragma once

class Trainer {
private:
    void clearChecpoints();

    static int getLatestModelVersion();

    static std::string getNextModelPath(float episodes);

public:
    static std::string getLatestModelPath();

    void run();
};
#pragma once

class Trainer {
private:
    int episodes;

    void clearChecpoints();

    static int getLatestModelVersion();

    static std::string getNextModelPath(int episodes);

public:
    Trainer(int _episodes);

    ~Trainer() = default;

    void run();
};
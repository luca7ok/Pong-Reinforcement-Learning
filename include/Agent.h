#pragma once

#include <deque>

#include "NeuralNetwork.h"
#include "RL_Structs.h"

namespace RL = RL_Structs;

class Agent {
private:
    NeuralNetwork brain;
    std::deque<RL::Experience> replayBuffer;

    float epsilon;
    float epsilonDecay;
    float learningRate;
    int batchSize;

public:
    Agent();

    ~Agent() = default;

    int getAction(const RL::GameState& state);

    void remember(const RL::Experience& experience);

    void train();

    void save(const std::string& filename);
    
    void load(const std::string& filename);
}
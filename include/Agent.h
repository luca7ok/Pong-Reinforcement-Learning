#pragma once

#include <torch/optim/adam.h>

#include <deque>
#include <memory>

#include "NeuralNetwork.h"
#include "RL_Structs.h"
#include "ReplayBuffer.h"

namespace RL = RL_Structs;

class Agent {
private:
    NeuralNetwork policyNetwork;
    NeuralNetwork targetNetwork;
    ReplayBuffer buffer;
    torch::optim::Adam optimizer;

    int batchSize;
    float gamma;
    float epsilon;
    float epsilonDecay;
    float epsilonMin;
    int learnStepCounter;
    int targetUpdateFreq;

public:
    Agent();

    ~Agent()
};
#pragma once

#include <torch/torch.h>

#include <string>

#include "RL_Structs.h"

namespace RL = RL_Structs;

class NeuralNetwork : public torch::nn::Module {
private:
    torch::nn::Linear inputLayer{nullptr};
    torch::nn::Linear hiddenLayer{nullptr};
    torch::nn::Linear outputLayer{nullptr};

public:
    NeuralNetwork(int inputSize, int hiddenSize, int outputSize);

    ~NeuralNetwork() = default;

    torch::Tensor forward(torch::Tensor x);

    int predictAction(const RL::StackedState& GameState);

    void save(const std::string& path);

    void load(const std::string& path);
};
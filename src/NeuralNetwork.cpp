#include "NeuralNetwork.h"

#include <torch/types.h>

#include "Constants.h"
#include "RL_Structs.h"

namespace C = Constants;

NeuralNetwork::NeuralNetwork(int inputSize, int hiddenSize, int outputSize) {
    inputLayer = register_module("fc1", torch::nn::Linear(inputSize, hiddenSize));
    hiddenLayer = register_module("fc2", torch::nn::Linear(hiddenSize, hiddenSize));
    outputLayer = register_module("fc3", torch::nn::Linear(hiddenSize, outputSize));
}

torch::Tensor NeuralNetwork::forward(torch::Tensor inputState) {
    torch::Tensor features = torch::relu(inputLayer->forward(inputState));
    features = torch::relu(hiddenLayer->forward(features));
    torch::Tensor qValues = outputLayer->forward(features);

    return qValues;
}

int NeuralNetwork::predictAction(const RL::StackedState& gameState) {
    std::vector<float> flatState;
    flatState.reserve(C::INPUT_LAYER_SIZE);

    for (const auto& s : gameState) {
        flatState.push_back(s.ballX);
        flatState.push_back(s.ballY);
        flatState.push_back(s.ballVelocity.x);
        flatState.push_back(s.ballVelocity.y);
        flatState.push_back(s.paddleY);
        flatState.push_back(s.enemyY);
    }

    torch::Tensor inputTensor = torch::tensor(flatState, torch::kFloat32);

    torch::Tensor output = forward(inputTensor);

    return output.argmax().item<int>();
}

void NeuralNetwork::save(const std::string& path) {
    torch::serialize::OutputArchive archive;
    this->torch::nn::Module::save(archive);
    archive.save_to(path);
}

void NeuralNetwork ::load(const std::string& path) {
    torch::serialize::InputArchive archive;
    archive.load_from(path);
    this->torch::nn::Module::load(archive);
}
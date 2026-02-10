#include "NeuralNetwork.h"

#include <torch/nn/module.h>
#include <torch/serialize/archive.h>

#include "RL_Structs.h"

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

int NeuralNetwork::predictAction(const RL::GameState& gameState) {
    torch::Tensor inputTensor =
        torch::tensor({gameState.ballX, gameState.ballY, gameState.ballVelocity.x,
                       gameState.ballVelocity.y, gameState.paddleY, gameState.enemyY},
                      torch::kFloat32);

    torch::Tensor output = forward(inputTensor);

    return output.argmax().item<int>();
}

void NeuralNetwork::save(const std::string& filename) {
    torch::serialize::OutputArchive archive;
    this->torch::nn::Module::save(archive);
    archive.save_to(filename);
}

void NeuralNetwork ::load(const std::string& filename) {
    torch::serialize::InputArchive archive;
    archive.load_from(filename);
    this->torch::nn::Module::load(archive);
}
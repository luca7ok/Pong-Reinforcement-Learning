#include "ReplayBuffer.h"

#include <random>
#include <vector>

#include "RL_Structs.h"

ReplayBuffer::ReplayBuffer(int _capacity) : capacity{_capacity} {
    std::random_device randomDevice;
    rng.seed(randomDevice());
}

void ReplayBuffer::push(const RL::Experience& experience) {
    buffer.push_back(experience);
    if (buffer.size() > capacity) {
        buffer.pop_front();
    }
}

std::vector<RL::Experience> ReplayBuffer::sample(int batchSize) {
    std::vector<RL::Experience> batch;
    std::uniform_int_distribution<int> distribution(0, buffer.size() - 1);

    for (int i = 0; i < batchSize; i++) {
        batch.push_back(buffer[distribution(rng)]);
    }
    return batch;
}
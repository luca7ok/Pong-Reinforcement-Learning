#include "ReplayBuffer.h"

#include <random>
#include <vector>

#include "RL_Structs.h"

ReplayBuffer::ReplayBuffer(int _capacity) : capacity{_capacity} {
}

void ReplayBuffer::push(const RL::Experience& experience) {
    buffer.push_back(experience);
    if (buffer.size() > capacity) {
        buffer.pop_front();
    }
}

std::vector<RL::Experience> ReplayBuffer::sample(int batchSize) {
    std::vector<RL::Experience> batch;
    static std::random_device randomDevice;
    static std::mt19937 rng(randomDevice());
    std::uniform_int_distribution<int> distribution(0, buffer.size() - 1);

    for (int i = 0; i < batchSize; i++) {
        batch.push_back(buffer[distribution(rng)]);
    }
    return batch;
}

int ReplayBuffer::getSize() const {
    return buffer.size();
}
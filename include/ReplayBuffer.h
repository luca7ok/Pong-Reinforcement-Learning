#pragma once

#include <deque>
#include <vector>

#include "RL_Structs.h"

namespace RL = RL_Structs;

class ReplayBuffer {
private:
    std::deque<RL::Experience> buffer;
    int capacity;

public:
    ReplayBuffer(int _capacity);

    ~ReplayBuffer() = default;

    void push(const RL::Experience& experience);

    std::vector<RL::Experience> sample(int batchSize);

    int getSize() const;
};
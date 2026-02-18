cmake_minimum_required(VERSION 3.16)

project(Pong-Reinforcement-Learning VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
find_package(Torch REQUIRED)

include_directories(include)

add_executable(main
    src/main.cpp
    src/Game.cpp
    src/Ball.cpp
    src/Paddle.cpp
    src/Score.cpp
    src/Agent.cpp
    src/NeuralNetwork.cpp
    src/Trainer.cpp
    src/ReplayBuffer.cpp
)

target_link_libraries(main PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
    Eigen3::Eigen
    ${TORCH_LIBRARIES})

target_include_directories(main PRIVATE ${TORCH_INCLUDE_DIRS})

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

target_precompile_headers(main PRIVATE <torch/torch.h>)
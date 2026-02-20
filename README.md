# Pong DQN Agent

A custom reinforcement learning project written in C++, designed to train an AI to master the game of Pong. This project implements a Deep Q-Network using LibTorch and a custom game environment built with SFML, demonstrating advanced RL concepts such as experience replay, frame stacking, and target network updating.

## Overview

This project was developed to explore the implementation of deep reinforcement learning algorithms from scratch in a C++ environment. It allows users to train a DQN agent against a hardcoded AI opponent, tune critical hyperparameters, and visualize the trained agent's performance in real-time.

## Features
### The Game Environment

The project features a custom, lightweight Pong engine built with SFML:
* **SFML Integration** for rendering and hardware input.
* **Frame-Independent Physics** ensuring consistent ball trajectories and paddle movement.
* **AABB Collision Detection** for accurate interactions between the ball, walls, and paddles.
* **Continuous State Normalization** to feed optimized, scaled data to the neural network.

### Reinforcement Learning (DQN)

The autonomous agent is powered by a modern DQN architecture:

* **Experience Replay Buffer** to store and sample past gameplay states, stabilizing the learning process.

* **Dual Network System** utilizing both a Policy Network (for active learning) and a Target Network (for stable Q-value calculation).
* **Epsilon-Greedy Exploration** to balance random discovery with learned exploitation.
* **Automated Tensor Conversion** bridging raw C++ game structs with LibTorch mathematical matrices.

## Operating Modes

You can swap between two distinct execution states depending on your current goal:

* **Headless Training Mode**: Disables all rendering to run thousands of game steps per second for rapid model training.

* **Visualization Mode**: Caps the framerate at 60 FPS and renders the environment to observe the AI's learned behaviors.

## Building from source
This project uses CMake. Because LibTorch is typically installed manually rather than through a package manager, you must provide CMake with the absolute path to your LibTorch directory during the configuration step.

1. Create and enter the build directory.
   ```bash
   mkdir build
   cd build
   ```
2. Configure the project: Replace /absolute/path/to/libtorch with the actual location where you extracted the LibTorch archive, e.g. /usr/local/libtorch

   ```bash
   cmake -DCMAKE_PREFIX_PATH=/absolute/path/to/libtorch ..
   ```

3. Compile the executable.
   ```bash
   cmake --build .
   ```
## Usage
1. Start the compiled executable. 
   ```bash
   cmake --build build && ./build/bin/main
   ```
2. Choose an option from the main menu.
3. Configure your session:

    * If training, input the number of episodes.

    * If evaluating, select your desired .pt model from the generated list.
4. Let the application run:
    * Training will run headlessly, saving checkpoints to the checkpoints/ folder and the final model to models/.
    * Gameplay and evaluation will open an SFML window where you can watch the game unfold in real-time.


## Dependencies

To build and run this project, you will need the following installed on your system:

* CMake (v3.16 or higher): The build system generator required to configure the project.

* A C++17 compatible compiler: The build is explicitly configured to require C++17 standard support (e.g., GCC, Clang, or MSVC).

* SFML (v2.5 or higher): Required for rendering the game. Specifically, the project uses the graphics, window, and system modules.

* LibTorch (PyTorch C++ Distribution): Required for the reinforcement learning agent and neural network.

## License

[MIT](https://choosealicense.com/licenses/mit/)

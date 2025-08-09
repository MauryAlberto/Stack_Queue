
# Stack and Queue Class Templates

This repository contains two separate C++ projects implementing **Stack** and **Queue** class templates using singly linked lists with capacity constraints.

Each project is self-contained in its own folder with a simple `main.cpp` file to test the class functionality.

---

## Stack

- Implements a templated stack data structure using a singly linked list.
- Supports push and pop operations with move semantics and capacity checks.
- Provides copy constructor and copy assignment operator for deep copies.
- Includes helper methods: `empty()`, `size()`, `totalCapacity()`, `clear()`, and `printStack()`.

### Building and Running the Stack Project

```bash
cd Stack
mkdir build
cd build
cmake ..
make
./StackApp
```

---

## Queue

- Implements a templated queue data structure using a singly linked list.
- Supports enqueue and dequeue operations with move semantics and capacity checks.
- Provides copy constructor and copy assignment operator for deep copies.
- Includes helper methods: `empty()`, `size()`, `totalCapacity()`, `clear()`, and `printQueue()`.

### Building and Running the Queue Project

```bash
cd Queue
mkdir build
cd build
cmake ..
make
./QueueApp
```

---

## Requirements

- C++17 compatible compiler (e.g. `g++`, `clang++`)
- CMake version 3.10 or higher

---

## Project Structure

```
project_root/
│
├── Stack/
│   ├── CMakeLists.txt
│   └── main.cpp
│
└── Queue/
    ├── CMakeLists.txt
    └── main.cpp
```

---

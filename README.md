# Network Emulator

## Introduction
The **Network Emulator** is a simulation tool designed to mimic real-world network behavior. It models routers, machines, priority-based message forwarding, and dynamic routing tables. This project is implemented in **C++** and demonstrates several data structures such as **priority queues, linked lists, and splay trees**.

## Features
- **Priority-Based Message Queuing** using a binary heap.
- **FIFO-Based Outgoing Queues** for message forwarding.
- **Routing Table Implementation** using:
  - Linear Lists
  - Splay Trees
- **Dijkstra’s Algorithm** for computing shortest paths.
- **Dynamic Routing Table Updates** (via command-line or file).
- **Network Delay Simulation** with a 1-second delay for message transfer between routers.
- **Edge Weight Modification** to update network routing in real-time.
- **File-Based Input/Output** support for messages and network configurations.

## Installation & Requirements

### Prerequisites
- **C++ Compiler:** Compatible with any standard C++ compiler (e.g., MinGW, MSVC).
- **Visual Studio 2019 or above:** Recommended for best compatibility.
- **Operating System:** Windows (Note: The code includes `Windows.h`; modifications may be needed for other OS).

### Compilation
To compile the project using g++, for example:
```bash
g++ -o network_emulator 20i-0700_20i-0607_20i-0681_P.cpp

./network_emulator

```

## How It Works
1. **Message Routing System**
Routers: Each router processes incoming messages based on their priority (using a binary heap) and then forwards the message to the appropriate outgoing queue.
Routing Table: Determines the next hop for a message using either:
Linear Lists or
Splay Trees
2. **Network Graph & Shortest Path Computation**
The network is represented as a weighted adjacency matrix (read from a CSV file).
Dijkstra’s algorithm is used to compute the shortest path from a source to a destination, updating the routing table accordingly.
3. **Delay Simulation**
Each message experiences a 1-second delay when transitioning from one router to the next, simulating real network latency.
Usage Guide
Upon running the program, a menu-driven interface is presented with the following options:

### 1. Write a Message

Enter message details manually:
**Message ID**
**Priority (0-10)**
**Source Address (e.g., M1, M2)**
**Destination Address (e.g., M7, M8)**
**Payload (Message Content)**
**Read a Message from a File**

### 2. Read a Message from a File
+ Reads messages from message.txt (or any provided file).
+ Messages are then processed through the routing system.

### 3. Change the Weight of an Edge

+ Update the weight of a specific connection in the network graph.
+ This triggers a recomputation of the shortest path.

### 4. Change an Edge

+ Dynamically modify the network by adding or removing edges, then update the routing tables accordingly.

### Example Command Queries
```bash 
Copy
Edit
send msg message.txt
change RT R1 add routing_table.csv
change RT R2 remove routing_table.csv
print path M6 to M9
print path M6 to *
print path * to M9
```

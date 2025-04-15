# Network-Emulator

This project is a **Network Emulator** implemented in C++. The emulator simulates a message-passing computer network consisting of routers and machines, handling routing, priorities, and delays.

## Features

- Priority-based message routing using **binary heaps**
- FIFO outgoing queues with simulated **network latency**
- Support for **routing tables** that dynamically update
- Message tracing from source to destination
- **CSV-based** network topology configuration
- **Dijkstra's algorithm** to compute optimal paths
- Command-based interaction and file support
- Simulated **interrupt mechanism** for timed message delivery

## Project Structure

- `Messages` class: Handles message creation, display, and file I/O
- `Routers` class: Manages incoming/outgoing queues and routing logic
- `AdjMatrix` class: Parses network topology from `network.csv`
- `Network` class: Emulates complete network behavior, handles Dijkstra’s routing
- `main.cpp`: Interactive menu-driven program to operate the emulator

### Messages.txt
Each message is stored in comma-separated format:

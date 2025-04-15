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

---

## 📂 Files and Responsibilities

| File/Class         | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| `main.cpp`         | The main driver file with a menu system for interacting with the emulator. |
| `Messages`         | Manages message creation, display, file I/O, and priority comparison.       |
| `Routers`          | Handles incoming priority queue, outgoing FIFO queue, and routing logic.    |
| `AdjMatrix`        | Reads and stores network topology from `network.csv`.                       |
| `Network`          | Builds and simulates the network using the matrix and Dijkstra's algorithm. |
| `Messages.txt`     | Stores messages in a persistent, comma-separated format.                    |
| `RoutingTable.txt` | Logs routing entries for source-destination pairs.                          |
| `path.txt`         | Stores the final trace/path of messages from source to destination.         |
| `network.csv`      | Input file representing the adjacency matrix of the network graph.          |
----------------------------------------------------------------------------------------------------

### Messages.txt

Each message is stored in comma-separated format:

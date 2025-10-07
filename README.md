# 🏭 Supply Chain Optimization using Graphs and Network Flow Algorithms

## 📖 Overview
This project models **supply chains as graphs** and optimizes the routes and inventory flow using **network flow algorithms** and **graph traversal techniques**.  
The program takes input in the form of **directed edges** representing supply routes, each with a **capacity** and **cost**.  
It applies a **Minimum Cost Maximum Flow (MCMF)** algorithm to determine:
- The **maximum flow** from a source warehouse to a consumer.
- The **minimum cost** to send that flow.

The program leverages **Dijkstra's algorithm** for finding the shortest path with reduced costs and uses **graph structures** like edges, nodes, and adjacency lists to represent the supply chain network.

---

## ✨ Features
- **Graph Representation:** Models supply chain nodes (warehouses and consumers) and edges (routes with capacity and cost).
- **User Input:** Allows users to input multiple routes with origin, destination, capacity, and cost.
- **Flow Calculation:** Computes the Maximum Flow and Minimum Cost between a source warehouse and consumer using the Successive Shortest Path algorithm.
- **Interactive Mode:** Users can test different source and consumer pairs and view the results.

---

## 🧱 Components

### 🗂 Data Structures

#### **Edge Structure**
Represents a directed edge between two nodes with the following attributes:
- `to`: Destination node (consumer or warehouse)
- `capacity`: Maximum flow capacity
- `cost`: Cost per unit of flow
- `flow`: Current flow through the edge
- `rev`: Index of the reverse edge in the adjacency list

#### **Graph Class**
Handles the network of nodes and edges. Supports:
- Adding edges between nodes
- Storing adjacency lists of edges
- Managing potentials used in reduced-cost shortest path calculations

---

## 🧮 Key Algorithms

### **Dijkstra's Algorithm**
Used to find the **shortest path** with the least cost, factoring in reduced costs based on node potentials.

### **Successive Shortest Path Algorithm**
Used for solving the **Minimum Cost Maximum Flow (MCMF)** problem.  
It repeatedly finds augmenting paths and adjusts the flow and total cost accordingly.

---

## ⚙️ Functions

### `dijkstra()`
Implements Dijkstra’s algorithm with reduced costs to find the shortest path between source and sink nodes.

### `minCostMaxFlow()`
Calculates the **maximum flow** and **minimum cost** from the source node to the sink node using successive shortest paths.

---

## 🧑‍💻 How to Use

## Example
### Input
A B 100 10
B C 50 5
A C 70 8
stop
Enter source: A
Enter consumer: C

### Output
Maximum Flow: 120
Minimum Cost: 1160


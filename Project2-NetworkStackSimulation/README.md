# Network Stack Simulation – BBM203 Project 2

This project was developed as part of the BBM203 Software Laboratory I course at Hacettepe University. It simulates the basic functioning of the OSI model's layers through object-oriented C++ programming.

## 📚 Course Info
- Course: BBM203 – Software Lab I
- Semester: Fall 2023
- Student: Yüksel Çağrı Arslan

## 🧠 Project Description

The simulation models how data packets move through different layers of a computer network system:

1. **Application Layer**
2. **Transport Layer**
3. **Network Layer**
4. **Physical Layer**

Each layer adds its own header and passes the packet down to the next, simulating encapsulation.

## 🧩 Components

| File | Description |
|------|-------------|
| `ApplicationLayerPacket.*` | Handles logic for the Application Layer |
| `TransportLayerPacket.*` | Simulates Transport Layer (e.g., port numbers) |
| `NetworkLayerPacket.*` | Handles IP-related logic |
| `PhysicalLayerPacket.*` | Simulates the final transmission layer |
| `Packet.*` | Base class for layered packets |
| `Client.*` | Simulates a user or host interacting with the system |
| `Network.*` | Manages overall communication |
| `Log.*` | Responsible for logging actions during transmission |

## 🛠️ How to Compile

```bash
g++ -std=c++11 *.cpp -o network_simulation
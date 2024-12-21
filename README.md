### **Description of the Project**

#### **Project Title**
**2D Multiplayer Barrage Game with Embedded Systems Concepts**

#### **Overview**
This project is a 2D, two-player multiplayer game where players compete in a simple PvP barrage scenario. Each player controls an avatar that can move left and right to dodge incoming bullets while automatically shooting their own projectiles. The objective is to survive longer than the opponent, with additional points awarded for successful hits. The game concludes when both players' avatars are destroyed, with the results displayed at the end. 

The primary focus of the project is to integrate concepts from the Embedded Operating Systems course, including inter-process communication (IPC), synchronization, multiprocessing, threading, timers, and signals, into a functional and demonstrable system. The server, implemented in C++, manages game logic, collision detection, and real-time synchronization, while the clients, implemented in Python, render the game and handle user input.

---

#### **Key Features**
1. **Game Mechanics**
    - **Player Actions:** Players can move left or right using two key presses.
    - **Automated Shooting:** Bullets are fired automatically at regular intervals.
    - **Collision Detection:** Bullets hitting an opponent register a score.
    - **Game Objective:** The first player to lose their avatar spectates while the other continues until both are destroyed. The surviving duration and the last-hit points determine the final score.

2. **Networking**
    - **Client-Server Model:** The server handles game logic and state synchronization, while the clients render the game and manage player inputs.
    - **Communication:** Data is exchanged using TCP sockets with JSON-formatted messages for language-agnostic interoperability.
    - **Connection Handling:** The server waits for two players to connect before starting the game. Connections terminate at the end of the game.

3. **Embedded Systems Integration**
    - **Multithreading:** The server uses threads to handle multiple clients and manage the game loop.
    - **Synchronization:** Shared resources (e.g., game state) are protected using mutexes.
    - **Timers:** A timer drives the game loop for consistent state updates (~30–60 FPS).
    - **Signals:** Signal handling may be incorporated to manage clean server shutdowns or specific interrupts.

4. **Simplified Deployment**
    - The game is designed for a local network environment using a server hosted on a Raspberry Pi and client devices connected via Wi-Fi. This setup ensures low latency and demonstrates practical embedded system constraints.

---

#### **Technical Implementation**

1. **Server (C++):**
    - Manages the entire game state, including player positions, bullet trajectories, and scores.
    - Implements a fixed-tick game loop to process inputs, update states, and send updates to clients.
    - Uses Box2D for collision detection, simplifying the implementation of bullet-object interactions.
    - Threads handle player connections and maintain real-time synchronization.

2. **Client (Python):**
    - Receives game state updates from the server and renders the game environment.
    - Sends player inputs (e.g., left/right movement) to the server in real time.
    - Displays final game results after the match ends.

3. **Networking:**
    - TCP sockets ensure reliable communication between the server and clients.
    - JSON is used for structured message exchanges (e.g., player positions, bullet states).

4. **Game State Management:**
    - Tracks player positions, active bullets, scores, and game status (alive/dead).
    - Updates and broadcasts state at regular intervals (~30–60 times per second).

---

#### **Development Goals**
1. **Core Objectives:**
    - Provide a functional multiplayer game that demonstrates course-related concepts.
    - Ensure the server correctly manages game state, handles client communication, and processes events in real time.

2. **Technical Highlights:**
    - Implementing multithreading to manage multiple clients.
    - Synchronizing shared resources (game state) using mutexes to prevent race conditions.
    - Using timers to drive consistent game updates.
    - Incorporating collision detection using Box2D for accurate gameplay mechanics.

3. **Simplified Gameplay Experience:**
    - Focus on basic mechanics and minimalistic visuals to ensure timely delivery.
    - Restrict the environment to a local network for easier testing and debugging.

---

#### **Challenges and Solutions**
1. **Challenge:** Synchronizing game state across clients.
    - **Solution:** The server acts as the single source of truth, broadcasting updates to clients at fixed intervals.

2. **Challenge:** Managing shared resources in a multithreaded server.
    - **Solution:** Use mutexes to lock shared game state during updates.

3. **Challenge:** Collision detection and physics.
    - **Solution:** Leverage Box2D for efficient and accurate collision handling.

4. **Challenge:** Testing and debugging the system within a week.
    - **Solution:** Focus on an MVP, with basic functionality prioritized over polish or scalability.

---

#### **Expected Outcome**
The project will deliver a working prototype of a 2D multiplayer barrage game. Players will be able to connect to the server, compete in a game round, and view results at the end. The server will demonstrate EOS concepts such as threading, synchronization, and timers in a real-time system. This system will highlight how embedded system principles can be applied to create a small-scale multiplayer game.


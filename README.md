# Social-Network-Simulation
📱 Social Network Simulation in C++
A modular and object-oriented social networking system written in modern C++, simulating the core features of platforms like Facebook and Instagram. The project uses custom implementations of fundamental data structures and algorithms to create a lightweight yet powerful backend simulation.

🚀 Features
📋 User Profiles
Secure user creation with password validation
Stores personal details (city, last login time)
Security question-answer mechanism for account recovery

📮 Messaging & Notifications
Send private messages between user
Notifications for follow requests, messages, and more
Stack and queue-based storage for efficient message and notification management

📰 Posts & Timeline
Users can create posts
View personal timeline and newsfeed (posts from followed users)

🤝 Following System
Send, accept, and manage follow requests
View followers and following lists
Notifications for accepted requests

🔐 Security
Password validation (must include uppercase, lowercase, digit, and special character)
Encapsulated password logic in UserAuthenticator

🌐 Social Network Graph
Represents users as nodes and connections as edges
Supports Breadth-First Search (BFS) and Depth-First Search (DFS) for traversal
Suggest mutual friends based on shared connections

🧪 Sample Functionalities
Create and display user profile info
Post messages and view timeline
Send and receive private messages
Perform BFS and DFS across user connections
Suggest mutual friends using graph analysis

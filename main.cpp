
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>
using namespace std;

template <typename T>
class CustomStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int currentSize;

public:
    CustomStack() : topNode(nullptr), currentSize(0) {}

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        ++currentSize;
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow: Attempted to pop from an empty stack.");
        }
        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        --currentSize;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty: Cannot peek.");
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    int size() const {
        return currentSize;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    ~CustomStack() {
        clear();
    }
};

// Custom Queue Template 
template <typename T>
class CustomQueue {
private:
    struct QueueNode {
        T data;
        QueueNode* next;
        QueueNode(T value) : data(value), next(nullptr) {}
    };
public:
    QueueNode* frontNode;
    QueueNode* rearNode;

    CustomQueue() : frontNode(nullptr), rearNode(nullptr) {}

    void enqueue(T value) {
        QueueNode* newNode = new QueueNode(value);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        }
        else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    T dequeue() {
        if (isEmpty()) throw runtime_error("Queue is empty");
        QueueNode* temp = frontNode;
        T value = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
        return value;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int size() const {
        int count = 0;
        QueueNode* current = frontNode;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    void display() {
        QueueNode* current = frontNode;
        int index = 1;
        while (current) {
            cout << index++ << ". " << current->data << endl;
            current = current->next;
        }
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Copy constructor and assignment operator
    CustomQueue(const CustomQueue& other) : frontNode(nullptr), rearNode(nullptr) {
        QueueNode* current = other.frontNode;
        while (current) {
            enqueue(current->data);
            current = current->next;
        }
    }

    CustomQueue& operator=(const CustomQueue& other) {
        if (this != &other) {
            clear();
            QueueNode* current = other.frontNode;
            while (current) {
                enqueue(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    ~CustomQueue() {
        clear();
    }
};

// Custom Time Utility
struct CustomTime {
    int year, month, day, hour, minute;

    static CustomTime getCurrentTime() {
        time_t now = time(0);
        tm ltm;

        if (localtime_s(&ltm, &now) != 0) {
            throw runtime_error("Failed to retrieve local time");
        }

        return {
            1900 + ltm.tm_year,
            1 + ltm.tm_mon,
            ltm.tm_mday,
            ltm.tm_hour,
            ltm.tm_min
        };
    }

    string toString() const {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d %02d:%02d",
            day, month, year, hour, minute);
        return string(buffer);
    }
};

// Structures for enhanced social network features
struct Post {
    string content;
    string authorName;
    CustomTime timestamp;

    string toString() const {
        return "Post by " + authorName + ": " + content +
            "\nTime: " + timestamp.toString();
    }
};

struct Message {
    string sender;
    string content;
    bool isRead;
    CustomTime timestamp;

    string toString() const {
        return "[" + sender + "]: " + content +
            (isRead ? " (Read)" : " (Unread)");
    }
};

struct Notification {
    string content;
    bool isRead;
    CustomTime timestamp;

    string toString() const {
        return content + (isRead ? " (Read)" : " (Unread)");
    }
};
// Forward declaration 
class UserProfile;
class GraphNode;

// Authenticator for enhanced security
class UserAuthenticator {
private:
    bool isValidPassword(const string& password) {
        if (password.length() < 8) {
            return false;
        }
        bool hasLowercase = false;
        bool hasUppercase = false;
        bool hasDigit = false;
        bool hasSpecialChar = false;

        string specialChars = "@$!%*?&";

        for (char ch : password) {
            if (islower(ch)) {
                hasLowercase = true;
            }
            else if (isupper(ch)) {
                hasUppercase = true;
            }
            else if (isdigit(ch)) {
                hasDigit = true;
            }
            else if (specialChars.find(ch) != string::npos) {
                hasSpecialChar = true;
            }
        }
        return hasLowercase && hasUppercase && hasDigit && hasSpecialChar;
    }
public:
    bool validatePassword(const string& password) {
        if (!isValidPassword(password)) {
            cout << "Password must be at least 8 characters long and contain:" << endl;
            cout << "- Uppercase letter" << endl;
            cout << "- Lowercase letter" << endl;
            cout << "- Number" << endl;
            cout << "- Special character (@$!%*?&)" << endl;
            return false;
        }
        return true;
    }
};

// GraphNode class declaration
class GraphNode {
public:
    UserProfile* user;
    GraphNode* next;
    CustomQueue<GraphNode*> connections;
    CustomQueue<GraphNode*> pendingRequests;

    GraphNode(UserProfile* userProfile);
};

// UserProfile class declaration
class UserProfile {
public:
    string name;
    string password;
    string securityQuestion;
    string securityAnswer;
    string city;
    CustomTime lastLogin;

    CustomStack<Post> posts;
    CustomStack<Message> messages;
    CustomQueue<Notification> notifications;
    CustomQueue<UserProfile*> followers;
    CustomQueue<UserProfile*> following;

    UserProfile(string n, string p, string sq, string sa, string c);

    void sendMessage(UserProfile* recipient, const string& content);
    void createPost(const string& content);
    void sendFollowRequest(GraphNode* requesterNode, GraphNode* targetNode);
    void acceptFollowRequest(GraphNode* graphNode, int requestIndex);
    void displayFollowers();
    void displayFollowing();
    void displayTimeline();
    void displayNewsfeed();
    void displayNotifications();
    void displayMessages();
    void displayConnections(GraphNode* graphNode);
    void displayPendingRequests(GraphNode* graphNode);
    string getProfileInfo() const {
        return "Username: " + name + "\nCity: " + city + "\nLast Login: " + lastLogin.toString();
    }
};

// GraphNode constructor definition
GraphNode::GraphNode(UserProfile* userProfile) :
    user(userProfile), next(nullptr) {}

// Social Network Graph Management
class SocialNetworkGraph {
private:
    GraphNode* userGraph;
    CustomQueue<GraphNode*> users;
    UserAuthenticator authenticator;

public:
    SocialNetworkGraph() : userGraph(nullptr) {}

    void addUser(GraphNode* newUserNode) {
        if (!newUserNode) {
            cout << "Error: Attempted to add a null user node." << endl;
            return;
        }
        users.enqueue(newUserNode);
        // Insert at the beginning of the graph
        newUserNode->next = userGraph;
        userGraph = newUserNode;
    }

    GraphNode* findUser(const string& username) {
        GraphNode* current = userGraph;
        while (current) {
            if (current->user->name == username) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void suggestMutualFriends(GraphNode* userNode) {
        cout << "Mutual Friends Suggestions for " << userNode->user->name << ":" << endl;

        GraphNode* current = userGraph;
        while (current) {
            // Skip the current user and existing connections
            if (current != userNode && !isConnected(userNode, current)) {
                int mutualCount = countMutualConnections(userNode, current);
                if (mutualCount > 0) {
                    cout << current->user->name << " (Mutual Connections: " << mutualCount << ")" << endl;
                }
            }
            current = current->next;
        }
    }

    // Breadth-First Search (BFS)
    void bfsTraversal(GraphNode* startNode) {
        if (!startNode) {
            cout << "Error: Start node is null." << endl;
            return;
        }

        CustomQueue<GraphNode*> queue;
        CustomQueue<GraphNode*> visited; // Using a queue for visited nodes

        queue.enqueue(startNode);
        visited.enqueue(startNode);

        cout << "BFS Traversal: ";
        while (!queue.isEmpty()) {
            GraphNode* current = queue.dequeue();
            cout << current->user->name << " ";

            CustomQueue<GraphNode*> connections = current->connections;
            while (!connections.isEmpty()) {
                GraphNode* neighbor = connections.dequeue();
                if (!isVisited(visited, neighbor)) {
                    queue.enqueue(neighbor);
                    visited.enqueue(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS)
    void dfsTraversal(GraphNode* startNode) {
        if (!startNode) {
            cout << "Error: Start node is null." << endl;
            return;
        }

        CustomQueue<GraphNode*> visited; // Using a queue for visited nodes
        cout << "DFS Traversal: ";
        dfsHelper(startNode, visited);
        cout << endl;
    }

private:
    // Helper function for DFS
    void dfsHelper(GraphNode* node, CustomQueue<GraphNode*>& visited) {
        visited.enqueue(node);
        cout << node->user->name << " ";

        CustomQueue<GraphNode*> connections = node->connections;
        while (!connections.isEmpty()) {
            GraphNode* neighbor = connections.dequeue();
            if (!isVisited(visited, neighbor)) {
                dfsHelper(neighbor, visited);
            }
        }
    }

    bool isVisited(CustomQueue<GraphNode*>& visited, GraphNode* node) {
        CustomQueue<GraphNode*> temp = visited; // Make a copy to check without modifying original
        while (!temp.isEmpty()) {
            if (temp.dequeue() == node) {
                return true; // Node is already visited
            }
        }
        return false;
    }

    bool isConnected(GraphNode* node1, GraphNode* node2) {
        CustomQueue<GraphNode*> tempConnections = node1->connections;
        while (!tempConnections.isEmpty()) {
            GraphNode* current = tempConnections.dequeue();
            if (current == node2) {
                return true;
            }
        }
        return false;
    }

    int countMutualConnections(GraphNode* node1, GraphNode* node2) {
        int mutualCount = 0;
        CustomQueue<GraphNode*> tempConn1 = node1->connections;

        while (!tempConn1.isEmpty()) {
            GraphNode* conn1 = tempConn1.dequeue();
            CustomQueue<GraphNode*> tempConn2 = node2->connections;

            while (!tempConn2.isEmpty()) {
                GraphNode* conn2 = tempConn2.dequeue();
                if (conn1 == conn2) {
                    mutualCount++;
                }
            }
        }

        return mutualCount;
    }
};


// Implementing UserProfile methods
UserProfile::UserProfile(string n, string p, string sq, string sa, string c) :
    name(n), password(p),
    securityQuestion(sq),
    securityAnswer(sa), city(c) {}

void UserProfile::sendMessage(UserProfile* recipient, const string& content) {
    Message msg{ name, content, false, CustomTime::getCurrentTime() };
    recipient->messages.push(msg);
    recipient->notifications.enqueue(
        Notification{ "New message from " + name, false, CustomTime::getCurrentTime() }
    );
}

void UserProfile::createPost(const string& content) {
    Post newPost{ content, name, CustomTime::getCurrentTime() };
    posts.push(newPost);
}

void UserProfile::sendFollowRequest(GraphNode* requesterNode, GraphNode* targetNode) {
    targetNode->pendingRequests.enqueue(requesterNode);
    string notification = "Follow request from " + requesterNode->user->name;
    targetNode->user->notifications.enqueue(
        Notification{ notification, false, CustomTime::getCurrentTime() }
    );
}

void UserProfile::acceptFollowRequest(GraphNode* graphNode, int requestIndex) {
    CustomQueue<GraphNode*> tempQueue;
    GraphNode* requestedNode = nullptr;
    int currentIndex = 1;

    // Find the specific request
    while (!graphNode->pendingRequests.isEmpty()) {
        GraphNode* currentRequest = graphNode->pendingRequests.dequeue();
        if (currentIndex == requestIndex) {
            requestedNode = currentRequest;
        }
        else {
            tempQueue.enqueue(currentRequest);
        }
        currentIndex++;
    }

    // Restore pending requests queue
    while (!tempQueue.isEmpty()) {
        graphNode->pendingRequests.enqueue(tempQueue.dequeue());
    }

    // If a valid request was found
    if (requestedNode) {
        // Add connection in both directions
        graphNode->connections.enqueue(requestedNode);
        requestedNode->connections.enqueue(graphNode);

        // Add to followers/following lists
        followers.enqueue(requestedNode->user);
        requestedNode->user->following.enqueue(graphNode->user);

        // Create notifications
        string notification = "Follow request accepted by " + graphNode->user->name;
        requestedNode->user->notifications.enqueue(
            Notification{ notification, false, CustomTime::getCurrentTime() }
        );
    }
}

void UserProfile::displayFollowers() {
    cout << "--- Followers ---" << endl;
    if (followers.isEmpty()) {
        cout << "No followers yet." << endl;
        return;
    }

    int index = 1;
    CustomQueue<UserProfile*> tempFollowers = followers;
    while (!tempFollowers.isEmpty()) {
        UserProfile* current = tempFollowers.dequeue();
        cout << index++ << ". " << current->name << endl;
    }
}

void UserProfile::displayFollowing() {
    cout << "--- Following ---" << endl;
    if (following.isEmpty()) {
        cout << "Not following anyone yet." << endl;
        return;
    }

    int index = 1;
    CustomQueue<UserProfile*> tempFollowing = following;
    while (!tempFollowing.isEmpty()) {
        UserProfile* current = tempFollowing.dequeue();
        cout << index++ << ". " << current->name << endl;
    }
}

void UserProfile::displayTimeline() {
    cout << "--- Timeline ---" << endl;
    if (following.isEmpty()) {
        cout << "Follow some users to see their posts!" << endl;
        return;
    }

    CustomQueue<UserProfile*> tempFollowing = following;
    while (!tempFollowing.isEmpty()) {
        UserProfile* current = tempFollowing.dequeue();
        cout << "Posts by " << current->name << ":" << endl;

        CustomStack<Post> tempPosts = current->posts;
        if (tempPosts.isEmpty()) {
            cout << "No posts yet." << endl;
        }
        else {
            while (!tempPosts.isEmpty()) {
                Post post = tempPosts.pop();
                cout << post.toString() << endl;
            }
        }
    }
}

void UserProfile::displayNewsfeed() {
    cout << "--- Your Posts ---" << endl;
    if (posts.isEmpty()) {
        cout << "No posts yet." << endl;
        return;
    }

    CustomStack<Post> tempPosts = posts;
    while (!tempPosts.isEmpty()) {
        Post post = tempPosts.pop();
        cout << post.toString() << endl;
    }
}

void UserProfile::displayNotifications() {
    cout << "--- Notifications ---" << endl;
    if (notifications.isEmpty()) {
        cout << "No notifications." << endl;
        return;
    }

    CustomQueue<Notification> tempNotifications = notifications;
    int index = 1;
    while (!tempNotifications.isEmpty()) {
        Notification notification = tempNotifications.dequeue();
        cout << index++ << ". " << notification.toString() << endl;
    }
}

void UserProfile::displayMessages() {
    cout << "--- Messages ---" << endl;
    if (messages.isEmpty()) {
        cout << "No messages." << endl;
        return;
    }

    CustomStack<Message> tempMessages = messages;
    int index = 1;
    while (!tempMessages.isEmpty()) {
        Message message = tempMessages.pop();
        cout << index++ << ". " << message.toString() << endl;
    }
}

void UserProfile::displayConnections(GraphNode* graphNode) {
    cout << "Connections for " << graphNode->user->name << ":" << endl;
    CustomQueue<GraphNode*> tempConnections = graphNode->connections;
    int index = 1;
    while (!tempConnections.isEmpty()) {
        GraphNode* current = tempConnections.dequeue();
        cout << index++ << ". " << current->user->name << endl;
    }
}

void UserProfile::displayPendingRequests(GraphNode* graphNode) {
    cout << "Pending Follow Requests for " << graphNode->user->name << ":" << endl;
    CustomQueue<GraphNode*> tempPendingRequests = graphNode->pendingRequests;
    int index = 1;
    while (!tempPendingRequests.isEmpty()) {
        GraphNode* current = tempPendingRequests.dequeue();
        cout << index++ << ". " << current->user->name << endl;
    }
}

class BSTNode {
public:
    UserProfile* user;
    BSTNode* left;
    BSTNode* right;

    BSTNode(UserProfile* userProfile);
};

class UserSearchBST {
private:
    BSTNode* root;
    BSTNode* insertRecursive(BSTNode* node, UserProfile* user);
    UserProfile* searchRecursive(BSTNode* node, const string& username) const;
    void inorderTraversalRecursive(BSTNode* node) const;
    void deleteTreeRecursive(BSTNode* node);

public:
    UserSearchBST();
    ~UserSearchBST();

    void addUser(UserProfile* user);
    UserProfile* findUser(const string& username) const;
    void displayAllUsers() const;
};

// BSTNode constructor
BSTNode::BSTNode(UserProfile* userProfile) :
    user(userProfile), left(nullptr), right(nullptr) {}

// UserSearchBST constructor
UserSearchBST::UserSearchBST() : root(nullptr) {}

// UserSearchBST destructor
UserSearchBST::~UserSearchBST() {
    deleteTreeRecursive(root);
}

// Recursive insert implementation
BSTNode* UserSearchBST::insertRecursive(BSTNode* node, UserProfile* user) {
    // Standard BST insertion
    if (node == nullptr) {
        return new BSTNode(user);
    }

    // Compare usernames to determine insertion path
    if (user->name < node->user->name) {
        node->left = insertRecursive(node->left, user);
    }
    else if (user->name > node->user->name) {
        node->right = insertRecursive(node->right, user);
    }
    else {
        // Username already exists
        cout << "User '" << user->name << "' already exists in the tree." << endl;
        return node;
    }

    return node;
}

// Recursive search implementation
UserProfile* UserSearchBST::searchRecursive(BSTNode* node, const string& username) const {
    // Base cases
    if (node == nullptr) {
        return nullptr;
    }

    // If username matches
    if (node->user->name == username) {
        return node->user;
    }

    // Recursive search in left or right subtree
    if (username < node->user->name) {
        return searchRecursive(node->left, username);
    }
    else {
        return searchRecursive(node->right, username);
    }
}

// Inorder traversal implementation
void UserSearchBST::inorderTraversalRecursive(BSTNode* node) const {
    if (node == nullptr) {
        return;
    }

    // Left subtree
    inorderTraversalRecursive(node->left);

    // Current node
    if (node->user) {
        cout << node->user->getProfileInfo() << "\n---\n";
    }

    // Right subtree
    inorderTraversalRecursive(node->right);
}

// Tree deletion implementation
void UserSearchBST::deleteTreeRecursive(BSTNode* node) {
    if (node == nullptr) {
        return;
    }

    // Recursively delete left and right subtrees
    deleteTreeRecursive(node->left);
    deleteTreeRecursive(node->right);

    // Delete the current node
    delete node;
}

// Public method implementations
void UserSearchBST::addUser(UserProfile* user) {
    root = insertRecursive(root, user);
}

UserProfile* UserSearchBST::findUser(const string& username) const {
    return searchRecursive(root, username);
}

void UserSearchBST::displayAllUsers() const {
    cout << "--- User List ---\n";
    inorderTraversalRecursive(root);
    cout << "-----------------\n";
}

class SocialNetworkApp {
private:
    SocialNetworkGraph socialNetwork;
    UserSearchBST userSearch;
    UserAuthenticator authenticator;
    GraphNode* currentUser;

    void searchUser() {
        string username;
        cout << "Enter username to search: ";
        cin >> username;

        UserProfile* user = userSearch.findUser(username);
        if (user) {
            cout << "User found:\n" << user->getProfileInfo() << "\n";
        }
        else {
            cout << "User not found.\n";
        }
    }

    void displayMainMenu() {
        cout << "\n--- Social Network Menu ---" << endl;
        cout << "1. Signup" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void displayLoggedInMenu() {
        cout << "\n--- Logged In Menu ---" << endl;
        cout << "1. Follow Requests" << endl;
        cout << "2. Send Follow Request" << endl;
        cout << "3. Create Post" << endl;
        cout << "4. View Newsfeed" << endl;
        cout << "5. View Notifications" << endl;
        cout << "6. Messaging" << endl;
        cout << "7. Search Users" << endl;
        cout << "8. View Followers" << endl;
        cout << "9. Logout" << endl;
        cout << "Enter your choice: ";
    }

    UserProfile* createUserProfile() {
        string name, password, securityQuestion, securityAnswer, city;

        // Check for unique username
        while (true) {
            cout << "Enter username: ";
            getline(cin, name);

            if (socialNetwork.findUser(name) == nullptr) {
                break;
            }
            cout << "Username already exists. Please choose another." << endl;
        }

        // Password validation
        while (true) {
            cout << "Enter password: ";
            getline(cin, password);

            if (authenticator.validatePassword(password)) {
                break;
            }
        }
        cout << "Enter city: ";
        getline(cin, city);

        cout << "Enter security question: ";
        getline(cin, securityQuestion);

        cout << "Enter security answer: ";
        getline(cin, securityAnswer);

        return new UserProfile(name, password, securityQuestion, securityAnswer, city);
    }

    void signupProcess() {
        UserProfile* newUser = createUserProfile();
        GraphNode* newUserNode = new GraphNode(newUser);
        socialNetwork.addUser(newUserNode);
        cout << "Signup successful!" << endl;
    }

    bool loginProcess() {
        string username, password;
        cout << "Enter username: ";
        getline(cin, username);

        GraphNode* userNode = socialNetwork.findUser(username);
        if (!userNode) {
            cout << "User not found." << endl;
            return false;
        }

        int attempts = 3;
        while (attempts > 0) {
            cout << "Enter password: ";
            getline(cin, password);

            if (userNode->user->password == password) {
                currentUser = userNode;
                cout << "Login successful!" << endl;
                return true;
            }

            attempts--;
            cout << "Incorrect password. " << attempts << " attempts remaining." << endl;
        }

        // Password reset option
        if (attempts == 0) {
            string securityAnswer;
            cout << "Security Question: " << userNode->user->securityQuestion << endl;
            cout << "Enter security answer: ";
            getline(cin, securityAnswer);

            if (securityAnswer == userNode->user->securityAnswer) {
                string newPassword;
                while (true) {
                    cout << "Enter new password: ";
                    getline(cin, newPassword);

                    if (authenticator.validatePassword(newPassword)) {
                        userNode->user->password = newPassword;
                        cout << "Password reset successful!" << endl;
                        return false;
                    }
                }
            }
            else {
                cout << "Incorrect security answer. Password reset failed." << endl;
            }
        }

        return false;
    }

    void followRequestsMenu() {
        while (true) {
            cout << "\n--- Follow Requests Menu ---" << endl;
            cout << "1. View Pending Requests" << endl;
            cout << "2. Accept Requests" << endl;
            cout << "3. Back to Main Menu" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                currentUser->user->displayPendingRequests(currentUser);
                break;
            case 2: {
                int requestIndex;
                cout << "Enter request number to accept: ";
                cin >> requestIndex;
                cin.ignore();
                currentUser->user->acceptFollowRequest(currentUser, requestIndex);
                break;
            }
            case 3:
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void sendFollowRequest() {
        string targetUsername;
        cout << "Enter username to follow: ";
        getline(cin, targetUsername);

        GraphNode* targetNode = socialNetwork.findUser(targetUsername);
        if (targetNode) {
            currentUser->user->sendFollowRequest(currentUser, targetNode);
            cout << "Follow request sent to " << targetUsername << endl;
        }
        else {
            cout << "User not found." << endl;
        }
    }

    void messagingMenu() {
        string recipientUsername, message;
        cout << "Enter recipient username: ";
        getline(cin, recipientUsername);

        GraphNode* recipientNode = socialNetwork.findUser(recipientUsername);
        if (recipientNode) {
            cout << "Enter message: ";
            getline(cin, message);
            currentUser->user->sendMessage(recipientNode->user, message);
            cout << "Message sent successfully!" << endl;
        }
        else {
            cout << "Recipient not found." << endl;
        }
    }


public:
    SocialNetworkApp() : currentUser(nullptr) {}

    void run() {
        int mainChoice;
        bool isRunning = true;

        while (isRunning) {
            if (currentUser == nullptr) {
                displayMainMenu();
                cin >> mainChoice;
                cin.ignore();

                switch (mainChoice) {
                case 1:
                    signupProcess();
                    break;
                case 2:
                    loginProcess();
                    break;
                case 3:
                    isRunning = false;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            }
            else {
                displayLoggedInMenu();
                int loggedInChoice;
                cin >> loggedInChoice;
                cin.ignore();

                switch (loggedInChoice) {
                case 1:
                    followRequestsMenu();
                    break;
                case 2:
                    sendFollowRequest();
                    break;
                case 3: {
                    string postContent;
                    cout << "Enter post content: ";
                    getline(cin, postContent);
                    currentUser->user->createPost(postContent);
                    break;
                }
                case 4:
                    currentUser->user->displayTimeline();
                    break;
                case 5:
                    currentUser->user->displayNotifications();
                    break;
                case 6:
                    messagingMenu();
                    break;
                case 7: {
                    searchUser();
                    break;
                }
                case 8:
                    currentUser->user->displayFollowers();
                    break;
                case 9:
                    currentUser = nullptr;
                    cout << "Logged out successfully!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            }
        }
    }
};

int main() {
    SocialNetworkApp app;
    app.run();
    return 0;
}

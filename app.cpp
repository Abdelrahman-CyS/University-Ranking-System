#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono> // Include the <chrono> header for time measurement
#include <cstdlib> // For strtod and strtol functions
#include <algorithm>
#include <ctime>
#include <unordered_map>

struct FeedbackNode {
    std::string customerName;
    std::string feedback;
    std::string reply;
    std::string feedbackTime;
    std::string replyTime;
    FeedbackNode* next;
    FeedbackNode* prev;

    FeedbackNode(const std::string& name, const std::string& fb)
        : customerName(name), feedback(fb), reply(""), feedbackTime(""), replyTime(""), next(nullptr), prev(nullptr) {
        time_t currentTime = time(nullptr);
        feedbackTime = std::asctime(std::localtime(&currentTime));
    }
};

class FeedbackList {
private:
    FeedbackNode* head;
    FeedbackNode* tail;
    FeedbackNode* currentFeedback;
    FeedbackNode* prevFeedback;

public:
    FeedbackList()
        : head(nullptr), tail(nullptr), currentFeedback(nullptr), prevFeedback(nullptr) {}

    void addFeedback(const std::string& name, const std::string& fb) {
        FeedbackNode* newNode = new FeedbackNode(name, fb);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        std::cout << "Feedback added successfully.\n" << std::endl;
    }

    void printFeedback() const {
        FeedbackNode* current = head;

        if (current == nullptr) {
            std::cout << "No feedback available." << std::endl;
        } else {
            std::vector<FeedbackNode*> feedbackVec; // Vector to store feedback nodes
            while (current != nullptr) {
                feedbackVec.push_back(current); // Store current feedback node in the vector
                current = current->next; // Move to the next feedback node
            }

            // Sort the feedback vector based on the reply time in descending order
            std::sort(feedbackVec.begin(), feedbackVec.end(), [](const FeedbackNode* a, const FeedbackNode* b) {
                return a->replyTime > b->replyTime;
            });

            std::cout << "\nCustomer Feedback (Sorted by Latest Reply Time):" << std::endl;
            for (const auto& feedbackNode : feedbackVec) {
                std::cout << "Customer Name: " << feedbackNode->customerName << std::endl;
                std::cout << "Feedback: " << feedbackNode->feedback << std::endl;
                std::cout << "Feedback Time: " << feedbackNode->feedbackTime;
                if (!feedbackNode->reply.empty()) {
                    std::cout << "Reply: " << feedbackNode->reply << std::endl;
                    std::cout << "Reply Time: " << feedbackNode->replyTime << std::endl;
                } else {
                    std::cout << "No reply yet." << std::endl;
                }
                std::cout << "------------------------\n" << std::endl;
            }
        }
    }

    void replyFeedback() {
        std::string customerName, reply;
        std::cin.ignore();
        std::cout << "Enter customer name: ";
        std::getline(std::cin, customerName);

        FeedbackNode* current = head;
        while (current != nullptr) {
            if (current->customerName == customerName) {
                std::cout << "Enter reply: ";
                std::getline(std::cin, reply);
                current->reply = reply;

                time_t currentTime = time(nullptr);
                current->replyTime = std::asctime(std::localtime(&currentTime));

                std::cout << "Reply sent successfully." << std::endl;
                return;
            }
            current = current->next;
        }

        std::cout << "Customer not found." << std::endl;
    }

    void navigateFeedback(const std::string& direction) {
        if (currentFeedback == nullptr) {
            if (direction == "next") {
                currentFeedback = head;
            } else if (direction == "prev") {
                currentFeedback = tail;
            } else {
                std::cout << "Invalid direction. Please enter either 'next' or 'prev'." << std::endl;
                return;
            }
        } else {
            if (direction == "next") {
                if (currentFeedback->next != nullptr) {
                    currentFeedback = currentFeedback->next;
                } else {
                    std::cout << "You have reached the end of the feedback list." << std::endl;
                    return;
                }
            } else if (direction == "prev") {
                if (currentFeedback->prev != nullptr) {
                    currentFeedback = currentFeedback->prev;
                } else {
                    std::cout << "You have reached the beginning of the feedback list." << std::endl;
                    return;
                }
            } else {
                std::cout << "Invalid direction. Please enter either 'next' or 'prev'." << std::endl;
                return;
            }
        }

        std::cout << "Customer Name: " << currentFeedback->customerName << std::endl;
        std::cout << "Feedback: " << currentFeedback->feedback << std::endl;
        std::cout << "Feedback Time: " << currentFeedback->feedbackTime;
        if (!currentFeedback->reply.empty()) {
            std::cout << "Reply: " << currentFeedback->reply << std::endl;
            std::cout << "Reply Time: " << currentFeedback->replyTime << std::endl;
        } else {
            std::cout << "No reply yet." << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }
};


using namespace std;
using namespace std::chrono;

double convertToDouble(const std::string& str) {
    try {
        return std::strtod(str.c_str(), nullptr);
    } catch (const std::invalid_argument&) {
        // Error occurred while converting string to double
        return 0.0; // Return a default value or handle the error as needed
    }
}

int convertToInt(const std::string& str) {
    try {
        return std::strtol(str.c_str(), nullptr, 10);
    } catch (const std::invalid_argument&) {
        // Error occurred while converting string to integer
        return 0; // Return a default value or handle the error as needed
    }
}

// Assume the Feedback class to store user feedback
class Feedback {
public:
    std::string username;
    std::string universityName;
    std::string text;
    std::string date;
};

// Assume the FeedbackReply class to store feedback replies
class FeedbackReply {
public:
    std::string username; // Username of the customer who submitted the feedback
    std::string date;     // Date of the reply
    std::string text;     // Reply text
};

class FeedbackManager {
private:
    std::vector<Feedback> feedbacks;
    std::vector<FeedbackReply> replies;

public:
    void addFeedback(const Feedback& feedback) {
        feedbacks.push_back(feedback);
    }

    void addFeedbackReply(const FeedbackReply& reply) {
        replies.push_back(reply);
    }

    std::vector<Feedback> getFeedbacksForUser(const std::string& username) const {
        std::vector<Feedback> userFeedbacks;
        for (const Feedback& feedback : feedbacks) {
            if (feedback.username == username) {
                userFeedbacks.push_back(feedback);
            }
        }
        return userFeedbacks;
    }

    std::vector<FeedbackReply> getFeedbackReplies(const std::string& username) {
        std::vector<FeedbackReply> userReplies;
        for (const FeedbackReply& reply : replies) {
            if (reply.username == username) {
                userReplies.push_back(reply);
            }
        }
        return userReplies;
    }

    const std::vector<Feedback>& getAllFeedbacks() const {
        return feedbacks;
    }
};


// University structure
struct University {
    int Rank;
    string institution;
    string locationCode;
    string location;
    double arScore;
    int arRank;
    double erScore;
    int erRank;
    double fsrScore;
    int fsrRank;
    double cpfScore;
    int cpfRank;
    double ifrScore;
    int ifrRank;
    double isrScore;
    int isrRank;
    double irnScore;
    int irnRank;
    double gerScore;
    int gerRank;
    double scoreScaled;
};

#include <string>

struct Customer {
    int id;
    std::string name;
    std::string username;
    std::string password;
    std::string status;
    std::string fullName;
    std::string favoriteUniversity;
    int age;
    bool isActive;
    bool cityStatus;
    std::vector<University> favorites;
    FeedbackManager feedbackManager;
    Customer* next;

    Customer() : next(nullptr), cityStatus(true) {}

    Customer(int id, const std::string& name, const std::string& username, const std::string& password, const std::string& status, int age, bool isActive)
        : id(id), name(name), username(username), password(password), status(status), age(age), isActive(isActive), next(nullptr) {}
};

class LinkedList {
public:
    struct ListNode {
        University university;
        ListNode* next;
        std::string username;
        std::string password;
        Customer customer;
    };

    ListNode* getHead() const {
        return head;
    }

    ListNode* getUserNodeByUsername(const std::string& username) const {
        if (usersByUsername.find(username) != usersByUsername.end()) {
            return usersByUsername.at(username);
        }
        return nullptr;
    }

    std::vector<Feedback> getAllFeedbacks() const {
        std::vector<Feedback> allFeedbacks;

        ListNode* current = head;
        while (current != nullptr) {
            std::vector<Feedback> customerFeedbacks = current->customer.feedbackManager.getAllFeedbacks();
            allFeedbacks.insert(allFeedbacks.end(), customerFeedbacks.begin(), customerFeedbacks.end());
            current = current->next;
        }

        return allFeedbacks;
    }

    std::vector<Feedback> getFeedbacksForCustomer(Customer& customer) const {
        std::vector<Feedback> feedbacks;
        // Assuming each Customer has a FeedbackManager and it has a method to return all feedbacks
        feedbacks = customer.feedbackManager.getAllFeedbacks();
        return feedbacks;
    }

    const std::vector<Feedback>& getFeedbacks() const {
        return feedbackManager.getAllFeedbacks();
    }

    LinkedList() : head(nullptr), lastCustomerId(0) {}

    const std::unordered_map<std::string, ListNode*>& getUsersByUsername() const {
        return usersByUsername;
    }

    void addUser(const std::string& username, const std::string& password, const std::string& name, int age) {
        ListNode* existingUser = getUserNodeByUsername(username);
        if (existingUser != nullptr) {
            std::cout << "Username already exists. Please choose a different username.\n";
            return;
        }

        ListNode* newNode = new ListNode;
        newNode->username = username;
        newNode->password = password;
        newNode->customer = Customer(++lastCustomerId, name, username, password, "Active", age, true);
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            ListNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        usersByUsername[username] = newNode;
    }

    void displayUsers() const {
        ListNode* current = head;
        std::cout << "----------------------------------------\n";
        std::cout << "Registered Users' Details:\n";
        std::cout << "----------------------------------------\n";
        int count = 1;
        while (current != nullptr) {
            std::cout << "Customer ID: " << count << std::endl;
            std::cout << "Username: " << current->username << ", Password: " << current->password << std::endl;
            std::cout << "Customer Name: " << current->customer.name << std::endl;
            std::cout << "Customer Age: " << current->customer.age << std::endl;
            std::cout << "Customer Status: " << current->customer.status << std::endl;
            std::cout << "City Status: " << (current->customer.cityStatus ? "True" : "False") << std::endl;
            std::cout << "----------------------------------------\n";
            current = current->next;
            count++;
        }
    }

    // Display all customers in the linked list
    void displayCustomers() const {
        ListNode* current = head;
        while (current != nullptr) {
            std::cout << "Customer Name: " << current->customer.name << std::endl;
            std::cout << "Customer Username: " << current->username << std::endl;
            std::cout << "Customer Password: " << current->password << std::endl;
            std::cout << "Customer Age: " << current->customer.age << std::endl;
            std::cout << "Customer Status: " << current->customer.status << std::endl;
            std::cout << "City Status: " << (current->customer.cityStatus ? "True" : "False") << std::endl;  // Display the city status
            // Display other customer details as needed
            std::cout << "-----------------------------" << std::endl;
            current = current->next;
        }
    }

    // View favorite universities
    void displayFavoriteUniversities(const std::string& username) const {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->username == username) {
                std::cout << "----------------------------------------\n";
                std::cout << "   Favorite Universities for User: " << username << "\n";
                std::cout << "----------------------------------------\n";
                if (current->customer.favorites.empty()) {
                    std::cout << "No favorite universities found.\n";
                } else {
                    int index = 1;
                    for (const University& favorite : current->customer.favorites) {
                        std::cout << "University " << index << ":\n";
                        std::cout << "    Name: " << favorite.institution << "\n";
                        std::cout << "    Location: " << favorite.location << "\n";
                        std::cout << "    Ranking: " << favorite.Rank << "\n";
                        std::cout << "----------------------------------------\n";
                        index++;
                    }
                }
                return;
            }
            current = current->next;
        }
        std::cout << "User not found.\n";
    }

    // Customer login
    bool customerLogin(const std::string& username, const std::string& password) {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->username == username && current->password == password) {
                return true;  // Login successful
            }
            current = current->next;
        }
        return false;  // Login failed
    }

    // Add a favorite university to the linked list
    void addFavoriteUniversity(const std::string& username, const University& university) {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->username == username) {
                current->customer.favorites.push_back(university);
                std::cout << "University added to favorites.\n";
                return;
            }
            current = current->next;
        }
        std::cout << "User not found.\n";
    }

    void addFeedback(const std::string& username, const Feedback& feedback) {
        ListNode* current = getUserNodeByUsername(username);
        if (current != nullptr) {
            current->customer.feedbackManager.addFeedback(feedback);
            std::cout << "Feedback added.\n";
            return;
        }
        std::cout << "User not found.\n";
    }

    void removeInactiveUsers() {
        ListNode* current = head;
        ListNode* prev = nullptr;
        while (current != nullptr) {
            if (current->customer.status != "Active") {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                usersByUsername.erase(current->username);
                ListNode* toDelete = current;
                if (prev != nullptr) {
                    current = prev->next;
                } else {
                    current = head;
                }
                delete toDelete;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }


private:
    FeedbackManager feedbackManager;
    ListNode* head;
    int lastCustomerId;
    std::unordered_map<std::string, ListNode*> usersByUsername;
};


// Hash Table class
class HashTable {
private:
    struct HashNode {
        string username;
        string password;
        HashNode* next;
    };

    static const int TABLE_SIZE = 10;
    vector<HashNode*> table;

public:
    HashTable() {
        table.resize(TABLE_SIZE, nullptr);
    }

    // Hash function
    int hash(const string& key) const {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % TABLE_SIZE;
    }

};


// Function to display all universities
void displayAllUniversities(const std::vector<University>& universities) {
    // Calculate the width of each column
    const int columnWidth = 12;

    std::cout << std::left;
    std::cout << std::setw(5) << "Rank" << " | " << std::setw(columnWidth) << "Institution" << " | " << std::setw(columnWidth) << "Location Code"
              << " | " << std::setw(columnWidth) << "Location" << " | " << std::setw(columnWidth) << "AR Score" << " | " << std::setw(columnWidth) << "AR Rank"
              << " | " << std::setw(columnWidth) << "ER Score" << " | " << std::setw(columnWidth) << "ER Rank" << " | " << std::setw(columnWidth) << "FSR Score"
              << " | " << std::setw(columnWidth) << "FSR Rank" << " | " << std::setw(columnWidth) << "CPF Score" << " | " << std::setw(columnWidth) << "CPF Rank"
              << " | " << std::setw(columnWidth) << "IFR Score" << " | " << std::setw(columnWidth) << "IFR Rank" << " | " << std::setw(columnWidth) << "ISR Score"
              << " | " << std::setw(columnWidth) << "ISR Rank" << " | " << std::setw(columnWidth) << "IRN Score" << " | " << std::setw(columnWidth) << "IRN Rank"
              << " | " << std::setw(columnWidth) << "GER Score" << " | " << std::setw(columnWidth) << "GER Rank" << " | " << std::setw(columnWidth) << "Scaled Score"
              << std::endl;

    std::cout << std::setfill('-') << std::setw(5 + (columnWidth * 17 + 3 * 16)) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (const auto& uni : universities) {
        std::cout << std::setw(5) << uni.Rank << " | " << std::setw(columnWidth) << uni.institution << " | " << std::setw(columnWidth) << uni.locationCode
                  << " | " << std::setw(columnWidth) << uni.location << std::fixed << std::setprecision(2) << " | " << std::setw(columnWidth) << uni.arScore
                  << " | " << std::setw(columnWidth) << uni.arRank << " | " << std::setw(columnWidth) << uni.erScore << " | " << std::setw(columnWidth) << uni.erRank
                  << " | " << std::setw(columnWidth) << uni.fsrScore << " | " << std::setw(columnWidth) << uni.fsrRank << " | " << std::setw(columnWidth) << uni.cpfScore
                  << " | " << std::setw(columnWidth) << uni.cpfRank << " | " << std::setw(columnWidth) << uni.ifrScore << " | " << std::setw(columnWidth) << uni.ifrRank
                  << " | " << std::setw(columnWidth) << uni.isrScore << " | " << std::setw(columnWidth) << uni.isrRank << " | " << std::setw(columnWidth) << uni.irnScore
                  << " | " << std::setw(columnWidth) << uni.irnRank << " | " << std::setw(columnWidth) << uni.gerScore << " | " << std::setw(columnWidth) << uni.gerRank
                  << " | " << std::setw(columnWidth) << uni.scoreScaled << std::endl;
    }
}


// Binary Search Tree class
class BinarySearchTree {
private:
    struct TreeNode {
        University data;
        TreeNode* left;
        TreeNode* right;
    };

    TreeNode* root;

public:
    BinarySearchTree() : root(nullptr) {}

    // Insert a university into the BST
    void insertUniversity(const University& university) {
        TreeNode* newNode = new TreeNode;
        newNode->data = university;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (root == nullptr) {
            root = newNode;
        } else {
            TreeNode* current = root;
            while (true) {
                if (university.institution < current->data.institution) {
                    if (current->left == nullptr) {
                        current->left = newNode;
                        break;
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = newNode;
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }
    }

    // Display all universities in the BST
    void displayUniversities() const {
        displayInOrder(root);
    }

    // Perform binary search and return the index of the found university
    int binarySearch(const std::vector<University>& universities, const std::string& searchKey) const {
        return binarySearchHelper(universities, searchKey, 0, universities.size() - 1);
    }

private:
    // Display universities in in-order traversal
    void displayInOrder(TreeNode* node) const {
        if (node != nullptr) {
            displayInOrder(node->left);
            cout << "Rank: " << node->data.Rank << ", Institution: " << node->data.institution << ", Location: " << node->data.location << endl;
            displayInOrder(node->right);
        }
    }

    // Binary search helper function
    int binarySearchHelper(const std::vector<University>& universities, const std::string& searchKey, int left, int right) const {
        if (left > right) {
            return -1;  // Not found
        }

        int mid = left + (right - left) / 2;
        if (universities[mid].institution == searchKey) {
            return mid;  // Found at mid index
        } else if (universities[mid].institution < searchKey) {
            return binarySearchHelper(universities, searchKey, mid + 1, right);
        } else {
            return binarySearchHelper(universities, searchKey, left, mid - 1);
        }
    }
};

// Base sort algorithm class
class SortAlgorithm {
public:
    virtual void sort(vector<University>& universities) = 0;
};

// Bubble Sort algorithm
class BubbleSort : public SortAlgorithm {
public:
    void sort(vector<University>& universities) override {
        int n = universities.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (universities[j].institution > universities[j + 1].institution) {
                    swap(universities[j], universities[j + 1]);
                }
            }
        }
    }
};

// Quick Sort algorithm
class QuickSort : public SortAlgorithm {
public:
    void sort(vector<University>& universities) override {
        quickSort(universities, 0, universities.size() - 1);
    }

private:
    void quickSort(vector<University>& universities, int low, int high) {
        if (low < high) {
            int pivot = partition(universities, low, high);
            quickSort(universities, low, pivot - 1);
            quickSort(universities, pivot + 1, high);
        }
    }

    int partition(vector<University>& universities, int low, int high) {
        University pivot = universities[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (universities[j].institution < pivot.institution) {
                i++;
                swap(universities[i], universities[j]);
            }
        }
        swap(universities[i + 1], universities[high]);
        return i + 1;
    }
};

// Base search algorithm class
class SearchAlgorithm {
public:
    virtual int search(std::vector<University>& universities, const std::string& key) = 0;
    virtual ~SearchAlgorithm() {}
};

// Linear Search algorithm
class LinearSearch : public SearchAlgorithm {
public:
    int search(std::vector<University>& universities, const std::string& key) override {
        for (int i = 0; i < universities.size(); i++) {
            if (std::to_string(universities[i].Rank) == key) {
                return i;
            }
        }
        return -1;
    }
};

// Binary Search algorithm
class BinarySearch : public SearchAlgorithm {
public:
    int search(std::vector<University>& universities, const std::string& key) override {
        int rank = std::stoi(key);

        // Sort the universities by rank in ascending order
        std::sort(universities.begin(), universities.end(), [](const University& u1, const University& u2) {
            return u1.Rank < u2.Rank;
        });

        // Perform binary search
        int low = 0;
        int high = universities.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (universities[mid].Rank == rank) {
                return mid;
            } else if (universities[mid].Rank < rank) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return -1; // Return -1 if the key is not found
    }
};



// Read university information from CSV file
// Function to parse CSV file and return vector of University objects
std::vector<University> readUniversitiesFromCSV(const std::string& filename) {
    std::vector<University> universities;

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl;
        return universities;
    }

    std::string line;
    std::getline(file, line); // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string data;

        University university;
        // Read data from CSV line and assign to University fields
        std::getline(iss, data, ',');
        university.Rank = convertToInt(data);
        std::getline(iss, university.institution, ',');
        std::getline(iss, university.locationCode, ',');
        std::getline(iss, university.location, ',');

        // Convert score and rank values with error handling
        std::getline(iss, data, ',');
        university.arScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.arRank = convertToInt(data);
        std::getline(iss, data, ',');
        university.erScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.erRank = convertToInt(data);
        std::getline(iss, data, ',');
        university.fsrScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.fsrRank = convertToInt(data);
        std::getline(iss, data, ',');
        university.cpfScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.cpfRank = convertToInt(data);
        std::getline(iss, data, ',');
        university.ifrScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.ifrRank = convertToInt(data);
        std::getline(iss, data, ',');
        university.isrScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.isrRank = convertToInt(data);
        std::getline(iss, data, ',');
        university.irnScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.irnRank = convertToInt(data);
        std::getline(iss, data, ',');
        university.gerScore = convertToDouble(data);
        std::getline(iss, data, ',');
        university.gerRank = convertToInt(data);
        std::getline(iss, data);
        university.scoreScaled = convertToDouble(data);

        universities.push_back(university);
    }

    file.close();

    return universities;
}


std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_now), "%Y-%m-%d %X");
    return ss.str();
}

bool isAdminLogin(const std::string& username, const std::string& password) {
    return (username == "admin" && password == "admin123");
}


int main() {
    FeedbackList feedbackList;
    LinkedList users;
    HashTable userTable;
    BinarySearchTree universityTree;
    vector<University> universities;
    string customerUsername, customerPassword;
    FeedbackManager feedbackManager;
    QuickSort quickSort;
    quickSort.sort(universities);
    std::string loggedInUsername; 
    Customer customer;


    std::string name, password, feedback;
    std::string username, password_admin, customerName;

    // Read universities from CSV file
    universities = readUniversitiesFromCSV("universities.csv");

    // Verify if universities are loaded
    if (universities.empty()) {
        std::cout << "No universities found in the dataset." << endl;
        return 0;
    } else {
        std::cout << "Total universities loaded: " << universities.size() << endl;
    }

    int mainChoice;
    do {
        std::cout << "\n----------------------------------------\n";
        std::cout << "           MAIN MENU                    \n";
        std::cout << "----------------------------------------\n";
        std::cout << "1. Display All Universities\n";
        std::cout << "2. Sort university\n";
        std::cout << "3. Search University\n";
        std::cout << "4. Login as a Customer\n";
        std::cout << "5. Login as an Admin\n";
        std::cout << "6. Register\n";
        std::cout << "7. Exit\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Enter your choice : ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                std::cout << "All Universities:\n";
                displayAllUniversities(universities);
                break;
            case 2: {
                int sortChoice;
                cout << "========================================\n";
                cout << "          Sorting Universities\n";
                cout << "========================================\n";
                cout << "1. Bubble Sort" << endl;
                cout << "2. Quick Sort" << endl;
                cout << "----------------------------------------\n";
                cout << "Enter your choice: ";
                cin >> sortChoice;

                vector<University> universitiesCopy = universities; // Moved outside the switch statement

                switch (sortChoice) {
                    case 1: {
                        // Perform bubble sort by university name in ascending order
                        SortAlgorithm* bubbleSort = new BubbleSort;

                        auto start = std::chrono::steady_clock::now();  // Start measuring time
                        bubbleSort->sort(universitiesCopy);
                        auto end = std::chrono::steady_clock::now();  // End measuring time

                        std::cout << "\nUniversities sorted using Bubble Sort (Ascending Order):\n";
                        displayAllUniversities(universitiesCopy);

                        // Calculate and display the execution time
                        std::chrono::duration<double> elapsedTime = end - start;
                        double seconds = elapsedTime.count();

                        std::cout << "\n";
                        std::cout << "***************************************" << std::endl;
                        std::cout << "* \033[1;33mExecution time: ";

                        if (seconds >= 1.0) {
                            std::cout << std::fixed << std::setprecision(2) << seconds << " seconds\033[0m *" << std::endl;
                        } else {
                            double milliseconds = seconds * 1000.0;
                            std::cout << std::fixed << std::setprecision(2) << milliseconds << " milliseconds\033[0m *" << std::endl;
                        }

                        std::cout << "***************************************" << std::endl;

                        delete bubbleSort;
                        break;
                    }

                    case 2: {
                        // Perform quick sort by university name in ascending order
                        SortAlgorithm* quickSort = new QuickSort;

                        auto start = std::chrono::steady_clock::now();  // Start measuring time
                        quickSort->sort(universitiesCopy);
                        auto end = std::chrono::steady_clock::now();  // End measuring time

                        std::cout << "\nUniversities sorted using Quick Sort (Ascending Order):\n";
                        displayAllUniversities(universitiesCopy);

                        // Calculate and display the execution time
                        std::chrono::duration<double> elapsedTime = end - start;
                        double seconds = elapsedTime.count();

                        std::cout << "\n";
                        std::cout << "***************************************" << std::endl;
                        std::cout << "* \033[1;33mExecution time: ";

                        if (seconds >= 1.0) {
                            std::cout << std::fixed << std::setprecision(2) << seconds << " seconds\033[0m *" << std::endl;
                        } else {
                            double milliseconds = seconds * 1000.0;
                            std::cout << std::fixed << std::setprecision(2) << milliseconds << " milliseconds\033[0m *" << std::endl;
                        }

                        std::cout << "***************************************" << std::endl;

                        delete quickSort;
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }

            case 3: {
                int searchChoice;
                cout << "========================================\n";
                cout << "          Searching Universities\n";
                cout << "========================================\n";
                cout << "1. Linear Search" << endl;
                cout << "2. Binary Search" << endl;
                cout << "----------------------------------------\n";
                cout << "Enter your choice: ";
                cin >> searchChoice;

                string searchKey;
                cout << "Enter the rank of the university to search: ";
                cin.ignore();
                getline(cin, searchKey);

                int searchIndex = -1;

                switch (searchChoice) {
                    case 1: {
                        // Perform linear search
                        SearchAlgorithm* linearSearch = new LinearSearch;
                        searchIndex = linearSearch->search(universities, searchKey);
                        delete linearSearch;
                        break;
                    }
                    case 2: {
                        SearchAlgorithm* binarySearch = new BinarySearch;
                        searchIndex = binarySearch->search(universities, searchKey);
                        delete binarySearch;
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }

                if (searchIndex != -1) {
                    // University found, display the details
                    const University& uni = universities[searchIndex];
                    cout << "\nUniversity found:\n";
                    cout << "================================================================\n";
                    cout << "\033[1;33mRank:            " << uni.Rank << "\033[0m" << endl;
                    cout << "\033[1;33mInstitution:     " << uni.institution << "\033[0m" << endl;
                    cout << "\033[1;33mLocation Code:   " << uni.locationCode << "\033[0m" << endl;
                    cout << "\033[1;33mLocation:        " << uni.location << "\033[0m" << endl;
                    cout << "----------------------------------------------------------------\n";
                    cout << "AR Score:  " << uni.arScore << " | " << "\tAR Rank:   " << uni.arRank << endl;
                    cout << "ER Score:  " << uni.erScore << " | " << "\tER Rank:   " << uni.erRank << endl;
                    cout << "FSR Score: " << uni.fsrScore << " | " << "\tFSR Rank: " << uni.fsrRank << endl;
                    cout << "CPF Score: " << uni.cpfScore << " | " << "\tCPF Rank: " << uni.cpfRank << endl;
                    cout << "IFR Score: " << uni.ifrScore << " | " << "\tIFR Rank: " << uni.ifrRank << endl;
                    cout << "ISR Score: " << uni.isrScore << " | " << "\tISR Rank: " << uni.isrRank << endl;
                    cout << "IRN Score: " << uni.irnScore << " | " << "\tIRN Rank: " << uni.irnRank << endl;
                    cout << "GER Score: " << uni.gerScore << " | " << "\tGER Rank: " << uni.gerRank << endl;
                    cout << "----------------------------------------------------------------\n";
                    cout << "Scaled Score: " << uni.scoreScaled << endl;
                    cout << "================================================================\n";
                } else {
                    cout << "University not found." << endl;
                }
                break;
            }

            case 4:
            {
                cout << "Customer Login\n";

                cout << "Enter your username: ";
                cin >> customerUsername;
                cout << "Enter your password: ";
                cin >> customerPassword;

                if (users.customerLogin(customerUsername, customerPassword)) {
                    cout << "Login successful!\n";

                    int customerChoice;
                    do {
                        std::cout << "\n----------------------------------------\n";
                        std::cout << "           Customer Menu              \n";
                        std::cout << "----------------------------------------\n";
                        std::cout << "1. Sort Universities\n";
                        std::cout << "2. Search Universities\n";
                        std::cout << "3. Save Favorite Universities\n";
                        std::cout << "4. Send Feedback\n";
                        std::cout << "5. Read Feedback Reply\n";
                        std::cout << "6. Exit\n";
                        std::cout << "----------------------------------------\n";
                        std::cout << "Enter your choice: ";
                        cin >> customerChoice;

                        switch (customerChoice) {
                            case 1: {
                                // Sort universities
                                int sortCusChoice;
                                do {
                                    cout << "----------------------------------------\n";
                                    cout << "           Sorting Options                   \n";
                                    cout << "----------------------------------------\n";
                                    cout << "1. Sort Based on Academic Reputation Score\n";
                                    cout << "2. Sort Based on Faculty/Student Ratio Score\n";
                                    cout << "3. Sort Based on Employer Reputation Score\n";
                                    cout << "4. Back to the Customer Menu\n";
                                    cout << "----------------------------------------\n";
                                    cout << "Enter your choice: ";
                                    cin >> sortCusChoice;

                                    switch (sortCusChoice) {
                                        case 1:
                                            // Sort based on academic reputation score in descending order
                                            sort(universities.begin(), universities.end(), [](const University& u1, const University& u2) {
                                                return u1.arScore > u2.arScore;
                                            });
                                            cout << "Universities sorted based on Academic Reputation Score (Descending Order):\n";
                                            displayAllUniversities(universities);
                                            break;

                                        case 2:
                                            // Sort based on faculty/student ratio score in descending order
                                            sort(universities.begin(), universities.end(), [](const University& u1, const University& u2) {
                                                return u1.fsrScore > u2.fsrScore;
                                            });
                                            cout << "Universities sorted based on Faculty/Student Ratio Score (Descending Order):\n";
                                            displayAllUniversities(universities);
                                            break;

                                        case 3:
                                            // Sort based on employer reputation score in descending order
                                            sort(universities.begin(), universities.end(), [](const University& u1, const University& u2) {
                                                return u1.erScore > u2.erScore;
                                            });
                                            cout << "Universities sorted based on Employer Reputation Score (Descending Order):\n";
                                            displayAllUniversities(universities);
                                            break;

                                        case 4:
                                            // Go back to the customer menu
                                            cout << "Returning to the Customer Menu.\n";
                                            break;

                                        default:
                                            cout << "Invalid choice. Please try again.\n";
                                    }
                                } while (sortCusChoice != 4);
                                break;
                            }

                            case 2: {
                                // Search universities
                                int searchCusChoice;
                                do {
                                    cout << "----------------------------------------\n";
                                    cout << "           Search Options                   \n";
                                    cout << "----------------------------------------\n";
                                    cout << "1. Search by Institution\n";
                                    cout << "2. Search by Location\n";
                                    cout << "3. Back to the Customer Menu\n";
                                    cout << "----------------------------------------\n";
                                    cout << "Enter your choice: ";
                                    cin >> searchCusChoice;

                                    switch (searchCusChoice) {
                                        case 1: {
                                            // Search by Institution
                                            string searchInstitution;
                                            cout << "Enter the institution name to search: ";
                                            cin.ignore();
                                            getline(cin, searchInstitution);

                                            // Perform search based on institution name
                                            vector<University> searchResults;
                                            for (const auto& uni : universities) {
                                                if (uni.institution == searchInstitution) {
                                                    searchResults.push_back(uni);
                                                }
                                            }

                                            if (searchResults.empty()) {
                                                cout << "No universities found with the specified institution name." << endl;
                                            } else {
                                                cout << "Universities found with the specified institution name:\n";
                                                displayAllUniversities(searchResults);
                                            }

                                            break;
                                        }

                                        case 2: {
                                            // Search by Location
                                            string searchLocation;
                                            cout << "Enter the location to search: ";
                                            cin.ignore();
                                            getline(cin, searchLocation);

                                            // Perform search based on location
                                            vector<University> searchResults;
                                            for (const auto& uni : universities) {
                                                if (uni.location == searchLocation) {
                                                    searchResults.push_back(uni);
                                                }
                                            }

                                            if (searchResults.empty()) {
                                                cout << "No universities found at the specified location." << endl;
                                            } else {
                                                cout << "Universities found at the specified location:\n";
                                                displayAllUniversities(searchResults);
                                            }

                                            break;
                                        }

                                        case 3:
                                            // Go back to the customer menu
                                            cout << "Returning to the Customer Menu.\n";
                                            break;

                                        default:
                                            cout << "Invalid choice. Please try again.\n";
                                    }
                                } while (searchCusChoice != 3);
                                break;
                            }

                            case 3: {
                                // Save favorite universities
                                std::string username = loggedInUsername;
                                int favoriteChoice;
                                do {
                                    std::cout << "----------------------------------------\n";
                                    std::cout << "           Favorite Universities                   \n";
                                    std::cout << "----------------------------------------\n";
                                    std::cout << "1. Add favorite universities\n";
                                    std::cout << "2. View favorite universities\n";
                                    std::cout << "3. Back to the Customer Menu\n";
                                    std::cout << "----------------------------------------\n";
                                    std::cout << "Enter your choice: ";
                                    std::cin >> favoriteChoice;

                                    switch (favoriteChoice) {
                                        case 1: {
                                            // Add favorite universities
                                            std::string universityName;
                                            std::cout << "Enter the name of the university to add to favorites: ";
                                            std::cin.ignore();
                                            std::getline(std::cin, universityName);

                                            // Search for the university by name
                                            std::vector<University> searchResults;
                                            for (const auto& uni : universities) {
                                                if (uni.institution == universityName) {
                                                    searchResults.push_back(uni);
                                                }
                                            }

                                            if (searchResults.empty()) {
                                                std::cout << "No universities found with the specified name." << std::endl;
                                            } else if (searchResults.size() == 1) {
                                                // Add the single search result to the list of favorite universities
                                                users.addFavoriteUniversity(username, searchResults[0]);
                                                std::cout << "University added to favorites.\n";
                                            } else {
                                                // Display multiple search results and let the user choose
                                                std::cout << "Multiple universities found with the specified name. Please choose one:\n";
                                                for (size_t i = 0; i < searchResults.size(); ++i) {
                                                    std::cout << i + 1 << ". " << searchResults[i].institution << std::endl;
                                                    // Display other university details as needed
                                                }

                                                int choice;
                                                std::cout << "Enter the number corresponding to the desired university: ";
                                                std::cin >> choice;

                                                if (choice >= 1 && choice <= searchResults.size()) {
                                                    // Add the selected university to the list of favorite universities
                                                    users.addFavoriteUniversity(username, searchResults[choice - 1]);
                                                    std::cout << "University added to favorites.\n";
                                                } else {
                                                    std::cout << "Invalid choice.\n";
                                                }
                                            }

                                            break;
                                        }

                                        case 2: {
                                            // View favorite universities
                                            users.displayFavoriteUniversities(username);
                                            break;
                                        }

                                        case 3:
                                            // Go back to the customer menu
                                            std::cout << "Returning to the Customer Menu.\n";
                                            break;

                                        default:
                                            std::cout << "Invalid choice. Please try again.\n";
                                    }
                                } while (favoriteChoice != 3);
                                break;
                            }

                            case 4: {
                                // Send feedback
                                
                                // send feedback
                                std::cin.ignore();
                                std::cout << "\nEnter customer name: ";
                                std::getline(std::cin, name);
                                std::cout << "Enter feedback: ";
                                std::getline(std::cin, feedback);
                                feedbackList.addFeedback(name, feedback);
                                break;
                                    
                            }

                            case 5: {
                                // Read feedback reply
                                feedbackList.printFeedback();
                                break;
                            }

                            case 6:
                                cout << "Exiting customer menu.\n";
                                break;
                            default:
                                cout << "Invalid choice. Please try again.\n";
                        }
                    } while (customerChoice != 6);

                } else {
                    cout << "Login failed. Invalid username or password.\n";
                }
                break;
            }

            case 5: {
                std::string username, password_admin, customerName;

                std::cin.ignore();
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter password: ";
                std::getline(std::cin, password_admin);

                if (isAdminLogin(username, password_admin)) {
                    int adminChoice;
                        do {
                            std::cout << "\n----------------------------------------\n";
                            std::cout << "               Admin Menu                   \n";
                            std::cout << "----------------------------------------\n";
                            std::cout << "1. Display Users\n";
                            std::cout << "2. Modify User\n";
                            std::cout << "3. Delete Inactive Accounts\n";
                            std::cout << "4. Navigate Feedback (next)\n";
                            std::cout << "5. Navigate Feedback (Previous)\n";
                            std::cout << "6. Read Feedback\n";
                            std::cout << "7. Reply to Feedback\n";
                            std::cout << "8. Generate Top Universities Report\n";
                            std::cout << "9. Exit\n";
                            std::cout << "----------------------------------------\n";
                            std::cout << "Enter your choice: ";
                            std::cin >> adminChoice;

                            std::string username;
                            switch (adminChoice) {
                                case 1:
                                    // Function to display all registered users' details
                                    users.displayUsers();
                                    break;
                                case 2: {
                                    // Function to modify a user detail
                                    std::string username;
                                    std::cout << "Enter the username of the user to modify: ";
                                    std::cin >> username;

                                    LinkedList::ListNode* current = users.getUserNodeByUsername(username);
                                    if (current != nullptr) {
                                        // Display current user details
                                        std::cout << "----------------------------------------\n";
                                        std::cout << "Current User Details:\n";
                                        std::cout << "Customer ID: " << current->customer.id << std::endl;
                                        std::cout << "Username: " << current->username << std::endl;
                                        std::cout << "Password: " << current->password << std::endl;
                                        std::cout << "Customer Name: " << current->customer.name << std::endl;
                                        std::cout << "Customer Age: " << current->customer.age << std::endl;
                                        std::cout << "Customer Status: " << current->customer.status << std::endl;
                                        std::cout << "City Status: " << (current->customer.cityStatus ? "True" : "False") << std::endl;
                                        std::cout << "----------------------------------------\n";

                                        // Modify user details
                                        char choice;
                                        std::cout << "Do you want to modify user details? (y/n): ";
                                        std::cin >> choice;
                                        if (choice == 'y' || choice == 'Y') {
                                            std::cout << "Which detail do you want to modify?\n";
                                            std::cout << "1. Username\n";
                                            std::cout << "2. Password\n";
                                            std::cout << "3. Customer Name\n";
                                            std::cout << "4. Customer Age\n";
                                            std::cout << "5. Customer Status\n";
                                            std::cout << "Enter your choice: ";
                                            int detailChoice;
                                            std::cin >> detailChoice;

                                            switch (detailChoice) {
                                                case 1: {
                                                    std::cout << "Enter new username: ";
                                                    std::string newUsername;
                                                    std::cin >> newUsername;
                                                    current->username = newUsername;
                                                    std::cout << "Username modified.\n";
                                                    break;
                                                }
                                                case 2: {
                                                    std::cout << "Enter new password: ";
                                                    std::string newPassword;
                                                    std::cin >> newPassword;
                                                    current->password = newPassword;
                                                    std::cout << "Password modified.\n";
                                                    break;
                                                }
                                                case 3: {
                                                    std::cout << "Enter new customer name: ";
                                                    std::string newName;
                                                    std::cin.ignore();
                                                    std::getline(std::cin, newName);
                                                    current->customer.name = newName;
                                                    std::cout << "Customer name modified.\n";
                                                    break;
                                                }
                                                case 4: {
                                                    std::cout << "Enter new customer age: ";
                                                    int newAge;
                                                    std::cin >> newAge;
                                                    current->customer.age = newAge;
                                                    std::cout << "Customer age modified.\n";
                                                    break;
                                                }
                                                case 5: {
                                                    std::cout << "Do you want to change the customer status to inactive? (Y/N): ";
                                                    char choice;
                                                    std::cin >> choice;

                                                    if (choice == 'Y' || choice == 'y') {
                                                        current->customer.status = "Inactive";
                                                        std::cout << "Customer status changed to Inactive.\n";
                                                    } else if (choice == 'N' || choice == 'n') {
                                                        std::cout << "Customer status remains Active.\n";
                                                    } else {
                                                        std::cout << "Invalid choice. Customer status remains Active.\n";
                                                    }
                                                    break;
                                                }
                                                default:
                                                    std::cout << "Invalid choice.\n";
                                            }
                                        } else {
                                            std::cout << "No modifications made.\n";
                                        }

                                        // Display modified user details
                                        std::cout << "----------------------------------------\n";
                                        std::cout << "Modified User Details:\n";
                                        std::cout << "Customer ID: " << current->customer.id << std::endl;
                                        std::cout << "Username: " << current->username << std::endl;
                                        std::cout << "Password: " << current->password << std::endl;
                                        std::cout << "Customer Name: " << current->customer.name << std::endl;
                                        std::cout << "Customer Age: " << current->customer.age << std::endl;
                                        std::cout << "Customer Status: " << current->customer.status << std::endl;
                                        std::cout << "City Status: " << (current->customer.cityStatus ? "True" : "False") << std::endl;
                                        std::cout << "----------------------------------------\n";
                                    } else {
                                        std::cout << "User not found.\n";
                                    }
                                    break;
                                }
                                case 3: {
                                    std::cout << "\nDeleting inactive user accounts..." << std::endl;
                                    users.removeInactiveUsers();
                                    std::cout << "Inactive user accounts deleted successfully." << std::endl;
                                    break;
                                }
                                case 4: {
                                    // navigate (next)
                                    feedbackList.navigateFeedback("next");
                                    break;
                                }

                                case 5:{
                                    // navigate (previous)
                                    feedbackList.navigateFeedback("prev");
                                    break;
                                }
                                case 6:{
                                    feedbackList.printFeedback();
                                    break;
                                }

                                case 7:{
                                    // reply
                                    feedbackList.replyFeedback();
                                    break;
                                }
                                case 8:{
                                    // Read universities from the CSV file
                                    std::vector<University> universities = readUniversitiesFromCSV("universities.csv");

                                    // Filter universities in Malaysia
                                    std::vector<University> universitiesInMalaysia;
                                    for (const University& university : universities) {
                                        if (university.location == "Malaysia") {
                                            universitiesInMalaysia.push_back(university);
                                        }
                                    }

                                    // Sort the universities in Malaysia based on rank
                                    std::sort(universitiesInMalaysia.begin(), universitiesInMalaysia.end(),
                                            [](const University& a, const University& b) {
                                                return a.Rank < b.Rank;
                                            });

                                    // Display the top 10 universities in Malaysia
                                    std::cout << "Top 10 Universities in Malaysia:\n";
                                    std::cout << "---------------------------------------------------------\n";
                                    int count = 0;
                                    for (const University& university : universitiesInMalaysia) {
                                        std::cout << "University: " << university.institution << "\n";
                                        std::cout << "Rank: " << university.Rank << "\n";
                                        std::cout << "Location: " << university.location << "\n";
                                        std::cout << "---------------------------------------------------------\n";
                                        count++;
                                        if (count == 10) {
                                            break;
                                        }
                                    }
                                    break;
                                }

                                case 9:{
                                    std::cout << "Exiting admin menu.\n";
                                    break;
                                }
                                
                                default:
                                    std::cout << "Invalid choice. Please try again.\n";
                            }

                        } while (adminChoice != 9); // Pass the users hash table to adminMenu
                    } else {
                        std::cout << "Invalid username or password. Please try again.\n";
                    }
                    break;
                }

                
            
            case 6: {
                cout << "Register as a Customer\n";

                string name, username, password;
                int age;

                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter a username: ";
                cin >> username;

                cout << "Enter a password: ";
                cin >> password;

                cout << "Enter your age: ";
                cin >> age;

                Customer customer;
                customer.name = name;
                customer.username = username;
                customer.password = password;
                customer.age = age;
                customer.isActive = true; // Set the initial activity status to true

                users.addUser(username, password, name, age); // Add the user to the LinkedList
                cout << "\nRegistration successful!\n";
                break;
            }

            case 7:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (mainChoice != 7);

    return 0;
}

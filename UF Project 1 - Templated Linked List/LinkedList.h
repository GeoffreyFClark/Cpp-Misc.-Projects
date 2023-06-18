#include <iostream>
#include <vector>
using namespace std;

template <class T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        CopyList(other);
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            Clear();
            CopyList(other);
        }
        return *this;
    }

    bool operator==(const LinkedList& other) const {
        if (this == &other)
            return true;

        if (count != other.count)
            return false;

        Node* current = head;
        Node* otherCurrent = other.head;
        while (current != nullptr && otherCurrent != nullptr) {
            if (current->data != otherCurrent->data)
                return false;

            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        return true;
    }

    ~LinkedList() {
        Clear();
    }

    void AddHead(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    void AddTail(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void AddNodesHead(const T* values, int size) {
        for (int i = size - 1; i >= 0; i--) {
            AddHead(values[i]);
        }
    }

    void AddNodesTail(const T* values, int size) {
        for (int i = 0; i < size; i++) {
            AddTail(values[i]);
        }
    }

    int NodeCount() const {
        return count;
    }

    void PrintForward() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
    }

    void PrintReverse() const {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->prev;
        }
    }

    Node* Head() const {
        return head;
    }

    Node* Tail() const {
        return tail;
    }

    Node* GetNode(int index) const {
        if (index >= 0 && index < count) {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current;
        }
        throw out_of_range("Index out of range");
    }

    T& operator[](int index) const {
        Node* node = GetNode(index);
        if (node != nullptr) {
            return node->data;
        }
        throw out_of_range("Index out of range");
    }

    Node* Find(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void FindAll(vector<Node*>& nodes, const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                nodes.push_back(current);
            }
            current = current->next;
        }
    }

    void InsertBefore(Node* node, const T& value) {
        if (node == nullptr)
            return;

        Node* newNode = new Node(value);
        newNode->next = node;
        newNode->prev = node->prev;
        if (node->prev != nullptr) {
            node->prev->next = newNode;
        } else {
            head = newNode;
        }
        node->prev = newNode;
        count++;
    }

    void InsertAfter(Node* node, const T& value) {
        if (node == nullptr)
            return;

        Node* newNode = new Node(value);
        newNode->prev = node;
        newNode->next = node->next;
        if (node->next != nullptr) {
            node->next->prev = newNode;
        } else {
            tail = newNode;
        }
        node->next = newNode;
        count++;
    }

    void InsertAt(const T& value, int index) {
        if (index < 0 || index > count)
            throw out_of_range("Index out of range");

        if (index == 0) {
            AddHead(value);
            return;
        }

        if (index == count) {
            AddTail(value);
            return;
        }

        Node* node = GetNode(index);
        InsertBefore(node, value);
    }

    bool RemoveHead() {
        if (head == nullptr) {
            return false;  // List is empty
        }

        Node* nodeToRemove = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete nodeToRemove;
        count--;

        if (head == nullptr) {
            tail = nullptr;
        }

        return true;
    }

    bool RemoveTail() {
        if (tail == nullptr) {
            return false;  // List is empty
        }

        Node* nodeToRemove = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            // if this is the last node, set head to nullptr
            head = nullptr;
        }
        delete nodeToRemove;
        count--;

        return true;
    }


    bool RemoveAt(int index) {
        if (index < 0 || index >= count) {
            return false;  // Invalid index
        }

        if (index == 0) {
            return RemoveHead();
        }

        if (index == count - 1) {
            return RemoveTail();
        }

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* nodeToRemove = current->next;
        current->next = nodeToRemove->next;
        current->next->prev = current;
        delete nodeToRemove;
        count--;

        return true;
    }

    int Remove(const T& value) {
        Node* current = head;
        int removedNodes = 0;

        while (current != nullptr) {
            if (current->data == value) {
                Node* toDelete = current;
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                current = current->next;
                delete toDelete;
                count--;
                removedNodes++;
            } else {
                current = current->next;
            }
        }

        return removedNodes;
    }

    void Print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }

    void PrintForwardRecursive(Node* node) const {
        if (node == nullptr) {
            return;
        }

        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }

    void PrintReverseRecursive(Node* node) const {
        if (node == nullptr) {
            return;
        }

        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

private:
    Node* head;
    Node* tail;
    int count;

    void CopyList(const LinkedList& other) {
        Node* current = other.head;
        while (current != nullptr) {
            AddTail(current->data);
            current = current->next;
        }
    }

};

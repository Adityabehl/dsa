#include <iostream>

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node *prev;
        Node *next;
        Node(int d) : data(d), prev(nullptr), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int length;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}
    
    // Destructor: free all nodes
    ~DoublyLinkedList() {
        Node *cur = head;
        while (cur) {
            Node *tmp = cur->next;
            delete cur;
            cur = tmp;
        }
    }

    // Return current size
    int size() const { return length; }

    // Print list from head to tail
    void printForward() const {
        Node *cur = head;
        std::cout << "List (size=" << length << "): ";
        while (cur) {
            std::cout << cur->data;
            if (cur->next) std::cout << " <-> ";
            cur = cur->next;
        }
        std::cout << "\n";
    }

    // i. Insert at beginning (O(1))
    void insertBeginning(int x) {
        Node *n = new Node(x);
        if (!head) { // empty list
            head = tail = n;
        } else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        ++length;
    }

    // ii. Insert at end (O(1))
    void insertEnd(int x) {
        Node *n = new Node(x);
        if (!tail) { // empty list
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        ++length;
    }

    // iii. Remove from beginning. Returns true on success and sets removedValue.
    bool removeBeginning(int &removedValue) {
        if (!head) return false; // empty
        Node *toRemove = head;
        removedValue = toRemove->data;

        if (head == tail) { // only one node
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete toRemove;
        --length;
        return true;
    }

    // iv. Remove from end. Returns true on success and sets removedValue.
    bool removeEnd(int &removedValue) {
        if (!tail) return false; // empty
        Node *toRemove = tail;
        removedValue = toRemove->data;

        if (head == tail) { // only one node
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete toRemove;
        --length;
        return true;
    }
};

int main() {
    DoublyLinkedList list;
    int choice;
    int x, removed;

    std::cout << "Doubly Linked List ADT Demo\n";

    while (true) {
        std::cout << "\n----- MENU -----\n";
        std::cout << "1. Insert at beginning\n";
        std::cout << "2. Insert at end\n";
        std::cout << "3. Remove from beginning\n";
        std::cout << "4. Remove from end\n";
        std::cout << "5. Print list\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Enter value to insert at beginning: ";
                std::cin >> x;
                list.insertBeginning(x);
                std::cout << "Inserted " << x << " at beginning.\n";
                break;

            case 2:
                std::cout << "Enter value to insert at end: ";
                std::cin >> x;
                list.insertEnd(x);
                std::cout << "Inserted " << x << " at end.\n";
                break;

            case 3:
                if (list.removeBeginning(removed))
                    std::cout << "Removed from beginning: " << removed << "\n";
                else
                    std::cout << "List is empty. Nothing to remove.\n";
                break;

            case 4:
                if (list.removeEnd(removed))
                    std::cout << "Removed from end: " << removed << "\n";
                else
                    std::cout << "List is empty. Nothing to remove.\n";
                break;

            case 5:
                list.printForward();
                break;

            case 6:
                std::cout << "Exiting.\n";
                return 0;

            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

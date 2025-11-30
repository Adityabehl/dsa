#include <iostream>

class SinglyLinkedList {
private:
    struct Node {
        int data;
        Node *next;
        Node(int d, Node *n = nullptr) : data(d), next(n) {}
    };

    Node *head;
    int length;

public:
    SinglyLinkedList() : head(nullptr), length(0) {}
    
    // Destructor: free all nodes
    ~SinglyLinkedList() {
        Node *cur = head;
        while (cur) {
            Node *tmp = cur->next;
            delete cur;
            cur = tmp;
        }
    }

    // Return list size
    int size() const { return length; }

    // Print list contents
    void printList() const {
        Node *cur = head;
        std::cout << "List (size=" << length << "): ";
        while (cur) {
            std::cout << cur->data;
            if (cur->next) std::cout << " -> ";
            cur = cur->next;
        }
        std::cout << "\n";
    }

    // i. Insert at beginning
    void insertBeginning(int x) {
        Node *n = new Node(x, head);
        head = n;
        ++length;
    }

    // ii. Insert at ith position (1-based). Valid positions: 1 .. length+1
    // If pos == 1, equivalent to insertBeginning.
    // Returns true on success, false for invalid pos.
    bool insertAtPosition(int pos, int x) {
        if (pos < 1 || pos > length + 1) return false;

        if (pos == 1) {
            insertBeginning(x);
            return true;
        }

        // find node at position pos-1
        Node *cur = head;
        for (int i = 1; i < pos - 1; ++i) cur = cur->next; // guaranteed non-null
        Node *n = new Node(x, cur->next);
        cur->next = n;
        ++length;
        return true;
    }

    // iii. Remove from beginning.
    // Returns true and sets removedValue on success; false if list empty.
    bool removeBeginning(int &removedValue) {
        if (!head) return false;
        Node *tmp = head;
        removedValue = tmp->data;
        head = head->next;
        delete tmp;
        --length;
        return true;
    }

    // iv. Remove from ith position (1-based). Valid positions: 1 .. length
    // Returns true and sets removedValue on success; false for invalid pos or empty list.
    bool removeAtPosition(int pos, int &removedValue) {
        if (pos < 1 || pos > length || !head) return false;

        if (pos == 1) return removeBeginning(removedValue);

        Node *prev = head;
        for (int i = 1; i < pos - 1; ++i) prev = prev->next; // prev points to pos-1
        Node *toRemove = prev->next;
        removedValue = toRemove->data;
        prev->next = toRemove->next;
        delete toRemove;
        --length;
        return true;
    }

    // vi. Search for element x, return Node* to the found node, or nullptr if not found.
    // Note: returned pointer is internal; user should not delete it.
    Node* search(int x) const {
        Node *cur = head;
        while (cur) {
            if (cur->data == x) return cur;
            cur = cur->next;
        }
        return nullptr;
    }
};

int main() {
    SinglyLinkedList list;
    int choice, x, pos, removed;

    while (true) {
        std::cout << "\n----- MENU -----\n";
        std::cout << "1. Insert at beginning\n";
        std::cout << "2. Insert at position\n";
        std::cout << "3. Remove from beginning\n";
        std::cout << "4. Remove at position\n";
        std::cout << "5. Search element\n";
        std::cout << "6. Print list\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter value: ";
            std::cin >> x;
            list.insertBeginning(x);
            break;

        case 2:
            std::cout << "Enter value: ";
            std::cin >> x;
            std::cout << "Enter position: ";
            std::cin >> pos;
            if (!list.insertAtPosition(pos, x))
                std::cout << "Invalid position!\n";
            break;

        case 3:
            if (list.removeBeginning(removed))
                std::cout << "Removed: " << removed << "\n";
            else
                std::cout << "List empty!\n";
            break;

        case 4:
            std::cout << "Enter position: ";
            std::cin >> pos;
            if (list.removeAtPosition(pos, removed))
                std::cout << "Removed: " << removed << "\n";
            else
                std::cout << "Invalid position!\n";
            break;

        case 5:
            std::cout << "Enter value to search: ";
            std::cin >> x;
            if (list.search(x))
                std::cout << "Element found.\n";
            else
                std::cout << "Element not found.\n";
            break;

        case 6:
            list.printList();
            break;

        case 7:
            return 0;

        default:
            std::cout << "Invalid choice! Try again.\n";
        }
    }
}

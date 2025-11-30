#include <iostream>
using namespace std;

class CircularLinkedList {
private:
    struct Node {
        int data;
        Node *next;
        Node(int d): data(d), next(nullptr) {}
    };
    Node *tail;
    int length;

public:
    CircularLinkedList(): tail(nullptr), length(0) {}

    ~CircularLinkedList() {
        if (!tail) return;
        Node *cur = tail->next;
        tail->next = nullptr;
        while (cur) {
            Node *tmp = cur->next;
            delete cur;
            cur = tmp;
        }
    }

    void insert(int x) {
        Node *n = new Node(x);
        if (!tail) {
            n->next = n;
            tail = n;
        } else {
            n->next = tail->next;
            tail->next = n;
            tail = n;
        }
        length++;
    }

    bool remove(int x, int &removed) {
        if (!tail) return false;
        Node *cur = tail->next, *prev = tail;
        for (int i = 0; i < length; i++) {
            if (cur->data == x) {
                removed = cur->data;
                if (cur == prev) tail = nullptr;
                else {
                    prev->next = cur->next;
                    if (cur == tail) tail = prev;
                }
                delete cur;
                length--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    Node* search(int x) {
        if (!tail) return nullptr;
        Node *cur = tail->next;
        for (int i = 0; i < length; i++) {
            if (cur->data == x) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    void print() {
        if (!tail) {
            cout << "List empty\n";
            return;
        }
        Node *cur = tail->next;
        for (int i = 0; i < length; i++) {
            cout << cur->data;
            if (i + 1 < length) cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

int main() {
    CircularLinkedList list;
    int ch, x, r;

    while (true) {
        cout << "circular linked list as an ADT" ;
        cout << "\n1.Insert\n2.Remove\n3.Search\n4.Print\n5.Exit\nChoice: ";
        cin >> ch;

        if (ch == 1) {
            cout << "Enter x: ";
            cin >> x;
            list.insert(x);
        }
        else if (ch == 2) {
            cout << "Enter x: ";
            cin >> x;
            if (list.remove(x, r)) cout << "Removed: " << r << "\n";
            else cout << "Not found\n";
        }
        else if (ch == 3) {
            cout << "Enter x: ";
            cin >> x;
            auto p = list.search(x);
            if (p) cout << "Found at node: " << p << "\n";
            else cout << "Not found\n";
        }
        else if (ch == 4) {
            list.print();
        }
        else if (ch == 5) break;
        else cout << "Invalid\n";
    }
}

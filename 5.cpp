#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Queue {
    vector<T> a;
    int head = 0, tail = 0, cap;
    bool fullFlag = false;
public:
    Queue(int capacity = 100): a(capacity), cap(capacity) {}
    bool empty() const { return head==tail && !fullFlag; }
    bool full() const { return fullFlag; }
    int size() const { return fullFlag ? cap : (tail - head + cap) % cap; }
    bool push(const T &v) {
        if (fullFlag) return false;
        a[tail] = v;
        tail = (tail + 1) % cap;
        if (tail==head) fullFlag = true;
        return true;
    }
    bool pop(T &out) {
        if (empty()) return false;
        out = a[head];
        head = (head + 1) % cap;
        fullFlag = false;
        return true;
    }
    T front() const { if(empty()) throw runtime_error("empty"); return a[head]; }
};

int main(){
    Queue<int> q(5);
    q.push(10); q.push(20); q.push(30);
    cout<<"Size: "<<q.size()<<"\n";
    int x;
    q.pop(x); cout<<"Popped: "<<x<<"\n";
    cout<<"Front: "<<q.front()<<"\n";
    return 0;
}

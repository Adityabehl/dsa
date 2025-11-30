#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Stack {
    vector<T> data;
public:
    void push(const T& x) { data.push_back(x); }
    T pop() { T v = data.back(); data.pop_back(); return v; }
    T top() const { return data.back(); }
    bool empty() const { return data.empty(); }
    int size() const { return (int)data.size(); }
};

bool isOp(const string &s) {
    return s=="+" || s=="-" || s=="*" || s=="/" || s=="^";
}

double applyOp(const string &op, double a, double b) {
    if (op=="+") return a+b;
    if (op=="-") return a-b;
    if (op=="*") return a*b;
    if (op=="/") return a/b;
    if (op=="^") return pow(a,b);
    throw runtime_error("Unknown operator");
}

vector<string> tokenize(const string &s) {
    vector<string> tok; string t;
    istringstream iss(s);
    while (iss >> t) tok.push_back(t);
    return tok;
}

double evalPostfix(const string &expr) {
    auto tok = tokenize(expr);
    Stack<double> st;
    for (auto &t : tok) {
        if (isOp(t)) {
            if (st.size() < 2) throw runtime_error("Invalid postfix");
            double b = st.pop();
            double a = st.pop();
            st.push(applyOp(t, a, b));
        } else st.push(stod(t));
    }
    if (st.size() != 1) throw runtime_error("Invalid postfix");
    return st.pop();
}

double evalPrefix(const string &expr) {
    auto tok = tokenize(expr);
    Stack<double> st;
    for (int i = (int)tok.size()-1; i >= 0; --i) {
        string t = tok[i];
        if (isOp(t)) {
            if (st.size() < 2) throw runtime_error("Invalid prefix");
            double a = st.pop();
            double b = st.pop();
            st.push(applyOp(t, a, b));
        } else st.push(stod(t));
    }
    if (st.size() != 1) throw runtime_error("Invalid prefix");
    return st.pop();
}

int main(){
    string line;
    cout << "Enter expression type (postfix/prefix): ";
    string type; if(!(cin>>type)) return 0;
    getline(cin, line); // consume newline
    cout << "Enter expression (space separated tokens):\n";
    getline(cin, line);
    try {
        if (type == "postfix") {
            double res = evalPostfix(line);
            cout << "Result: " << res << "\n";
        } else if (type == "prefix") {
            double res = evalPrefix(line);
            cout << "Result: " << res << "\n";
        } else {
            cout << "Unknown type\n";
        }
    } catch (exception &e) {
        cout << "Error: " << e.what() << "\n";
    }
    return 0;
}

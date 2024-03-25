#include <vector>
#include <array>

template <typename T, T (*func)(T, T)>
struct Stack {
private:
    std::vector<std::array<T, 2>> arr;

public:
    void push(T val) {
        arr.push_back({val, func(val, arr.empty() ? val : arr.back()[1])});
    }

    inline void pop() {
        arr.pop_back();
    }

    inline bool empty() {
        return arr.empty();
    }

    inline int size() {
        return arr.size();
    }

    inline T top() {
        return arr.back()[0];
    }

    inline T f() {
        return arr.back()[1];
    }
};

template <typename T, T (*func)(T, T)>
struct Queue {
private:
    Stack<T, func> push_stack, pop_stack;

public:
    inline void push(T val) {
        push_stack.push(val);
    }

    void transferStack() {
        if (pop_stack.empty()) {
            while (!push_stack.empty()) {
                pop_stack.push(push_stack.top());
                push_stack.pop();
            }
        }
    }

    inline void pop() {
        transferStack();
        pop_stack.pop();
    }

    inline bool empty() {
        return push_stack.empty() && pop_stack.empty();
    }

    inline int size() {
        return push_stack.size() + pop_stack.size();
    }

    inline T front() {
        transferStack();
        return pop_stack.top();
    }

    inline T f() {
        transferStack();
        return push_stack.empty() ? pop_stack.f() : func(push_stack.f(), pop_stack.f());
    }
};

int main() {
    
}
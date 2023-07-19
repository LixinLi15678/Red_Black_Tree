#ifndef TRANSPARENTSTACK_H
#define TRANSPARENTSTACK_H

#include <stack>
#include <iostream>

using namespace std;

template <typename T>
class TransparentStack : public std::stack<T> {
    public:
        T peek_at(size_t index) const {
            std::stack<T> copy = *this;

        // Iterate through the stack and return the element at the desired index
        if (index >= copy.size()) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = copy.size(); i > index + 1; i--) {
            copy.pop();
        }

        return copy.top();
    }
};

#endif
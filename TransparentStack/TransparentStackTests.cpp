#include "TransparentStack.h"
#include <cassert>

int main() {
    TransparentStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    // cout << stack.peek_at(0) << endl;
    assert(stack.peek_at(0) == 1);
    // cout << stack.peek_at(1) << endl;
    assert(stack.peek_at(1) == 2);
    // cout << stack.peek_at(2) << endl;
    assert(stack.peek_at(2) == 3);
    // cout << stack.peek_at(3) << endl;
    assert(stack.peek_at(3) == 4);
    return 0;
}
#include <cassert>
#include <iostream>
#include "PageStack.h"
#include "StringUtils.h"

void test_push_and_peek() {
    PageStack stack;
    stack.push(Page("https://uno.com", "Uno"));

    Page top = stack.peek();
    assert(compareString(top.getUrl(), "https://uno.com") == 0);
    assert(compareString(top.getTitle(), "Uno") == 0);
}

void test_push_and_pop() {
    PageStack stack;
    stack.push(Page("https://uno.com", "Uno"));
    stack.push(Page("https://dos.com", "Dos"));

    Page popped = stack.pop();
    assert(compareString(popped.getTitle(), "Dos") == 0);

    Page top = stack.peek();
    assert(compareString(top.getTitle(), "Uno") == 0);
}

void test_isEmpty_and_clear() {
    PageStack stack;
    assert(stack.isEmpty());

    stack.push(Page("https://uno.com", "Uno"));
    assert(!stack.isEmpty());

    stack.clear();
    assert(stack.isEmpty());
}

int main() {
    test_push_and_peek();
    test_push_and_pop();
    test_isEmpty_and_clear();
    std::cout << "✔ Pruebas unitarias de PageStack pasaron correctamente.\n";
    return 0;
}

#include "PageStack.h"
#include <stdexcept>

PageStack::PageStack() : topNode(nullptr) {}

PageStack::~PageStack() {
    clear();
}

void PageStack::push(const Page& page) {
    topNode = new Node(page, topNode);
}

Page PageStack::pop() {
    if (!topNode) throw std::runtime_error("Stack is empty");
    Node* oldTop = topNode;
    Page p = topNode->page;
    topNode = topNode->next;
    delete oldTop;
    return p;
}

Page PageStack::peek() const {
    if (!topNode) throw std::runtime_error("Stack is empty");
    return topNode->page;
}

bool PageStack::isEmpty() const {
    return topNode == nullptr;
}

void PageStack::clear() {
    while (topNode) {
        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
    }
}

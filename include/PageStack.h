#ifndef PAGE_STACK_H
#define PAGE_STACK_H

#include "Page.h"

class PageStack {
private:
    struct Node {
        Page page;
        Node* next;
        Node(const Page& p, Node* n = nullptr) : page(p), next(n) {}
    };
    Node* topNode;

public:
    PageStack();
    ~PageStack();

    void push(const Page& page);
    Page pop();
    Page peek() const;
    bool isEmpty() const;
    void clear();
};

#endif // PAGE_STACK_H

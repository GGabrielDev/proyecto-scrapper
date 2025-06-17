#include "FolderList.h"
#include "StringUtils.h"

FolderList::FolderList() : head(nullptr) {}

FolderList::~FolderList() {
    clear();
}

void FolderList::add(const Folder& f) {
    Node* newNode = new Node(f);
    newNode->next = head;
    head = newNode;
}

Folder* FolderList::findByName(const char* name) const {
    Node* current = head;
    while (current) {
        if (compareString(current->data.getName(), name) == 0) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

int FolderList::size() const {
    Node* current = head;
    int count = 0;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}

void FolderList::clear() {
    Node* current = head;
    while (current) {
        Node* tmp = current;
        current = current->next;
        delete tmp;
    }
    head = nullptr;
}

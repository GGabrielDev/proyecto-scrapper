#include "BookmarkList.h"
#include "StringUtils.h"

BookmarkList::BookmarkList() : head(nullptr) {}

BookmarkList::~BookmarkList() {
    clear();
}

void BookmarkList::add(const Bookmark& b) {
    Node* newNode = new Node(b);
    newNode->next = head;
    head = newNode;
}

bool BookmarkList::removeByUrl(const char* url) {
    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (compareString(current->data.getUrl(), url) == 0) {
            if (previous) previous->next = current->next;
            else head = current->next;
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

Bookmark* BookmarkList::findByName(const char* name) {
    Node* current = head;
    while (current) {
        if (compareString(current->data.getName(), name) == 0) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

Bookmark* BookmarkList::at(int index) {
    Node* current = head;
    int i = 0;
    while (current) {
        if (i == index) return &current->data;
        current = current->next;
        ++i;
    }
    return nullptr;
}

int BookmarkList::size() const {
    Node* current = head;
    int count = 0;
    while (current) {
        ++count;
        current = current->next;
    }
    return count;
}

void BookmarkList::clear() {
    Node* current = head;
    while (current) {
        Node* tmp = current;
        current = current->next;
        delete tmp;
    }
    head = nullptr;
}

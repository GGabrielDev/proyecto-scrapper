#ifndef BOOKMARK_LIST_H
#define BOOKMARK_LIST_H

#include "Bookmark.h"

class BookmarkList {
private:
    struct Node {
        Bookmark data;
        Node* next;
        Node(const Bookmark& b) : data(b), next(nullptr) {}
    };

    Node* head;

public:
    BookmarkList();
    ~BookmarkList();

    void add(const Bookmark& b);
    bool removeByUrl(const char* url); // elimina el primer match
    Bookmark* findByName(const char* name); // retorna puntero o nullptr
    Bookmark* at(int index); // acceso directo
    int size() const;
    void clear();
};

#endif // BOOKMARK_LIST_H

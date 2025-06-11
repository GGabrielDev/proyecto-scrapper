#ifndef FOLDER_LIST_H
#define FOLDER_LIST_H

#include "Folder.h"

class FolderList {
private:
    struct Node {
        Folder data;
        Node* next;
        Node(const Folder& f) : data(f), next(nullptr) {}
    };

    Node* head;

public:
    FolderList();
    ~FolderList();

    void add(const Folder& f);
    Folder* findByName(const char* name);
    int size() const;
    void clear();
};

#endif // FOLDER_LIST_H

#ifndef FOLDER_LIST_H
#define FOLDER_LIST_H

#include "Folder.h"

class FolderList {
public:
    struct Node {
        Folder data;
        Node* next;
        Node(const Folder& f) : data(f.getName()), next(nullptr) {
            BookmarkList* sourceList = f.getList();
            for (int i = 0; i < sourceList->size(); ++i) {
                Bookmark* b = sourceList->at(i);
                if (b) data.addBookmark(*b);  // ❗Copiar contenido, no estructura
            }
        }
    };

    FolderList();
    ~FolderList();

    void clear();
    void add(const Folder& f);
    int size() const;
    Folder* findByName(const char* name) const;
    Node* getHead() const { return head; }

private:
    Node* head;

};

#endif // FOLDER_LIST_H

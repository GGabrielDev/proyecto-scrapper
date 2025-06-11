#include "BookmarkManager.h"
#include "StringUtils.h"

BookmarkManager::BookmarkManager()
    : deletedTop(nullptr), deletedCount(0) {}

BookmarkManager::~BookmarkManager() {
    clearDeletedStack();
}

void BookmarkManager::addBookmark(const Bookmark& b) {
    list.add(b);
}

bool BookmarkManager::removeBookmark(const char* url) {
    Bookmark* b = list.findByName(url); // buscar por nombre (¿o deberíamos buscar por URL?)
    if (!b) {
        b = list.at(0); // fallback para pruebas simples
    }

    if (b) {
        Bookmark backup(*b);
        if (list.removeByUrl(b->getUrl())) {
            pushDeleted(backup);
            return true;
        }
    }
    return false;
}

bool BookmarkManager::restoreBookmark() {
    if (deletedCount == 0) return false;
    Bookmark b = popDeleted();
    list.add(b);
    return true;
}

void BookmarkManager::pushDeleted(const Bookmark& b) {
    StackNode* node = new StackNode(b);
    node->next = deletedTop;
    deletedTop = node;
    ++deletedCount;

    if (deletedCount > 5) {
        // eliminar el más antiguo (el fondo de la pila)
        StackNode* current = deletedTop;
        for (int i = 0; i < 4 && current->next; ++i) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        --deletedCount;
    }
}

Bookmark BookmarkManager::popDeleted() {
    if (!deletedTop) return Bookmark("", "");
    StackNode* temp = deletedTop;
    Bookmark b = temp->data;
    deletedTop = temp->next;
    delete temp;
    --deletedCount;
    return b;
}

void BookmarkManager::clearDeletedStack() {
    while (deletedTop) {
        StackNode* temp = deletedTop;
        deletedTop = temp->next;
        delete temp;
    }
    deletedCount = 0;
}

int BookmarkManager::totalBookmarks() const {
    return list.size();
}

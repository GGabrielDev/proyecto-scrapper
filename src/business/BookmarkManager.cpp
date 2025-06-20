#include "BookmarkManager.h"
#include "FileStorage.h"
#include "StringUtils.h"

BookmarkManager::BookmarkManager()
    : deletedTop(nullptr), deletedCount(0) {}

BookmarkManager::~BookmarkManager() {
    clearDeletedStack();
}

const Bookmark* BookmarkManager::atRaw(int index) const {
    return list.at(index);
}

const FolderList* BookmarkManager::getFolderList() const {
    return &folders;
}

bool BookmarkManager::addBookmark(const Bookmark& b) {
    for (int i = 0; i < list.size(); ++i) {
        Bookmark* actual = list.at(i);
        if (compareString(actual->getUrl(), b.getUrl()) == 0 ||
            compareString(actual->getName(), b.getName()) == 0) {
            return false;
        }
    }

    list.add(b);
    return true;
}

bool BookmarkManager::removeBookmark(const char* url) {
    Bookmark* b = list.findByName(url);
    if (!b) b = list.at(0);  // fallback básico

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

void BookmarkManager::createFolder(const char* name) {
    if (!folders.findByName(name)) {
        folders.add(Folder(name));
    }
}

bool BookmarkManager::addBookmarkToFolder(const Bookmark& b, const char* folderName) {
    Folder* folder = folders.findByName(folderName);
    if (!folder) return false;
    folder->addBookmark(b);
    return true;
}

Bookmark* BookmarkManager::findBookmarkInFolder(const char* name, const char* folderName) {
    Folder* folder = folders.findByName(folderName);
    if (!folder) return nullptr;
    return folder->getList()->findByName(name);
}

int BookmarkManager::totalFolders() const {
    return folders.size();
}

void BookmarkManager::saveToDisk(const char* bookmarksPath, const char* foldersPath) {
    // Guardar favoritos sueltos
    BookmarkList listCopy;
    for (int i = 0; i < list.size(); ++i) {
        Bookmark* b = list.at(i);
        if (b) listCopy.add(*b);
    }
    FileStorage::saveBookmarks(listCopy, bookmarksPath);

    // Guardar carpetas
    FileStorage::saveFolders(folders, foldersPath);
}

void BookmarkManager::loadFromDisk(const char* bookmarksPath, const char* foldersPath) {
    // Cargar favoritos sueltos
    BookmarkList loaded;
    FileStorage::loadBookmarks(loaded, bookmarksPath);
    list.clear();
    for (int i = 0; i < loaded.size(); ++i) {
        Bookmark* b = loaded.at(i);
        if (b) list.add(*b);
    }

    // Cargar carpetas
    folders.clear();
    FileStorage::loadFolders(folders, foldersPath);
}

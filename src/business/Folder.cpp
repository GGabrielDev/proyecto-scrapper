#include "Folder.h"
#include "StringUtils.h"

Folder::Folder(const char* n) {
    copyString(name, n, 256);
}

const char* Folder::getName() const {
    return name;
}

void Folder::setName(const char* newName) {
    copyString(name, newName, 256);
}

void Folder::addBookmark(const Bookmark& b) {
    list.add(b);
}

bool Folder::removeBookmark(const char* url) {
    return list.removeByUrl(url);
}

BookmarkList* Folder::getList() {
    return &list;
}

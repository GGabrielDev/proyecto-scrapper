#include "Bookmark.h"
#include "StringUtils.h"

Bookmark::Bookmark(const char* urlInput, const char* nameInput, const char* folderInput) {
    copyString(url, urlInput, 256);
    copyString(name, nameInput, 256);
    copyString(folder, folderInput, 256);
}

const char* Bookmark::getUrl() const {
    return url;
}

const char* Bookmark::getName() const {
    return name;
}

const char* Bookmark::getFolder() const {
    return folder;
}

void Bookmark::setFolder(const char* newFolder) {
    copyString(folder, newFolder, 256);
}

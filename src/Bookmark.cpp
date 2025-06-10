#include "Bookmark.h"

// Copia una cadena con límite de tamaño, asegurando null terminación
void copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (i < maxLen - 1 && src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
}

// Compara dos cadenas, devuelve 0 si son iguales
int compareString(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return a[i] - b[i];
        ++i;
    }
    return a[i] - b[i];
}

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

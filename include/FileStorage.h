#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "BookmarkList.h"

class FileStorage {
public:
    // Guarda la lista de favoritos en un archivo
    static bool saveBookmarks(const BookmarkList& list, const char* filePath);

    // Carga la lista de favoritos desde un archivo (sobrescribe)
    static bool loadBookmarks(BookmarkList& list, const char* filePath);
};

#endif // FILE_STORAGE_H

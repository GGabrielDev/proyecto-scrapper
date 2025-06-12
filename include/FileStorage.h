#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "BookmarkList.h"
#include "FolderList.h"

class FileStorage {
public:
    static bool saveBookmarks(const BookmarkList& list, const char* filePath);
    static bool loadBookmarks(BookmarkList& list, const char* filePath);

    static bool saveFolders(const FolderList& folders, const char* filePath);
    static bool loadFolders(FolderList& folders, const char* filePath);
};

#endif // FILE_STORAGE_H

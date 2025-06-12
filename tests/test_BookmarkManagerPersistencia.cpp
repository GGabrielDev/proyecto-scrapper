#include <cassert>
#include <iostream>
#include <cstdio>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
    #define RMDIR(path) _rmdir(path)
#else
    #include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
    #define MKDIR(path) mkdir(path, 0755)
    #define RMDIR(path) rmdir(path)
#endif

#include "BookmarkManager.h"
#include "StringUtils.h"

const char* TEST_DIR = "data_test";
const char* FILE_BOOKMARKS = "data_test/bookmarks_final.txt";
const char* FILE_FOLDERS = "data_test/folders_final.txt";

bool isDirectoryEmpty(const char* path) {
#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((std::string(path) + "\\*").c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) return false;
    int count = 0;
    do {
        if (++count > 2) break;
    } while (FindNextFile(hFind, &findFileData));
    FindClose(hFind);
    return count <= 2;
#else
    DIR* dir = opendir(path);
    if (!dir) return false;
    int count = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (++count > 2) break;
    }
    closedir(dir);
    return count <= 2;
#endif
}

void setupTestDirectory() {
    MKDIR(TEST_DIR);
}

void cleanupTestDirectory() {
    std::remove(FILE_BOOKMARKS);
    std::remove(FILE_FOLDERS);
    if (isDirectoryEmpty(TEST_DIR)) {
        RMDIR(TEST_DIR);
    }
}

void test_save_and_load_bookmark_manager() {
    setupTestDirectory();

    // Original manager con favoritos sueltos y en carpetas
    BookmarkManager manager;
    manager.addBookmark(Bookmark("https://uno.com", "Uno"));
    manager.addBookmark(Bookmark("https://dos.com", "Dos", "General"));

    manager.createFolder("Trabajo");
    manager.createFolder("Entretenimiento");
    manager.addBookmarkToFolder(Bookmark("https://yt.com", "YouTube", "Entretenimiento"), "Entretenimiento");

    manager.saveToDisk(FILE_BOOKMARKS, FILE_FOLDERS);

    // Nuevo manager
    BookmarkManager restored;
    restored.loadFromDisk(FILE_BOOKMARKS, FILE_FOLDERS);

    assert(restored.totalBookmarks() == 2);

    Bookmark* b = restored.findBookmarkInFolder("YouTube", "Entretenimiento");
    assert(b != nullptr);
    assert(compareString(b->getUrl(), "https://yt.com") == 0);

    cleanupTestDirectory();
}

int main() {
    test_save_and_load_bookmark_manager();
    std::cout << "BookmarkManager persistencia unificada OK.\n";
    return 0;
}

#include <cassert>
#include <iostream>
#include <cstdio> 

#ifdef _WIN32
    #include <direct.h>
    #include <io.h>
    #include <windows.h>
    #define MKDIR(path) _mkdir(path)
    #define RMDIR(path) _rmdir(path)
#else
    #include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
    #define MKDIR(path) mkdir(path, 0755)
    #define RMDIR(path) rmdir(path)
#endif

#include "FileStorage.h"
#include "BookmarkList.h"
#include "Bookmark.h"
#include "StringUtils.h"

const char* TEST_DIR = "data_test";
const char* TEST_FILE = "data_test/bookmarks_test.txt";

void createTestDirectory() {
    mkdir(TEST_DIR, 0755);
}

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
        if (++count > 2) break; // "." and ".."
    }

    closedir(dir);
    return count <= 2;
#endif
}

void cleanTestEnvironment() {
    std::remove(TEST_FILE);
    if (isDirectoryEmpty(TEST_DIR)) {
        rmdir(TEST_DIR);
    }
}

void test_save_and_load_bookmarks() {
    createTestDirectory();

    BookmarkList list;
    list.add(Bookmark("https://uno.com", "Uno"));
    list.add(Bookmark("https://dos.com", "Dos", "Noticias"));
    list.add(Bookmark("https://tres.com", "Tres", "Favoritos"));

    FileStorage::saveBookmarks(list, TEST_FILE);

    BookmarkList loaded;
    FileStorage::loadBookmarks(loaded, TEST_FILE);

    assert(loaded.size() == 3);

    Bookmark* a = loaded.findByName("Uno");
    assert(a != nullptr);
    assert(compareString(a->getUrl(), "https://uno.com") == 0);
    assert(compareString(a->getFolder(), "") == 0);

    Bookmark* b = loaded.findByName("Dos");
    assert(b != nullptr);
    assert(compareString(b->getFolder(), "Noticias") == 0);

    Bookmark* c = loaded.findByName("Tres");
    assert(c != nullptr);
    assert(compareString(c->getFolder(), "Favoritos") == 0);

    cleanTestEnvironment();
}

int main() {
    test_save_and_load_bookmarks();
    std::cout << "All FileStorage tests passed.\n";
    return 0;
}

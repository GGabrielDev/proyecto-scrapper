#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>

#include "BookmarkManager.h"
#include "StringUtils.h"

const char* TEST_DIR = "data_test";
const char* FILE_BOOKMARKS = "data_test/bookmarks.txt";
const char* FILE_FOLDERS = "data_test/folders.txt";

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

void setupTestDirectory() {
    MKDIR(TEST_DIR);
}

void cleanupTestDirectory() {
    std::remove(FILE_BOOKMARKS);
    std::remove(FILE_FOLDERS);
    RMDIR(TEST_DIR);
}

void integracion_test_save_and_load_manager() {
    setupTestDirectory();

    BookmarkManager original;
    original.addBookmark(Bookmark("https://uno.com", "Uno"));
    original.createFolder("Trabajo");
    original.addBookmarkToFolder(Bookmark("https://ide.com", "IDE", "Trabajo"), "Trabajo");

    original.saveToDisk(FILE_BOOKMARKS, FILE_FOLDERS);

    BookmarkManager loaded;
    loaded.loadFromDisk(FILE_BOOKMARKS, FILE_FOLDERS);

    assert(loaded.totalBookmarks() == 1);
    const Bookmark* b = loaded.atRaw(0);
    assert(b != nullptr);
    assert(compareString(b->getName(), "Uno") == 0);

    const Folder* f = loaded.getFolderList()->findByName("Trabajo");
    assert(f != nullptr);
    BookmarkList* list = f->getList();
    assert(list->size() == 1);
    Bookmark* bf = list->at(0);
    assert(compareString(bf->getName(), "IDE") == 0);

    cleanupTestDirectory();
}

int main() {
    integracion_test_save_and_load_manager();
    std::cout << "✔ Prueba de integración guardar/cargar: OK\n";
    return 0;
}

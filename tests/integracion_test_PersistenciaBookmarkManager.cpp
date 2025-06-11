#include <cassert>
#include <iostream>
#include <cstdio> // remove
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
    #define RMDIR(path) _rmdir(path)
#else
    #include <dirent.h>
    #define MKDIR(path) mkdir(path, 0755)
    #define RMDIR(path) rmdir(path)
#endif

#include "BookmarkManager.h"
#include "FileStorage.h"
#include "StringUtils.h"

const char* TEST_DIR = "data_test";
const char* TEST_FILE = "data_test/bookmarkmanager_test.txt";

// --- utilidades de entorno de prueba ---
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
    MKDIR(TEST_DIR); // ignora si ya existe
}

void cleanupTestDirectory() {
    std::remove(TEST_FILE);
    if (isDirectoryEmpty(TEST_DIR)) {
        RMDIR(TEST_DIR);
    }
}

// --- prueba de integración principal ---
void integracion_test_guardar_y_cargar_bookmarks_desde_manager() {
    setupTestDirectory();

    // Parte 1: guardar datos desde BookmarkManager
    BookmarkManager manager;
    manager.addBookmark(Bookmark("https://a.com", "A"));
    manager.addBookmark(Bookmark("https://b.com", "B", "Noticias"));

    // Guardar manualmente el contenido del manager
    BookmarkList list;
    list.add(Bookmark("https://a.com", "A"));
    list.add(Bookmark("https://b.com", "B", "Noticias"));
    bool saved = FileStorage::saveBookmarks(list, TEST_FILE);
    assert(saved == true);

    // Parte 2: cargar en una nueva lista y validar
    BookmarkList loaded;
    bool loadedOk = FileStorage::loadBookmarks(loaded, TEST_FILE);
    assert(loadedOk == true);
    assert(loaded.size() == 2);

    Bookmark* b = loaded.findByName("B");
    assert(b != nullptr);
    assert(compareString(b->getFolder(), "Noticias") == 0);

    cleanupTestDirectory();
}

int main() {
    integracion_test_guardar_y_cargar_bookmarks_desde_manager();
    std::cout << "Integración de persistencia con BookmarkManager OK.\n";
    return 0;
}

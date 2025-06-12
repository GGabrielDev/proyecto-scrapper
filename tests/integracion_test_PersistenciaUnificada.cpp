#include <cassert>
#include <iostream>
#include <cstdio>

#ifdef _WIN32
    #include <direct.h>
    #include <io.h>
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
#include "FileStorage.h"
#include "StringUtils.h"

const char* TEST_DIR = "data_test";
const char* BOOKMARKS_FILE = "data_test/bookmarks_full.txt";
const char* FOLDERS_FILE = "data_test/folders_full.txt";

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
    std::remove(BOOKMARKS_FILE);
    std::remove(FOLDERS_FILE);
    if (isDirectoryEmpty(TEST_DIR)) {
        RMDIR(TEST_DIR);
    }
}

void integracion_test_persistencia_unificada() {
    setupTestDirectory();

    // Parte 1: Crear y guardar datos
    BookmarkManager manager;
    manager.addBookmark(Bookmark("https://a.com", "A"));
    manager.addBookmark(Bookmark("https://b.com", "B", "Noticias"));

    manager.createFolder("Noticias");
    manager.createFolder("Juegos");
    manager.addBookmarkToFolder(Bookmark("https://game.com", "JuegosOnline", "Juegos"), "Juegos");

    // Guardar favoritos sueltos y carpetas
    BookmarkList rawList;
    rawList.add(Bookmark("https://a.com", "A"));
    rawList.add(Bookmark("https://b.com", "B", "Noticias"));
    FileStorage::saveBookmarks(rawList, BOOKMARKS_FILE);

    FolderList folders;
    Folder juegos("Juegos");
    juegos.addBookmark(Bookmark("https://game.com", "JuegosOnline", "Juegos"));
    folders.add(juegos);
    FileStorage::saveFolders(folders, FOLDERS_FILE);

    // Parte 2: Cargar en estructuras nuevas y validar
    BookmarkList loadedList;
    FolderList loadedFolders;

    FileStorage::loadBookmarks(loadedList, BOOKMARKS_FILE);
    FileStorage::loadFolders(loadedFolders, FOLDERS_FILE);

    assert(loadedList.size() == 2);
    Bookmark* b = loadedList.findByName("B");
    assert(b != nullptr);
    assert(compareString(b->getFolder(), "Noticias") == 0);

    Folder* f = loadedFolders.findByName("Juegos");
    assert(f != nullptr);
    Bookmark* game = f->getList()->findByName("JuegosOnline");
    assert(game != nullptr);
    assert(compareString(game->getUrl(), "https://game.com") == 0);

    cleanupTestDirectory();
}

int main() {
    integracion_test_persistencia_unificada();
    std::cout << "Integración de persistencia completa: OK\n";
    return 0;
}

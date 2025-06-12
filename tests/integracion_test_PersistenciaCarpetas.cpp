#include <cassert>
#include <iostream>
#include <cstdio>

#include "BookmarkManager.h"
#include "FileStorage.h"
#include "StringUtils.h"
#include "FolderList.h"
#include "Folder.h"

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

const char* TEST_DIR = "data_test";
const char* TEST_FILE = "data_test/folder_test.txt";

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
    std::remove(TEST_FILE);
    if (isDirectoryEmpty(TEST_DIR)) {
        RMDIR(TEST_DIR);
    }
}

void integracion_test_guardar_y_cargar_folders() {
    setupTestDirectory();

    // Creamos carpeta con favoritos
    FolderList original;
    Folder noticias("Noticias");
    noticias.addBookmark(Bookmark("https://cnn.com", "CNN"));
    noticias.addBookmark(Bookmark("https://bbc.com", "BBC"));

    Folder tecnologia("Tecnologia");
    tecnologia.addBookmark(Bookmark("https://github.com", "GitHub"));

    original.add(noticias);
    original.add(tecnologia);

    // Guardamos
    bool saved = FileStorage::saveFolders(original, TEST_FILE);
    assert(saved == true);

    // Cargamos en nueva estructura
    FolderList loaded;
    bool loadedOK = FileStorage::loadFolders(loaded, TEST_FILE);
    assert(loadedOK == true);
    assert(loaded.size() == 2);

    Folder* f = loaded.findByName("Tecnologia");
    assert(f != nullptr);
    Bookmark* b = f->getList()->findByName("GitHub");
    assert(b != nullptr);
    assert(compareString(b->getUrl(), "https://github.com") == 0);

    cleanupTestDirectory();
}

int main() {
    integracion_test_guardar_y_cargar_folders();
    std::cout << "Integración de persistencia de carpetas OK.\n";
    return 0;
}

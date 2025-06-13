#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>

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
#include "HtmlExporter.h"

const char* TEST_DIR = "data_test";
const char* HTML_FILE = "data_test/export_test.html";

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
    std::remove(HTML_FILE);
    if (isDirectoryEmpty(TEST_DIR)) {
        RMDIR(TEST_DIR);
    }
}

void test_html_export() {
    setupTestDirectory();

    BookmarkManager bm;
    bm.addBookmark(Bookmark("https://uno.com", "Uno"));
    bm.addBookmark(Bookmark("https://dos.com", "Dos", "Lectura"));

    bm.createFolder("Lectura");
    bm.addBookmarkToFolder(Bookmark("https://tres.com", "Tres", "Lectura"), "Lectura");
    bm.createFolder("Trabajo");
    bm.addBookmarkToFolder(Bookmark("https://cuatro.com", "Cuatro", "Trabajo"), "Trabajo");

    bool ok = HtmlExporter::exportToFile(bm, HTML_FILE);
    assert(ok == true);

    FILE* f = fopen(HTML_FILE, "r");
    assert(f != nullptr);

    char line[512];
    bool foundUno = false, foundCuatro = false;
    while (fgets(line, sizeof(line), f)) {
        if (!foundUno && strstr(line, "https://uno.com")) foundUno = true;
        if (!foundCuatro && strstr(line, "https://cuatro.com")) foundCuatro = true;
    }
    fclose(f);

    assert(foundUno);
    assert(foundCuatro);

    cleanupTestDirectory();
}

int main() {
    test_html_export();
    std::cout << "Exportación HTML completada correctamente.\n";
    return 0;
}

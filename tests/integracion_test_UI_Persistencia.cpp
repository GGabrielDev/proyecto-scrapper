#include <cassert>
#include <iostream>
#include <cstdio>
#include "BookmarkManager.h"
#include "FileStorage.h"
#include "HtmlExporter.h"

const char* FILE_BM = "data_test/bookmarks.txt";
const char* FILE_FL = "data_test/folders.txt";
const char* FILE_HTML = "data_test/export.html";

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

void integracion_test_persistencia_ui() {
    MKDIR("data_test");

    BookmarkManager manager;
    manager.addBookmark(Bookmark("https://uno.com", "Uno"));
    manager.createFolder("Docs");
    manager.addBookmarkToFolder(Bookmark("https://doc.com", "Doc", "Docs"), "Docs");

    // Guardar
    manager.saveToDisk(FILE_BM, FILE_FL);

    // Nueva instancia y cargar
    BookmarkManager loaded;
    loaded.loadFromDisk(FILE_BM, FILE_FL);
    assert(loaded.totalBookmarks() == 1);
    assert(loaded.getFolderList()->findByName("Docs") != nullptr);

    // Exportar
    assert(HtmlExporter::exportToFile(loaded, FILE_HTML));

    // Cleanup
    std::remove(FILE_BM);
    std::remove(FILE_FL);
    std::remove(FILE_HTML);
}

int main() {
    integracion_test_persistencia_ui();
    std::cout << "✔ Prueba de integración de persistencia UI: OK\n";
    return 0;
}

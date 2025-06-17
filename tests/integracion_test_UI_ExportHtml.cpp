#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>
#include "BookmarkManager.h"
#include "HtmlExporter.h"

const char* FILE_HTML = "data_test/export.html";

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0755)
#endif

void integracion_test_export_html_manual() {
    MKDIR("data_test");

    BookmarkManager manager;
    manager.addBookmark(Bookmark("https://ejemplo.com", "Ejemplo"));
    manager.createFolder("Sitios");
    manager.addBookmarkToFolder(Bookmark("https://otro.com", "Otro", "Sitios"), "Sitios");

    bool ok = HtmlExporter::exportToFile(manager, FILE_HTML);
    assert(ok);

    FILE* f = fopen(FILE_HTML, "r");
    assert(f != nullptr);

    char line[256];
    bool found = false;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "https://ejemplo.com")) {
            found = true;
            break;
        }
    }
    fclose(f);
    assert(found);

    std::remove(FILE_HTML);
}

int main() {
    integracion_test_export_html_manual();
    std::cout << "✔ Prueba de integración exportar HTML: OK\n";
    return 0;
}

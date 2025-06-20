#include <iostream>
#include "PersistenceMenu.h"
#include "ClearScreen.h"
#include "FileStorage.h"
#include "HtmlExporter.h"

static const char* FILE_BOOKMARKS = "data/bookmarks.txt";
static const char* FILE_FOLDERS   = "data/folders.txt";
static const char* FILE_HTML      = "data/export.html";

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0755)
#endif

static void handleSave(BookmarkManager& manager);
static void handleLoad(BookmarkManager& manager);
static void handleExportHtml(const BookmarkManager& manager);

void showPersistenceMenu(BookmarkManager& manager) {
    int opcion;

    clearScreen();
    do {
        std::cout << "======= GUARDAR / EXPORTAR =======\n";
        std::cout << "1. Guardar a disco\n";
        std::cout << "2. Cargar desde disco\n";
        std::cout << "3. Exportar a HTML\n";
        std::cout << "4. Volver al menú principal\n";
        std::cout << "==================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: handleSave(manager); break;
            case 2: handleLoad(manager); break;
            case 3: handleExportHtml(manager); break;
            case 4:
                clearScreen();
                return;
            default:
                std::cout << "❌ Opción inválida.\n";
        }
    } while (true);
}

static void handleSave(BookmarkManager& manager) {
    clearScreen();
    MKDIR("data");
    manager.saveToDisk(FILE_BOOKMARKS, FILE_FOLDERS);
    std::cout << "✔ Favoritos guardados en disco.\n";
}

static void handleLoad(BookmarkManager& manager) {
    clearScreen();
    manager.loadFromDisk(FILE_BOOKMARKS, FILE_FOLDERS);
    std::cout << "✔ Favoritos cargados desde disco.\n";
}

static void handleExportHtml(const BookmarkManager& manager) {
    clearScreen();
    MKDIR("data");
    bool ok = HtmlExporter::exportToFile(manager, FILE_HTML);
    if (ok)
        std::cout << "✔ Exportado a " << FILE_HTML << "\n";
    else
        std::cout << "❌ No se pudo exportar.\n";
}

#include "ConsoleUI.h"
#include "BookmarkManager.h"
#include "HistoryManager.h"
#include "HtmlExporter.h"
#include <iostream>
#include <cstdio>
#include <cstring>

#ifdef _WIN32
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif

static void showMenu();
static int readOption();

static void handleListAll(const BookmarkManager& manager);
static void handleListFolder(const BookmarkManager& manager);
static void handleAddBookmark(BookmarkManager& manager);
static void handleCreateFolder(BookmarkManager& manager);
static void handleAddBookmarkToFolder(BookmarkManager& manager);
static void handleSave(BookmarkManager& manager);
static void handleLoad(BookmarkManager& manager);
static void handleExportHtml(const BookmarkManager& manager);
static void handleVisitPage(HistoryManager& history);
static void handleGoBack(HistoryManager& history);
static void handleGoForward(HistoryManager& history);
static void handleShowCurrentPage(const HistoryManager& history);
static void handleExit();

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::system("clear");
#endif
}

void ConsoleUI::run() {
    BookmarkManager manager;
    HistoryManager history;

    int option;
    do {
        showMenu();
        option = readOption();

        switch (option) {
            case 1:
                handleListAll(manager);
                break;
            case 2:
                handleListFolder(manager);
                break;
            case 3:
                handleAddBookmark(manager);
                break;
            case 5:
                handleCreateFolder(manager);
                break;
            case 6:
                handleAddBookmarkToFolder(manager);
                break;
            case 7:
                handleSave(manager);
                break;
            case 8:
                handleLoad(manager);
                break;
            case 9:
                handleExportHtml(manager);
                break;
            case 10:
                handleVisitPage(history);
                break;
            case 11:
                handleGoBack(history);
                break;
            case 12:
                handleGoForward(history);
                break;
            case 13:
                handleShowCurrentPage(history);
                break;
            case 0:
                handleExit();
                break;
            default:
                std::cout << "Opción no válida.\n";
                break;
        }
    } while (option != 0);
}

static void showMenu() {
    std::cout << "\n=== GESTOR DE FAVORITOS ===\n";
    std::cout << "1. Ver todos los favoritos\n";
    std::cout << "2. Ver favoritos por carpeta\n";
    std::cout << "3. Agregar un favorito\n";
    std::cout << "4. Eliminar un favorito\n";
    std::cout << "5. Crear carpeta\n";
    std::cout << "6. Agregar favorito a carpeta\n";
    std::cout << "7. Guardar\n";
    std::cout << "8. Cargar\n";
    std::cout << "9. Exportar a HTML\n";
    std::cout << "0. Salir\n";
    std::cout << "10. Visitar nueva página\n";
    std::cout << "11. Retroceder\n";
    std::cout << "12. Avanzar\n";
    std::cout << "13. Ver página actual\n";
    std::cout << "Seleccione una opción: ";
}

static int readOption() {
    int opt = -1;
    std::cin >> opt;
    std::cin.ignore(1000, '\n'); // limpia entrada
    return opt;
}

static void handleListAll(const BookmarkManager& manager) {
    std::cout << "\n--- Favoritos sin carpeta ---\n";
    for (int i = 0; i < manager.totalBookmarks(); ++i) {
        const Bookmark* b = manager.atRaw(i);
        if (b && b->getFolder()[0] == '\0') {
            std::cout << "- " << b->getName() << " (" << b->getUrl() << ")\n";
        }
    }
}

static void handleExit() {
    std::cout << "\n¡Hasta luego!\n";
}

static void handleAddBookmark(BookmarkManager& manager) {
    clearScreen();
    std::cout << "\n--- Agregar un favorito ---\n";

    char url[256], name[256], folder[256];

    std::cout << "Ingrese la URL: ";
    std::cin.getline(url, sizeof(url));

    std::cout << "Ingrese el nombre: ";
    std::cin.getline(name, sizeof(name));

    std::cout << "¿Desea agregarlo a una carpeta? (deje vacío si no): ";
    std::cin.getline(folder, sizeof(folder));

    manager.addBookmark(Bookmark(url, name, folder));

    std::cout << "✔ Favorito agregado correctamente.\n";
}

static void handleCreateFolder(BookmarkManager& manager) {
    clearScreen();
    std::cout << "\n--- Crear una carpeta ---\n";

    char folderName[128];
    std::cout << "Nombre de la nueva carpeta: ";
    std::cin.getline(folderName, sizeof(folderName));

    if (folderName[0] == '\0') {
        std::cout << "❌ El nombre no puede estar vacío.\n";
        return;
    }

    manager.createFolder(folderName);
    std::cout << "✔ Carpeta \"" << folderName << "\" creada correctamente.\n";
}

static void handleListFolder(const BookmarkManager& manager) {
    clearScreen();
    std::cout << "\n--- Ver favoritos por carpeta ---\n";

    char folderName[128];
    std::cout << "Ingrese el nombre de la carpeta: ";
    std::cin.getline(folderName, sizeof(folderName));

    const Folder* folder = manager.getFolderList()->findByName(folderName);

    if (!folder) {
        std::cout << "❌ Carpeta no encontrada.\n";
        return;
    }

    BookmarkList* list = folder->getList();
    if (list->size() == 0) {
        std::cout << "La carpeta está vacía.\n";
        return;
    }

    std::cout << "Favoritos en \"" << folderName << "\":\n";
    for (int i = 0; i < list->size(); ++i) {
        Bookmark* b = list->at(i);
        if (b) {
            std::cout << "- " << b->getName() << " (" << b->getUrl() << ")\n";
        }
    }
}

static void handleAddBookmarkToFolder(BookmarkManager& manager) {
    clearScreen();
    std::cout << "\n--- Agregar favorito a una carpeta ---\n";

    char folderName[128];
    std::cout << "Nombre de la carpeta destino: ";
    std::cin.getline(folderName, sizeof(folderName));

    Folder* folder = manager.getFolderList()->findByName(folderName);
    if (!folder) {
        std::cout << "❌ La carpeta no existe. Cree la carpeta primero.\n";
        return;
    }

    char url[256], name[128];
    std::cout << "Ingrese la URL: ";
    std::cin.getline(url, sizeof(url));

    std::cout << "Ingrese el nombre: ";
    std::cin.getline(name, sizeof(name));

    Bookmark b(url, name, folderName);
    manager.addBookmarkToFolder(b, folderName);

    std::cout << "✔ Favorito agregado a la carpeta \"" << folderName << "\".\n";
}

static void handleSave(BookmarkManager& manager) {
    clearScreen();
    std::cout << "\n--- Guardar favoritos ---\n";

    const char* fileBookmarks = "data/bookmarks.txt";
    const char* fileFolders = "data/folders.txt";

#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0755);
#endif

    manager.saveToDisk(fileBookmarks, fileFolders);
    std::cout << "✔ Favoritos guardados correctamente.\n";
}

static void handleLoad(BookmarkManager& manager) {
    clearScreen();
    std::cout << "\n--- Cargar favoritos desde disco ---\n";

    const char* fileBookmarks = "data/bookmarks.txt";
    const char* fileFolders = "data/folders.txt";

    manager.loadFromDisk(fileBookmarks, fileFolders);
    std::cout << "✔ Favoritos cargados correctamente.\n";
}

static void handleExportHtml(const BookmarkManager& manager) {
    clearScreen();
    std::cout << "\n--- Exportar favoritos a HTML ---\n";

    const char* htmlPath = "data/export.html";

#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0755);
#endif

    bool ok = HtmlExporter::exportToFile(manager, htmlPath);
    if (ok) {
        std::cout << "✔ Exportación realizada correctamente a: " << htmlPath << "\n";
    } else {
        std::cout << "❌ Error al generar el archivo HTML.\n";
    }
}

static void handleVisitPage(HistoryManager& history) {
    clearScreen();
    std::cout << "\n--- Visitar nueva página ---\n";

    char url[256], title[128];
    std::cout << "Ingrese la URL: ";
    std::cin.getline(url, sizeof(url));

    std::cout << "Ingrese el título: ";
    std::cin.getline(title, sizeof(title));

    history.visit(Page(url, title));
    std::cout << "✔ Página visitada: " << title << "\n";
}

static void handleGoBack(HistoryManager& history) {
    clearScreen();
    std::cout << "\n--- Retroceder ---\n";

    if (!history.canGoBack()) {
        std::cout << "❌ No hay página anterior.\n";
        return;
    }

    history.goBack();
    std::cout << "✔ Página anterior cargada.\n";
}

static void handleGoForward(HistoryManager& history) {
    clearScreen();
    std::cout << "\n--- Avanzar ---\n";

    if (!history.canGoForward()) {
        std::cout << "❌ No hay página siguiente.\n";
        return;
    }

    history.goForward();
    std::cout << "✔ Página siguiente cargada.\n";
}

static void handleShowCurrentPage(const HistoryManager& history) {
    clearScreen();
    std::cout << "\n--- Página actual ---\n";

    Page actual = history.getCurrent();
    std::cout << "Título: " << actual.getTitle() << "\n";
    std::cout << "URL: " << actual.getUrl() << "\n";
}

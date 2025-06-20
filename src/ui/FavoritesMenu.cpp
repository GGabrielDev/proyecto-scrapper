#include <iostream>
#include "FavoritesMenu.h"
#include "ClearScreen.h"

static void handleViewAllBookmarks(const BookmarkManager& manager);
static void handleViewBookmarksByFolder(const BookmarkManager& manager);
static void handleAddBookmark(BookmarkManager& manager);
static void handleRemoveBookmark(BookmarkManager& manager);

void mostrarMenuFavoritos(BookmarkManager& manager) {
    int opcion;

    clearScreen();
    do {
        std::cout << "===== GESTIÓN DE FAVORITOS =====\n";
        std::cout << "1. Ver todos los favoritos\n";
        std::cout << "2. Ver favoritos por carpeta\n";
        std::cout << "3. Agregar favorito\n";
        std::cout << "4. Eliminar favorito\n";
        std::cout << "5. Restaurar favorito eliminado\n";
        std::cout << "6. Crear carpeta\n";
        std::cout << "7. Agregar favorito a carpeta\n";
        std::cout << "8. Volver al menú principal\n";
        std::cout << "================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                handleViewAllBookmarks(manager);
                break;
            case 2:
                handleViewBookmarksByFolder(manager);
                break;
            case 3:
                handleAddBookmark(manager);
                break;
            case 4:
                handleRemoveBookmark(manager);
                break;
            case 5:
                // implementar
                break;
            case 6:
                // implementar
                break;
            case 7:
                // implementar
                break;
            case 8:
                return;
            default:
                clearScreen();
                std::cout << "❌ Opción inválida.\n";
        }

    } while (true);
}

static void handleViewAllBookmarks(const BookmarkManager& manager) {
    clearScreen();
    std::cout << "--- Favoritos guardados ---\n\n";

    int total = manager.totalBookmarks();
    if (total == 0) {
        std::cout << "No hay favoritos.\n";
        return;
    }

    for (int i = 0; i < total; ++i) {
        const Bookmark* b = manager.atRaw(i);
        std::cout << i + 1 << ". " << b->getName() << " (" << b->getUrl() << ")\n";
    }
}

static void handleViewBookmarksByFolder(const BookmarkManager& manager) {
    clearScreen();
    std::cout << "--- Favoritos por carpeta ---\n\n";

    const FolderList* folders = manager.getFolderList();
    FolderList::Node* node = folders->getHead();

    if (!node) {
        std::cout << "No hay carpetas.\n";
        return;
    }

    int carpetaIndex = 1;
    while (node) {
        Folder* folder = &node->data;
        std::cout << carpetaIndex++ << ") " << folder->getName() << ":\n";

        BookmarkList* list = folder->getList();
        if (list->size() == 0) {
            std::cout << "   (Vacía)\n";
        } else {
            for (int i = 0; i < list->size(); ++i) {
                Bookmark* b = list->at(i);
                std::cout << "   - " << b->getName() << " (" << b->getUrl() << ")\n";
            }
        }

        std::cout << "\n";
        node = node->next;
    }
}

static void handleAddBookmark(BookmarkManager& manager) {
    clearScreen();
    std::cout << "--- Agregar nuevo favorito ---\n";

    char url[256];
    char name[128];

    std::cout << "Ingrese la URL: ";
    std::cin.getline(url, sizeof(url));

    std::cout << "Ingrese el nombre: ";
    std::cin.getline(name, sizeof(name));

    Bookmark nuevo(url, name);

    if (manager.addBookmark(nuevo)) {
        std::cout << "✔ Favorito agregado correctamente.\n";
    } else {
        std::cout << "❌ Ya existe un favorito con esa URL o nombre.\n";
    }
}

static void handleRemoveBookmark(BookmarkManager& manager) {
    clearScreen();
    std::cout << "--- Eliminar favorito ---\n";
    std::cout << "¿Desea eliminar por:\n";
    std::cout << "1. URL\n";
    std::cout << "2. Nombre\n";
    std::cout << "Seleccione una opción: ";

    int metodo;
    std::cin >> metodo;
    std::cin.ignore();

    char input[256];
    if (metodo == 1) {
        std::cout << "Ingrese la URL exacta: ";
        std::cin.getline(input, sizeof(input));
        if (manager.removeBookmarkByUrl(input)) {
            std::cout << "✔ Favorito eliminado por URL.\n";
        } else {
            std::cout << "❌ No se encontró un favorito con esa URL.\n";
        }
    } else if (metodo == 2) {
        std::cout << "Ingrese el nombre exacto: ";
        std::cin.getline(input, sizeof(input));
        if (manager.removeBookmarkByName(input)) {
            std::cout << "✔ Favorito eliminado por nombre.\n";
        } else {
            std::cout << "❌ No se encontró un favorito con ese nombre.\n";
        }
    } else {
        std::cout << "❌ Opción inválida.\n";
    }
}

#include <iostream>
#include "NavigationMenu.h"
#include "BookmarkManager.h"
#include "HistoryManager.h"
#include "ClearScreen.h"

static void handleVisitPage(HistoryManager& history);
static void handleGoBack(HistoryManager& history);
static void handleGoForward(HistoryManager& history);
static void handleShowCurrentPage(const HistoryManager& history);
static void handleCurrentToBookmark(BookmarkManager& manager, const HistoryManager& history);
static void handleVisitBookmark(BookmarkManager& manager, HistoryManager& history);

void showNavigationMenu(BookmarkManager& manager, HistoryManager& history) {
    int opcion;

    clearScreen();
    do {
        std::cout << "==== NAVEGACIÓN WEB SIMULADA ====\n";
        Page actual = history.getCurrent();
        std::cout << "Página actual: [" << actual.getUrl() << "] - " << actual.getTitle() << "\n";
        std::cout << "1. Visitar nueva página\n";
        std::cout << "2. Retroceder\n";
        std::cout << "3. Avanzar\n";
        std::cout << "4. Ver página actual\n";
        std::cout << "5. Agregar página actual a favoritos\n";
        std::cout << "6. Visitar un favorito\n";
        std::cout << "7. Volver al menú principal\n";
        std::cout << "==================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: handleVisitPage(history); break;
            case 2: handleGoBack(history); break;
            case 3: handleGoForward(history); break;
            case 4: handleShowCurrentPage(history); break;
            case 5: handleCurrentToBookmark(manager, history); break;
            case 6: handleVisitBookmark(manager, history); break;
            case 7:
                clearScreen();
                return;
            default:
                clearScreen();
                std::cout << "❌ Opción inválida.\n";
        }
    } while (true);
}

static void handleVisitPage(HistoryManager& history) {
    clearScreen();
    char url[256], title[128];
    std::cout << "Ingrese la URL: ";
    std::cin.getline(url, sizeof(url));
    std::cout << "Ingrese el título: ";
    std::cin.getline(title, sizeof(title));
    history.visit(Page(url, title));
    std::cout << "✔ Página visitada.\n";
}

static void handleGoBack(HistoryManager& history) {
    clearScreen();
    if (history.canGoBack()) {
        history.goBack();
        std::cout << "✔ Retrocedido.\n";
    } else {
        std::cout << "❌ No hay página anterior.\n";
    }
}

static void handleGoForward(HistoryManager& history) {
    clearScreen();
    if (history.canGoForward()) {
        history.goForward();
        std::cout << "✔ Avanzado.\n";
    } else {
        std::cout << "❌ No hay página siguiente.\n";
    }
}

static void handleShowCurrentPage(const HistoryManager& history) {
    clearScreen();
    Page p = history.getCurrent();
    std::cout << "Título: " << p.getTitle() << "\n";
    std::cout << "URL: " << p.getUrl() << "\n";
}

static void handleCurrentToBookmark(BookmarkManager& manager, const HistoryManager& history) {
    clearScreen();
    Page actual = history.getCurrent();

    std::cout << "--- Agregar página actual a favoritos ---\n";
    std::cout << "URL: " << actual.getUrl() << "\n";
    std::cout << "Nombre: " << actual.getTitle() << "\n";

    // Mostrar carpetas existentes
    const FolderList* folders = manager.getFolderList();
    FolderList::Node* node = folders->getHead();

    std::cout << "Carpetas disponibles:\n";
    int count = 0;
    while (node) {
        std::cout << " - " << node->data.getName() << "\n";
        node = node->next;
        ++count;
    }
    if (count == 0) std::cout << " (ninguna)\n";

    char folder[128];
    std::cout << "Ingrese carpeta destino (vacío para dejar suelto): ";
    std::cin.getline(folder, sizeof(folder));

    Bookmark nuevo(actual.getUrl(), actual.getTitle(), folder);

    if (folder[0] == '\0') {
        // Sin carpeta
        if (manager.addBookmark(nuevo)) {
            std::cout << "✔ Favorito agregado sin carpeta.\n";
        } else {
            std::cout << "❌ No se pudo agregar (¿duplicado?).\n";
        }
    } else {
        // Carpeta escrita
        if (!folders->findByName(folder)) {
            manager.createFolder(folder);
            std::cout << "ℹ Carpeta \"" << folder << "\" creada automáticamente.\n";
        }

        if (manager.addBookmarkToFolder(nuevo, folder)) {
            std::cout << "✔ Favorito agregado a carpeta.\n";
        } else {
            std::cout << "❌ No se pudo agregar (¿duplicado?).\n";
        }
    }
}

static void handleVisitBookmark(BookmarkManager& manager, HistoryManager& history) {
    clearScreen();
    std::cout << "--- Visitar un favorito ---\n";

    const FolderList* folders = manager.getFolderList();
    int total = manager.totalBookmarks();
    int index = 0;

    // Mostrar favoritos sueltos
    for (int i = 0; i < total; ++i) {
        const Bookmark* b = manager.atRaw(i);
        std::cout << ++index << ". " << b->getName() << " - " << b->getUrl() << "\n";
    }

    // Mostrar favoritos por carpeta
    FolderList::Node* node = folders->getHead();
    while (node) {
        Folder* folder = &node->data;
        BookmarkList* list = folder->getList();
        for (int i = 0; i < list->size(); ++i) {
            Bookmark* b = list->at(i);
            std::cout << ++index << ". " << b->getName()
                      << " - " << b->getUrl()
                      << " (Carpeta: " << folder->getName() << ")\n";
        }
        node = node->next;
    }

    if (index == 0) {
        std::cout << "No hay favoritos disponibles.\n";
        return;
    }

    std::cout << "Seleccione el número del favorito a visitar: ";
    int seleccion;
    std::cin >> seleccion;
    std::cin.ignore();

    if (seleccion < 1 || seleccion > index) {
        std::cout << "❌ Selección inválida.\n";
        return;
    }

    // Reiterar el mismo proceso para encontrar el favorito
    index = 0;
    for (int i = 0; i < total; ++i) {
        const Bookmark* b = manager.atRaw(i);
        if (++index == seleccion) {
            history.visit(Page(b->getUrl(), b->getName()));
            std::cout << "✔ Navegado a favorito.\n";
            return;
        }
    }

    node = folders->getHead();
    while (node) {
        Folder* folder = &node->data;
        BookmarkList* list = folder->getList();
        for (int i = 0; i < list->size(); ++i) {
            Bookmark* b = list->at(i);
            if (++index == seleccion) {
                history.visit(Page(b->getUrl(), b->getName()));
                std::cout << "✔ Navegado a favorito de carpeta.\n";
                return;
            }
        }
        node = node->next;
    }
}

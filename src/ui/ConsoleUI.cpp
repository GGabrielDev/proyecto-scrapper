#include "ConsoleUI.h"
#include "BookmarkManager.h"
#include <iostream>
#include <cstdio>
#include <cstring>

static void showMenu();
static int readOption();
static void handleListAll(const BookmarkManager& manager);
static void handleExit();

void ConsoleUI::run() {
    BookmarkManager manager;

    int option;
    do {
        showMenu();
        option = readOption();

        switch (option) {
            case 1:
                handleListAll(manager);
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

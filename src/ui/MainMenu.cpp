#include <iostream>
#include "MainMenu.h"
#include "FavoritesMenu.h"
#include "NavigationMenu.h"
#include "PersistenceMenu.h"
#include "ClearScreen.h"

void mostrarMenuPrincipal() {
    BookmarkManager manager;
    HistoryManager history;
    int opcion;

    clearScreen();
    do {
        std::cout << "========= MENÚ PRINCIPAL =========\n";
        std::cout << "1. Gestión de favoritos\n";
        std::cout << "2. Navegación web simulada\n";
        std::cout << "3. Guardar / Cargar / Exportar\n";
        std::cout << "0. Salir\n";
        std::cout << "==================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                showFavoritesMenu(manager);
                break;
            case 2:
                showNavigationMenu(manager, history);
                break;
            case 3:
                showPersistenceMenu(manager);
                break;
            case 0:
                std::cout << "Saliendo...\n";
                break;
            default:
                clearScreen();
                std::cout << "❌ Opción inválida.\n";
        }

    } while (opcion != 0);
}

#include <iostream>
#include "FavoritesMenu.h"
#include "ClearScreen.h"

void mostrarMenuFavoritos(BookmarkManager& manager) {
    int opcion;

    do {
        clearScreen();
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
                // implementar
                break;
            case 2:
                // implementar
                break;
            case 3:
                // implementar
                break;
            case 4:
                // implementar
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
                std::cout << "❌ Opción inválida.\n";
        }

    } while (true);
}

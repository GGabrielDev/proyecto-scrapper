#include <iostream>
#include "NavigationMenu.h"
#include "ClearScreen.h"

static void handleVisitPage(HistoryManager& history);
static void handleGoBack(HistoryManager& history);
static void handleGoForward(HistoryManager& history);
static void handleShowCurrentPage(const HistoryManager& history);

void mostrarMenuNavegacion(HistoryManager& history) {
    int opcion;

    do {
        clearScreen();
        std::cout << "==== NAVEGACIÓN WEB SIMULADA ====\n";
        Page actual = history.getCurrent();
        std::cout << "Página actual: [" << actual.getUrl() << "] - " << actual.getTitle() << "\n";
        std::cout << "1. Visitar nueva página\n";
        std::cout << "2. Retroceder\n";
        std::cout << "3. Avanzar\n";
        std::cout << "4. Ver página actual\n";
        std::cout << "5. Volver al menú principal\n";
        std::cout << "==================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: handleVisitPage(history); break;
            case 2: handleGoBack(history); break;
            case 3: handleGoForward(history); break;
            case 4: handleShowCurrentPage(history); break;
            case 5: return;
            default:
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

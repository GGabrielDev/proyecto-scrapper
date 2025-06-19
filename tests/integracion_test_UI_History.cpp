#include <cassert>
#include <iostream>
#include "HistoryManager.h"
#include "StringUtils.h"

void integracion_test_navegacion_simulada() {
    HistoryManager history;

    // Simula visitar páginas
    history.visit(Page("https://a.com", "A"));
    history.visit(Page("https://b.com", "B"));
    history.visit(Page("https://c.com", "C"));

    Page actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "C") == 0);

    // Retroceder dos veces
    history.goBack();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "B") == 0);

    history.goBack();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "A") == 0);

    // Avanzar una vez
    history.goForward();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "B") == 0);
}

int main() {
    integracion_test_navegacion_simulada();
    std::cout << "✔ Prueba de integración de navegación en UI: OK\n";
    return 0;
}

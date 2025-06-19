#include <cassert>
#include <iostream>
#include "HistoryManager.h"
#include "StringUtils.h"

void integracion_test_history_flow() {
    HistoryManager history;

    // Visita 3 páginas
    history.visit(Page("https://a.com", "A"));
    history.visit(Page("https://b.com", "B"));
    history.visit(Page("https://c.com", "C"));

    // Validar que la actual sea C
    Page actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "C") == 0);

    // Ir atrás una vez → B
    history.goBack();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "B") == 0);

    // Ir atrás otra vez → A
    history.goBack();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "A") == 0);

    // Ir adelante una vez → B
    history.goForward();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "B") == 0);

    // Visitar una nueva página (debe borrar forwardStack)
    history.visit(Page("https://d.com", "D"));
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "D") == 0);

    // Ya no debe poder ir adelante
    assert(!history.canGoForward());

    // Ir atrás → B
    history.goBack();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "B") == 0);

    // Volver adelante → D
    history.goForward();
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "D") == 0);
}

int main() {
    integracion_test_history_flow();
    std::cout << "✔ Prueba de integración de navegación con HistoryManager: OK\n";
    return 0;
}

#include <cassert>
#include <iostream>
#include "HistoryManager.h"
#include "StringUtils.h"

void integracion_test_navegacion_ui() {
    HistoryManager history;

    history.visit(Page("https://uno.com", "Uno"));
    history.visit(Page("https://dos.com", "Dos"));
    history.visit(Page("https://tres.com", "Tres"));

    history.goBack(); // → Dos
    assert(compareString(history.getCurrent().getTitle(), "Dos") == 0);

    history.goForward(); // → Tres
    assert(compareString(history.getCurrent().getTitle(), "Tres") == 0);

    history.goBack(); // → Dos
    history.visit(Page("https://nueva.com", "Nueva")); // borra forward
    assert(!history.canGoForward());
}

int main() {
    integracion_test_navegacion_ui();
    std::cout << "✔ Prueba de integración de navegación UI: OK\n";
    return 0;
}

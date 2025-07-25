#include <cassert>
#include <iostream>
#include "HistoryManager.h"
#include "StringUtils.h"

void test_visit_and_getCurrent() {
    HistoryManager history;
    history.visit(Page("https://example.com", "Inicio"));

    Page current = history.getCurrent();
    assert(compareString(current.getUrl(), "https://example.com") == 0);
    assert(compareString(current.getTitle(), "Inicio") == 0);
}

void test_back_and_forward() {
    HistoryManager history;
    history.visit(Page("https://uno.com", "Uno"));
    history.visit(Page("https://dos.com", "Dos"));
    history.visit(Page("https://tres.com", "Tres"));

    history.goBack();  // a Dos
    Page actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "Dos") == 0);

    history.goBack();  // a Uno
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "Uno") == 0);

    history.goForward();  // a Dos
    actual = history.getCurrent();
    assert(compareString(actual.getTitle(), "Dos") == 0);
}

void test_canGoBack_and_canGoForward() {
    HistoryManager history;

    assert(!history.canGoBack());
    assert(!history.canGoForward());

    history.visit(Page("https://uno.com", "Uno"));
    assert(!history.canGoBack());
    assert(!history.canGoForward());

    history.visit(Page("https://dos.com", "Dos"));
    assert(history.canGoBack());
    assert(!history.canGoForward());

    history.goBack();  // volver a Uno
    assert(!history.canGoBack());
    assert(history.canGoForward());

    history.goForward();  // volver a Dos
    assert(history.canGoBack());
    assert(!history.canGoForward());
}

int main() {
    test_visit_and_getCurrent();
    test_back_and_forward();
    test_canGoBack_and_canGoForward();
    std::cout << "✔ Pruebas de HistoryManager pasaron correctamente.\n";
    return 0;
}

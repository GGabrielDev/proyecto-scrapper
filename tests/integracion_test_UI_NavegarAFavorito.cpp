#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "HistoryManager.h"
#include "StringUtils.h"

void integracion_test_navegar_a_favorito() {
    BookmarkManager manager;
    HistoryManager history;

    Bookmark b1("https://uno.com", "Uno");
    Bookmark b2("https://dos.com", "Dos");

    assert(manager.addBookmark(b1));
    assert(manager.addBookmark(b2));

    // Simula el usuario eligiendo el segundo favorito
    Page p(b2.getUrl(), b2.getName());
    history.visit(p);

    Page current = history.getCurrent();
    assert(compareString(current.getUrl(), "https://dos.com") == 0);
    assert(compareString(current.getTitle(), "Dos") == 0);
}

int main() {
    integracion_test_navegar_a_favorito();
    std::cout << "✔ Integración: navegar a favorito — OK\n";
    return 0;
}

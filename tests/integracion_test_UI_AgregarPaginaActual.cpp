#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "HistoryManager.h"
#include "StringUtils.h"

void integracion_test_agregar_pagina_actual_a_favoritos() {
    BookmarkManager manager;
    HistoryManager history;

    Page actual("https://a.com", "A");
    history.visit(actual);

    Bookmark favorito(actual.getUrl(), "Test", "");
    assert(manager.addBookmark(favorito));
    assert(manager.totalBookmarks() == 1);

    const Bookmark* b = manager.atRaw(0);
    assert(compareString(b->getUrl(), "https://a.com") == 0);
    assert(compareString(b->getName(), "Test") == 0);
}

int main() {
    integracion_test_agregar_pagina_actual_a_favoritos();
    std::cout << "✔ Integración: agregar página actual a favoritos — OK\n";
    return 0;
}

#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "Bookmark.h"
#include "StringUtils.h"

void integracion_test_add_bookmark_manual() {
    BookmarkManager manager;

    // Simular entrada como lo haría ConsoleUI
    manager.addBookmark(Bookmark("https://ejemplo.com", "Ejemplo", ""));

    assert(manager.totalBookmarks() == 1);

    const Bookmark* b = manager.atRaw(0);
    assert(b != nullptr);
    assert(compareString(b->getName(), "Ejemplo") == 0);
    assert(compareString(b->getUrl(), "https://ejemplo.com") == 0);
    assert(compareString(b->getFolder(), "") == 0);
}

int main() {
    integracion_test_add_bookmark_manual();
    std::cout << "✔ Prueba de integración de agregar favorito: OK\n";
    return 0;
}

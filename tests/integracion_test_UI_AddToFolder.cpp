#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"

void integracion_test_add_bookmark_to_folder_manual() {
    BookmarkManager manager;
    manager.createFolder("Noticias");

    Bookmark b("https://noticias.com", "NoticiasHoy", "Noticias");
    manager.addBookmarkToFolder(b, "Noticias");

    const Folder* f = manager.getFolderList()->findByName("Noticias");
    assert(f != nullptr);

    BookmarkList* list = f->getList();
    assert(list->size() == 1);

    Bookmark* inside = list->at(0);
    assert(inside != nullptr);
    assert(compareString(inside->getUrl(), "https://noticias.com") == 0);
    assert(compareString(inside->getName(), "NoticiasHoy") == 0);
    assert(compareString(inside->getFolder(), "Noticias") == 0);
}

int main() {
    integracion_test_add_bookmark_to_folder_manual();
    std::cout << "✔ Prueba de integración de agregar favorito a carpeta: OK\n";
    return 0;
}

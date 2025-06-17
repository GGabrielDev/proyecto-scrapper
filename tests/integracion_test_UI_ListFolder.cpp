#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "Bookmark.h"
#include "StringUtils.h"

void integracion_test_list_folder_manual() {
    BookmarkManager manager;
    manager.createFolder("Lectura");

    Bookmark b("https://libros.com", "Libros", "Lectura");
    manager.addBookmarkToFolder(b, "Lectura");

    const Folder* f = manager.getFolderList()->findByName("Lectura");
    assert(f != nullptr);

    BookmarkList* list = f->getList();
    assert(list->size() == 1);

    Bookmark* inside = list->at(0);
    assert(inside != nullptr);
    assert(compareString(inside->getUrl(), "https://libros.com") == 0);
    assert(compareString(inside->getName(), "Libros") == 0);
}

int main() {
    integracion_test_list_folder_manual();
    std::cout << "✔ Prueba de integración de listar carpeta: OK\n";
    return 0;
}

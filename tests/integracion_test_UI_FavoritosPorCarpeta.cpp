#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "FolderList.h"
#include "StringUtils.h"

void integracion_test_favoritos_por_carpeta() {
    BookmarkManager manager;

    // Crear carpetas
    manager.createFolder("Recursos");
    manager.createFolder("Docs");

    // Agregar favoritos a carpetas
    manager.addBookmarkToFolder(Bookmark("https://cpp.com", "C++", "Recursos"), "Recursos");
    manager.addBookmarkToFolder(Bookmark("https://docs.io", "Docs", "Docs"), "Docs");

    const FolderList* folders = manager.getFolderList();
    FolderList::Node* node = folders->getHead();

    int contador = 0;

    while (node) {
        Folder* folder = &node->data;
        BookmarkList* list = folder->getList();
        assert(list->size() == 1);

        Bookmark* b = list->at(0);
        if (compareString(folder->getName(), "Recursos") == 0) {
            assert(compareString(b->getUrl(), "https://cpp.com") == 0);
        } else if (compareString(folder->getName(), "Docs") == 0) {
            assert(compareString(b->getUrl(), "https://docs.io") == 0);
        } else {
            assert(false && "Nombre de carpeta inesperado");
        }

        contador++;
        node = node->next;
    }

    assert(contador == 2);
}

int main() {
    integracion_test_favoritos_por_carpeta();
    std::cout << "✔ Prueba de integración de favoritos por carpeta: OK\n";
    return 0;
}

#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"

void integracion_test_crear_carpeta() {
    BookmarkManager manager;

    manager.createFolder("Proyectos");
    manager.createFolder("Noticias");

    const FolderList* list = manager.getFolderList();
    assert(list->findByName("Proyectos") != nullptr);
    assert(list->findByName("Noticias") != nullptr);
    assert(list->findByName("Inexistente") == nullptr);
}

int main() {
    integracion_test_crear_carpeta();
    std::cout << "✔ Prueba de creación de carpetas: OK\n";
    return 0;
}

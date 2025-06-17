#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"

void integracion_test_create_folder_manual() {
    BookmarkManager manager;

    // Simula lo que haría ConsoleUI al crear una carpeta
    manager.createFolder("Proyectos");

    assert(manager.getFolderList()->size() == 1);

    Folder* f = manager.getFolderList()->findByName("Proyectos");
    assert(f != nullptr);
    assert(compareString(f->getName(), "Proyectos") == 0);
}

int main() {
    integracion_test_create_folder_manual();
    std::cout << "✔ Prueba de integración de creación de carpeta: OK\n";
    return 0;
}

#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"

void integracion_test_favoritos_ui() {
    BookmarkManager manager;

    manager.addBookmark(Bookmark("https://ejemplo.com", "Ejemplo"));
    assert(manager.totalBookmarks() == 1);

    manager.removeBookmark("https://ejemplo.com");
    assert(manager.totalBookmarks() == 0);

    manager.restoreBookmark();
    assert(manager.totalBookmarks() == 1);

    manager.createFolder("Tareas");
    manager.addBookmarkToFolder(Bookmark("https://task.com", "Task", "Tareas"), "Tareas");

    Folder* f = manager.getFolderList()->findByName("Tareas");
    assert(f != nullptr);
    assert(f->getList()->size() == 1);
}

int main() {
    integracion_test_favoritos_ui();
    std::cout << "✔ Prueba de integración de favoritos UI: OK\n";
    return 0;
}

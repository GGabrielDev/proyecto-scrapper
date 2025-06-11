#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "Bookmark.h"
#include "StringUtils.h"

void integracion_test_folder_creation_and_count() {
    BookmarkManager manager;

    manager.createFolder("Noticias");
    manager.createFolder("Tecnología");
    manager.createFolder("Juegos");

    assert(manager.totalFolders() == 3);
}

void integracion_test_add_bookmark_to_folder_and_retrieve() {
    BookmarkManager manager;

    manager.createFolder("Favoritos");
    Bookmark b("https://ejemplo.com", "Ejemplo");

    bool added = manager.addBookmarkToFolder(b, "Favoritos");
    assert(added == true);

    Bookmark* found = manager.findBookmarkInFolder("Ejemplo", "Favoritos");
    assert(found != nullptr);
    assert(compareString(found->getUrl(), "https://ejemplo.com") == 0);
}

void integracion_test_add_to_nonexistent_folder_fails() {
    BookmarkManager manager;
    Bookmark b("https://fail.com", "Fallido");

    bool added = manager.addBookmarkToFolder(b, "NoExiste");
    assert(added == false);
}

int main() {
    integracion_test_folder_creation_and_count();
    integracion_test_add_bookmark_to_folder_and_retrieve();
    integracion_test_add_to_nonexistent_folder_fails();

    std::cout << "All integrated BookmarkManager tests passed.\n";
    return 0;
}

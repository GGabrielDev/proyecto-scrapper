#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"

void integracion_test_restore_bookmark() {
    BookmarkManager manager;

    Bookmark b1("https://a.com", "A");
    Bookmark b2("https://b.com", "B");

    assert(manager.addBookmark(b1));
    assert(manager.addBookmark(b2));
    assert(manager.totalBookmarks() == 2);

    assert(manager.removeBookmarkByUrl("https://a.com"));
    assert(manager.removeBookmarkByUrl("https://b.com"));
    assert(manager.totalBookmarks() == 0);

    assert(manager.restoreBookmark());  // restaura B
    assert(manager.totalBookmarks() == 1);
    const Bookmark* b = manager.atRaw(0);
    assert(compareString(b->getName(), "B") == 0);

    assert(manager.restoreBookmark());  // restaura A
    assert(manager.totalBookmarks() == 2);

    // No más que restaurar
    assert(!manager.restoreBookmark());
}

int main() {
    integracion_test_restore_bookmark();
    std::cout << "✔ Prueba de integración de restauración: OK\n";
    return 0;
}

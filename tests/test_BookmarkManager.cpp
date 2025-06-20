#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"

void test_add_and_remove_bookmark() {
    BookmarkManager manager;
    Bookmark b1("https://a.com", "A");
    Bookmark b2("https://b.com", "B");

    assert(manager.addBookmark(b1) == true);
    assert(manager.addBookmark(b2) == true);
    assert(manager.totalBookmarks() == 2);

    // Intentar duplicado
    assert(manager.addBookmark(b1) == false);
    assert(manager.totalBookmarks() == 2);

    bool removed = manager.removeBookmark("https://a.com");
    assert(removed == true);
    assert(manager.totalBookmarks() == 1);
}

void test_restore_bookmark() {
    BookmarkManager manager;
    Bookmark b("https://z.com", "Z");

    manager.addBookmark(b);
    manager.removeBookmark("https://z.com");

    assert(manager.totalBookmarks() == 0);

    bool restored = manager.restoreBookmark();
    assert(restored == true);
    assert(manager.totalBookmarks() == 1);
}

void test_restore_limit() {
    BookmarkManager manager;
    for (int i = 0; i < 7; ++i) {
        char url[32];
        char name[16];
        url[0] = name[0] = '\0';
        url[0] = name[0] = '\0';

        url[0] = name[0] = 'a' + i;
        url[1] = '.'; url[2] = 'c'; url[3] = 'o'; url[4] = 'm'; url[5] = '\0';
        name[1] = '\0';

        Bookmark b(url, name);
        manager.addBookmark(b);
        manager.removeBookmark(url);
    }

    int restored = 0;
    while (manager.restoreBookmark()) {
        restored++;
    }

    assert(restored == 5); // máximo de 5 restauraciones
}

void test_remove_by_name() {
    BookmarkManager manager;

    Bookmark b1("https://a.com", "A");
    Bookmark b2("https://b.com", "B");

    assert(manager.addBookmark(b1));
    assert(manager.addBookmark(b2));
    assert(manager.totalBookmarks() == 2);

    bool removed = manager.removeBookmarkByName("A");
    assert(removed == true);
    assert(manager.totalBookmarks() == 1);

    // Intentar con nombre no existente
    removed = manager.removeBookmarkByName("Inexistente");
    assert(removed == false);
    assert(manager.totalBookmarks() == 1);
}

int main() {
    test_add_and_remove_bookmark();
    test_restore_bookmark();
    test_restore_limit();
    test_remove_by_name();
    std::cout << "All BookmarkManager tests passed.\n";
    return 0;
}

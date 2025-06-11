#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"

void test_add_and_remove_bookmark() {
    BookmarkManager manager;
    Bookmark b1("https://a.com", "A");
    Bookmark b2("https://b.com", "B");

    manager.addBookmark(b1);
    manager.addBookmark(b2);
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

int main() {
    test_add_and_remove_bookmark();
    test_restore_bookmark();
    test_restore_limit();
    std::cout << "All BookmarkManager tests passed.\n";
    return 0;
}

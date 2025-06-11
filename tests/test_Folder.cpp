#include <cassert>
#include <iostream>
#include "Folder.h"
#include "StringUtils.h"

void test_folder_creation_and_name() {
    Folder f("Noticias");
    assert(compareString(f.getName(), "Noticias") == 0);

    f.setName("Tecnología");
    assert(compareString(f.getName(), "Tecnología") == 0);
}

void test_add_and_list_bookmarks() {
    Folder f("Favoritos");

    Bookmark b1("https://a.com", "A");
    Bookmark b2("https://b.com", "B");

    f.addBookmark(b1);
    f.addBookmark(b2);

    BookmarkList* list = f.getList();
    assert(list->size() == 2);

    Bookmark* found = list->findByName("A");
    assert(found != nullptr);
    assert(compareString(found->getUrl(), "https://a.com") == 0);
}

void test_remove_bookmark() {
    Folder f("Sitios");

    f.addBookmark(Bookmark("https://x.com", "X"));
    f.addBookmark(Bookmark("https://y.com", "Y"));

    bool removed = f.removeBookmark("https://x.com");
    assert(removed == true);

    BookmarkList* list = f.getList();
    assert(list->size() == 1);
    assert(list->findByName("X") == nullptr);
}

int main() {
    test_folder_creation_and_name();
    test_add_and_list_bookmarks();
    test_remove_bookmark();
    std::cout << "All Folder tests passed.\n";
    return 0;
}

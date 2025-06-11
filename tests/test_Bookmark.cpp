#include <cassert>
#include <iostream>
#include "Bookmark.h"
#include "StringUtils.h"

void test_bookmark_creation() {
    Bookmark bm("https://example.com", "Example", "Noticias");

    assert(compareString(bm.getUrl(), "https://example.com") == 0);
    assert(compareString(bm.getName(), "Example") == 0);
    assert(compareString(bm.getFolder(), "Noticias") == 0);
}

void test_set_folder() {
    Bookmark bm("https://a.com", "A");
    bm.setFolder("Favoritos");
    assert(compareString(bm.getFolder(), "Favoritos") == 0);
}

int main() {
    test_bookmark_creation();
    test_set_folder();
    std::cout << "All Bookmark tests passed.\n";
    return 0;
}

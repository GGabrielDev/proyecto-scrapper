#include <cassert>
#include <iostream>
#include "Bookmark.h"

// Versión reducida de strcmp para pruebas
int test_strcmp(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 1;
        ++i;
    }
    return (a[i] == b[i]) ? 0 : 1;
}

void test_bookmark_creation() {
    Bookmark bm("https://example.com", "Example", "Noticias");

    assert(test_strcmp(bm.getUrl(), "https://example.com") == 0);
    assert(test_strcmp(bm.getName(), "Example") == 0);
    assert(test_strcmp(bm.getFolder(), "Noticias") == 0);
}

void test_set_folder() {
    Bookmark bm("https://a.com", "A");
    bm.setFolder("Favoritos");
    assert(test_strcmp(bm.getFolder(), "Favoritos") == 0);
}

int main() {
    test_bookmark_creation();
    test_set_folder();
    std::cout << "All Bookmark tests passed.\n";
    return 0;
}

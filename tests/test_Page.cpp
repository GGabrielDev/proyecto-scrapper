#include <cassert>
#include <iostream>
#include "Page.h"
#include "StringUtils.h"

void test_page_creation() {
    Page p("https://a.com", "A");
    assert(compareString(p.getUrl(), "https://a.com") == 0);
    assert(compareString(p.getTitle(), "A") == 0);
}

void test_setters() {
    Page p;
    p.setUrl("https://b.com");
    p.setTitle("B");

    assert(compareString(p.getUrl(), "https://b.com") == 0);
    assert(compareString(p.getTitle(), "B") == 0);
}

int main() {
    test_page_creation();
    test_setters();
    std::cout << "All Page tests passed.\n";
    return 0;
}

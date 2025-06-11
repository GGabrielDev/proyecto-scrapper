#include <cassert>
#include <iostream>
#include "Bookmark.h"
#include "BookmarkList.h"
#include "StringUtils.h"

void test_add_and_size() {
    BookmarkList list;
    list.add(Bookmark("https://a.com", "A"));
    list.add(Bookmark("https://b.com", "B"));
    assert(list.size() == 2);
}

void test_find_by_name() {
    BookmarkList list;
    list.add(Bookmark("https://a.com", "A"));
    Bookmark* found = list.findByName("A");
    assert(found != nullptr);
    assert(compareString(found->getUrl(), "https://a.com") == 0);
}

void test_remove_by_url() {
    BookmarkList list;
    list.add(Bookmark("https://a.com", "A"));
    list.add(Bookmark("https://b.com", "B"));
    bool removed = list.removeByUrl("https://a.com");
    assert(removed == true);
    assert(list.size() == 1);
    assert(list.findByName("A") == nullptr);
}

void test_at() {
    BookmarkList list;
    list.add(Bookmark("https://x.com", "X"));
    list.add(Bookmark("https://y.com", "Y"));
    list.add(Bookmark("https://z.com", "Z"));
    // 'Z' está al frente porque se insertó último
    Bookmark* b = list.at(0);
    assert(compareString(b->getName(), "Z") == 0);
}

int main() {
    test_add_and_size();
    test_find_by_name();
    test_remove_by_url();
    test_at();
    std::cout << "All BookmarkList tests passed.\n";
    return 0;
}

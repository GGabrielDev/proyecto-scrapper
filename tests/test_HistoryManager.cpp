#include <cassert>
#include <iostream>
#include "HistoryManager.h"
#include "Page.h"

void test_visit_and_getCurrent() {
    HistoryManager history;
    Page p1("https://example.com", "Example");
    history.visit(p1);
    assert(history.getCurrent().getUrl() == "https://example.com");
}

void test_back_and_forward() {
    HistoryManager history;
    history.visit(Page("https://a.com", "A"));
    history.visit(Page("https://b.com", "B"));
    history.visit(Page("https://c.com", "C"));

    history.goBack();
    assert(history.getCurrent().getUrl() == "https://b.com");

    history.goBack();
    assert(history.getCurrent().getUrl() == "https://a.com");

    history.goForward();
    assert(history.getCurrent().getUrl() == "https://b.com");
}

int main() {
    test_visit_and_getCurrent();
    test_back_and_forward();
    std::cout << "All tests passed.\n";
    return 0;
}

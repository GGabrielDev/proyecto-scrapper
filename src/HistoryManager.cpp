#include "HistoryManager.h"
#include <stdexcept>

HistoryManager::HistoryManager()
    : current(nullptr) {}

HistoryManager::~HistoryManager() {
    delete current;
}

void HistoryManager::visit(const Page& page) {
    if (current) {
        backStack.push(*current);
        delete current;
    }
    current = new Page(page);
    forwardStack.clear();
}

void HistoryManager::goBack() {
    if (!backStack.isEmpty()) {
        forwardStack.push(*current);
        delete current;
        current = new Page(backStack.pop());
    }
}

void HistoryManager::goForward() {
    if (!forwardStack.isEmpty()) {
        backStack.push(*current);
        delete current;
        current = new Page(forwardStack.pop());
    }
}

Page HistoryManager::getCurrent() const {
    if (!current) throw std::runtime_error("No current page");
    return *current;
}

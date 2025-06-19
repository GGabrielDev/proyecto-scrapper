#include "HistoryManager.h"

HistoryManager::HistoryManager() : hasCurrent(false) {}

void HistoryManager::visit(const Page& page) {
    if (hasCurrent) {
        backStack.push(current);
    }
    current = page;
    hasCurrent = true;
    forwardStack.clear();
}

void HistoryManager::goBack() {
    if (backStack.isEmpty()) return;
    forwardStack.push(current);
    current = backStack.pop();
}

void HistoryManager::goForward() {
    if (forwardStack.isEmpty()) return;
    backStack.push(current);
    current = forwardStack.pop();
}

Page HistoryManager::getCurrent() const {
    return current;
}

bool HistoryManager::canGoBack() const {
    return !backStack.isEmpty();
}

bool HistoryManager::canGoForward() const {
    return !forwardStack.isEmpty();
}

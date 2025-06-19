#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include "Page.h"
#include "PageStack.h"

class HistoryManager {
private:
    PageStack backStack;
    PageStack forwardStack;
    Page current;
    bool hasCurrent;

public:
    HistoryManager();

    void visit(const Page& page);
    void goBack();
    void goForward();
    Page getCurrent() const;
    bool canGoBack() const;
    bool canGoForward() const;
};

#endif // HISTORY_MANAGER_H

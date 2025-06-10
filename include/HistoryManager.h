#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include "Page.h"
#include "PageStack.h"

class HistoryManager {
private:
    PageStack backStack;
    PageStack forwardStack;
    Page* current;

public:
    HistoryManager();
    ~HistoryManager();

    void visit(const Page& page);
    void goBack();
    void goForward();
    Page getCurrent() const;
};

#endif // HISTORY_MANAGER_H

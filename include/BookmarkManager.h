#ifndef BOOKMARK_MANAGER_H
#define BOOKMARK_MANAGER_H

#include "BookmarkList.h"
#include "Bookmark.h"

class BookmarkManager {
private:
    BookmarkList list;

    struct StackNode {
        Bookmark data;
        StackNode* next;
        StackNode(const Bookmark& b) : data(b), next(nullptr) {}
    };

    StackNode* deletedTop;
    int deletedCount;

    void pushDeleted(const Bookmark& b);
    Bookmark popDeleted();
    void clearDeletedStack();

public:
    BookmarkManager();
    ~BookmarkManager();

    void addBookmark(const Bookmark& b);
    bool removeBookmark(const char* url);
    bool restoreBookmark();

    int totalBookmarks() const;
};

#endif // BOOKMARK_MANAGER_H

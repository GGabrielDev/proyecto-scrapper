#ifndef BOOKMARK_MANAGER_H
#define BOOKMARK_MANAGER_H

#include "BookmarkList.h"
#include "Bookmark.h"
#include "FolderList.h"

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

    FolderList folders;

    void pushDeleted(const Bookmark& b);
    Bookmark popDeleted();
    void clearDeletedStack();

public:
    BookmarkManager();
    ~BookmarkManager();

    const Bookmark* atRaw(int index) const;
    const FolderList* getFolderList() const;

    bool addBookmark(const Bookmark& b);
    bool removeBookmark(const char* url);
    bool restoreBookmark();
    int totalBookmarks() const;

    void createFolder(const char* name);
    bool addBookmarkToFolder(const Bookmark& b, const char* folderName);
    Bookmark* findBookmarkInFolder(const char* name, const char* folderName);
    int totalFolders() const;

    void saveToDisk(const char* bookmarksPath, const char* foldersPath);
    void loadFromDisk(const char* bookmarksPath, const char* foldersPath);
};

#endif // BOOKMARK_MANAGER_H

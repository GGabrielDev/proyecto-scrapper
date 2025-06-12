#ifndef FOLDER_H
#define FOLDER_H

#include "BookmarkList.h"

class Folder {
private:
    char name[256];
    BookmarkList list;

public:
    Folder(const char* name);

    const char* getName() const;
    void setName(const char* newName);

    void addBookmark(const Bookmark& b);
    bool removeBookmark(const char* url);
    BookmarkList* getList() const;
};

#endif // FOLDER_H

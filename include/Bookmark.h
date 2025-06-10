#ifndef BOOKMARK_H
#define BOOKMARK_H

class Bookmark {
private:
    char url[256];
    char name[256];
    char folder[256];

public:
    Bookmark(const char* url, const char* name, const char* folder = "");

    const char* getUrl() const;
    const char* getName() const;
    const char* getFolder() const;

    void setFolder(const char* newFolder);
};

#endif // BOOKMARK_H

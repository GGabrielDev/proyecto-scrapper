#ifndef PAGE_H
#define PAGE_H

class Page {
private:
    char url[256];
    char title[256];

public:
    Page();
    Page(const char* url, const char* title);

    const char* getUrl() const;
    const char* getTitle() const;

    void setUrl(const char* newUrl);
    void setTitle(const char* newTitle);
};

#endif // PAGE_H

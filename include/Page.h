#ifndef PAGE_H
#define PAGE_H

#include <string>

class Page {
private:
    std::string url;
    std::string title;

public:
    Page(const std::string& url, const std::string& title);
    std::string getUrl() const;
    std::string getTitle() const;
};

#endif // PAGE_H

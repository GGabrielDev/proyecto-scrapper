#include "Page.h"

Page::Page(const std::string& url, const std::string& title)
    : url(url), title(title) {}

std::string Page::getUrl() const {
    return url;
}

std::string Page::getTitle() const {
    return title;
}

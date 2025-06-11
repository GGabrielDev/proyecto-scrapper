#include "Page.h"
#include "StringUtils.h"

Page::Page() {
    url[0] = '\0';
    title[0] = '\0';
}

Page::Page(const char* u, const char* t) {
    copyString(url, u, 256);
    copyString(title, t, 256);
}

const char* Page::getUrl() const {
    return url;
}

const char* Page::getTitle() const {
    return title;
}

void Page::setUrl(const char* newUrl) {
    copyString(url, newUrl, 256);
}

void Page::setTitle(const char* newTitle) {
    copyString(title, newTitle, 256);
}

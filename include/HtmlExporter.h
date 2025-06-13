#ifndef HTML_EXPORTER_H
#define HTML_EXPORTER_H

#include "BookmarkManager.h"

class HtmlExporter {
public:
    static bool exportToFile(const BookmarkManager& manager, const char* filePath);
};

#endif // HTML_EXPORTER_H

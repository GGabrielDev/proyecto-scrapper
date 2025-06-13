#include "HtmlExporter.h"
#include "BookmarkManager.h"
#include "BookmarkList.h"
#include "FolderList.h"
#include "Folder.h"
#include <cstdio>

bool HtmlExporter::exportToFile(const BookmarkManager& manager, const char* filePath) {
    FILE* f = fopen(filePath, "w");
    if (!f) return false;

    fprintf(f, "<!DOCTYPE html>\n<html>\n<head><meta charset=\"UTF-8\"><title>Favoritos</title></head>\n<body>\n");
    fprintf(f, "<h1>Favoritos</h1>\n");

    // Favoritos sin carpeta
    fprintf(f, "<h2>Sin carpeta</h2>\n<ul>\n");
    for (int i = 0; i < manager.totalBookmarks(); ++i) {
        const Bookmark* b = manager.atRaw(i);
        if (b && b->getFolder()[0] == '\0') {
            fprintf(f, "<li><a href=\"%s\">%s</a></li>\n", b->getUrl(), b->getName());
        }
    }
    fprintf(f, "</ul>\n");

    // Favoritos por carpeta
    FolderList::Node* node = manager.getFolderList()->getHead();
    while (node) {
        const Folder& folder = node->data;
        fprintf(f, "<h2>%s</h2>\n<ul>\n", folder.getName());

        BookmarkList* list = folder.getList();
        for (int j = 0; j < list->size(); ++j) {
            Bookmark* b = list->at(j);
            if (b) {
                fprintf(f, "<li><a href=\"%s\">%s</a></li>\n", b->getUrl(), b->getName());
            }
        }

        fprintf(f, "</ul>\n");
        node = node->next;
    }

    fprintf(f, "</body>\n</html>\n");
    fclose(f);
    return true;
}

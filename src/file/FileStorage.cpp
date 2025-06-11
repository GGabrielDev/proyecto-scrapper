#include <cstdio>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0755)
#endif

#include "FileStorage.h"
#include "Bookmark.h"
#include "StringUtils.h"

// Extracts directory from path (e.g. "data/bookmarks.txt" -> "data")
void extractDirectory(const char* filePath, char* output, int maxLen) {
    int len = 0;
    for (int i = 0; filePath[i] != '\0' && len < maxLen - 1; ++i) {
        if (filePath[i] == '/' || filePath[i] == '\\') {
            len = i;
        }
    }

    for (int i = 0; i <= len && i < maxLen - 1; ++i) {
        output[i] = filePath[i];
    }
    output[len + 1] = '\0';
}

bool FileStorage::saveBookmarks(const BookmarkList& list, const char* filePath) {
    // Crear carpeta si no existe
    char folder[256];
    extractDirectory(filePath, folder, 256);
    MKDIR(folder); // Ignoramos si ya existe

    FILE* f = std::fopen(filePath, "w");
    if (!f) return false;

    for (int i = 0; i < list.size(); ++i) {
        Bookmark* b = list.at(i);
        if (b) {
            std::fprintf(f, "%s|%s|%s\n", b->getUrl(), b->getName(), b->getFolder());
        }
    }

    std::fclose(f);
    return true;
}

bool FileStorage::loadBookmarks(BookmarkList& list, const char* filePath) {
    FILE* f = std::fopen(filePath, "r");
    if (!f) return false;

    char line[768];
    char url[256], name[256], folder[256];

    while (std::fgets(line, sizeof(line), f)) {
        int i = 0, j = 0;

        // Extraer URL
        while (line[i] != '|' && line[i] != '\0' && j < 255) {
            url[j++] = line[i++];
        }
        url[j] = '\0';
        i++; j = 0;

        // Extraer NAME
        while (line[i] != '|' && line[i] != '\0' && j < 255) {
            name[j++] = line[i++];
        }
        name[j] = '\0';
        i++; j = 0;

        // Extraer FOLDER (hasta fin de línea o \n)
        while (line[i] != '\n' && line[i] != '\0' && j < 255) {
            folder[j++] = line[i++];
        }
        folder[j] = '\0';

        list.add(Bookmark(url, name, folder));
    }

    std::fclose(f);
    return true;
}

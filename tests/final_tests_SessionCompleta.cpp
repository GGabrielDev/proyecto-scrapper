#include <cassert>
#include <iostream>
#include <filesystem>
#include "BookmarkManager.h"
#include "HistoryManager.h"
#include "FileStorage.h"
#include "HtmlExporter.h"
#include "StringUtils.h"

void final_tests_sesion_completa() {
    // Preparación
    const char* dir = "data_test";
    const char* fileBookmarks = "data_test/bookmarks.txt";
    const char* fileFolders   = "data_test/folders.txt";
    const char* fileHtml      = "data_test/export.html";

    std::filesystem::create_directory(dir);

    BookmarkManager manager;
    HistoryManager history;

    // 1. Navegar a página
    Page actual("https://final.test", "Final Test");
    history.visit(actual);
    assert(compareString(history.getCurrent().getUrl(), "https://final.test") == 0);

    // 2. Guardar como favorito
    Bookmark favorito(actual.getUrl(), "Test", "");
    assert(manager.addBookmark(favorito));

    // 3. Crear carpeta y agregar favorito duplicado dentro
    manager.createFolder("Trabajo");
    Bookmark favorito2(actual.getUrl(), "Test Copia", "Trabajo");
    assert(manager.addBookmarkToFolder(favorito2, "Trabajo"));

    // 4. Guardar a disco
    manager.saveToDisk(fileBookmarks, fileFolders);
    assert(std::filesystem::exists(fileBookmarks));
    assert(std::filesystem::exists(fileFolders));

    // 5. Simular nueva sesión (nuevo manager)
    BookmarkManager nuevo;
    nuevo.loadFromDisk(fileBookmarks, fileFolders);
    assert(nuevo.totalBookmarks() == 1);  // solo el favorito sin carpeta

    // 6. Navegar al favorito cargado
    const Bookmark* b = nuevo.atRaw(0);
    history.visit(Page(b->getUrl(), b->getName()));
    assert(compareString(history.getCurrent().getTitle(), "Test") == 0);

    // 7. Exportar a HTML
    bool exported = HtmlExporter::exportToFile(nuevo, fileHtml);
    assert(exported);
    assert(std::filesystem::exists(fileHtml));

    // Limpieza (eliminar archivos si carpeta vacía)
    std::filesystem::remove(fileBookmarks);
    std::filesystem::remove(fileFolders);
    std::filesystem::remove(fileHtml);
    if (std::filesystem::is_empty(dir)) {
        std::filesystem::remove(dir);
    }

    std::cout << "✔ Prueba final de sesión completa — OK\n";
}

int main() {
    final_tests_sesion_completa();
    return 0;
}

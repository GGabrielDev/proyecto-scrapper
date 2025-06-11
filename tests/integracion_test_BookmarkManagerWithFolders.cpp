#include <cassert>
#include <iostream>
#include "BookmarkManager.h"
#include "StringUtils.h"
#include "FolderList.h"
#include "Folder.h"
#include "Bookmark.h"

// Simulación mínima del futuro BookmarkManager extendido
class TestableBookmarkManager {
private:
    FolderList folders;

public:
    void createFolder(const char* name) {
        if (!folders.findByName(name)) {
            folders.add(Folder(name));
        }
    }

    bool addBookmarkToFolder(const Bookmark& b, const char* folderName) {
        Folder* folder = folders.findByName(folderName);
        if (!folder) return false;
        folder->addBookmark(b);
        return true;
    }

    Bookmark* findBookmarkInFolder(const char* name, const char* folderName) {
        Folder* folder = folders.findByName(folderName);
        if (!folder) return nullptr;
        return folder->getList()->findByName(name);
    }

    int totalFolders() const {
        return folders.size();
    }
};

void integracion_test_create_and_use_folder() {
    TestableBookmarkManager manager;

    manager.createFolder("Tecnología");
    manager.createFolder("Noticias");
    assert(manager.totalFolders() == 2);
}

void integracion_test_add_and_find_bookmark_in_folder() {
    TestableBookmarkManager manager;
    manager.createFolder("Libros");

    Bookmark b("https://libros.com", "Libros Online");
    bool added = manager.addBookmarkToFolder(b, "Libros");
    assert(added == true);

    Bookmark* found = manager.findBookmarkInFolder("Libros Online", "Libros");
    assert(found != nullptr);
    assert(compareString(found->getUrl(), "https://libros.com") == 0);
}

void integracion_test_fail_to_add_to_nonexistent_folder() {
    TestableBookmarkManager manager;

    Bookmark b("https://fail.com", "ShouldFail");
    bool added = manager.addBookmarkToFolder(b, "NoExiste");
    assert(added == false);
}

int main() {
    integracion_test_create_and_use_folder();
    integracion_test_add_and_find_bookmark_in_folder();
    integracion_test_fail_to_add_to_nonexistent_folder();

    std::cout << "All integration tests for folder handling passed.\n";
    return 0;
}

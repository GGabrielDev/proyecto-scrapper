#include <cassert>
#include <iostream>
#include "FolderList.h"
#include "StringUtils.h"

void test_add_and_find_folder() {
    FolderList folders;
    folders.add(Folder("Noticias"));
    folders.add(Folder("Juegos"));

    Folder* f = folders.findByName("Noticias");
    assert(f != nullptr);
    assert(compareString(f->getName(), "Noticias") == 0);
}

void test_folder_list_size() {
    FolderList folders;
    folders.add(Folder("A"));
    folders.add(Folder("B"));
    folders.add(Folder("C"));
    assert(folders.size() == 3);
}

int main() {
    test_add_and_find_folder();
    test_folder_list_size();
    std::cout << "All FolderList tests passed.\n";
    return 0;
}

#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

class MenuHandler {
public:
    static void verFavoritos();
    static void verPorCarpeta();
    static void agregarFavorito();
    static void eliminarFavorito();
    static void crearCarpeta();
    static void agregarAFavoritoEnCarpeta();
    static void guardar();
    static void cargar();
    static void exportarHtml();
};

#endif // MENU_HANDLER_H

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// Copia una cadena de caracteres con límite de longitud, asegurando null terminación
void copyString(char* dest, const char* src, int maxLen);

// Compara dos cadenas; devuelve 0 si son iguales, distinto si no
int compareString(const char* a, const char* b);

#endif // STRING_UTILS_H

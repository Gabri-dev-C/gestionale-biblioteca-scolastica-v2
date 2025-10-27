#ifndef GH_STRING_H
#define GH_STRING_H

// Libreria personale gh_string.
// Funzioni per la gestione di stringhe con array di char.
// Autore: Gabriele Henriet


// Funzione: gh_length
// restituisce la lunghezza di una stringa (escluso '\0')
int gh_length(const char s[]);

// Funzione: gh_strcmp
// confronta due stringhe e ritorna:
// 0 se uguali.
// < 0 se prima stringa è più corta.
// > 0 se prima stringa è pià lunga.
int gh_strcmp(const char s1[], const char s2[]);

// Funzione: gh_strcpy
// copia la stringa sorgente nella stringa di destinazione
// assicurarsi che dest abbia spazio sufficente
// modifica in-place
void gh_strcpy(char dest[], const char src[]);

// Funzione: gh_strcat
// concatena le due stringhe s1 e s2,
// s1 deve avere spazio sufficiente per contenere entrambe
// modifica in-place s1
void gh_strcat(char s1[], const char s2[]);

// Funzione: gh_strrev
// Inverte la stringa s
// modifica in-place
void gh_strrev(char s[]);

// Funzione: gh_strchar
// Ricerca il carattere c all'interno della stringa s
// ritorna >= 0: posizione del carattere.
// ritorna -1: se non trovato.
int gh_strchr(const char s[], const char c);

// Funzione: gh_toUpper
// converte tutti i caratteri della stringa s in maiuscolo
// modifica in-place.
void gh_toUpper(char s[]);

// Funzione: gh_toLower
// converte tutti i caratteri della stringa s in minuscolo
// modifica in-place.
void gh_toLower(char s[]);

// Funzione: gh_trim
// Elimina tutti gli spazi a inizio e fine della stringa s
// modifica in-place
void gh_trim(char s[]);

// Funzione gh_remove_double_space
// scandisce la stringa ed elimina i doppi spazi
// modifica in-place
void gh_remove_double_space(char stringa[]);

// Funzione gh_capitalize_first
// converte il primo carattere della stringa s
// in maiuscolo se è minuscolo
// modifica in-place
void gh_capitalize_first(char s[]);

// Funzione gh_capitalize_word
// converte il primo carattere di ogni
// parola della stringa s in maiuscolo se è minuscolo,
// modifica in-place
void gh_capitalize_word(char s[]);

#endif

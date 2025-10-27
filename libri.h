#ifndef LIBRI_H_INCLUDED
#define LIBRI_H_INCLUDED

#include "utility.h"
#include "config.h"

// modulo per la gestione dei libri della biblioteca
// scritto da Gabriele Henriet

// struttura libro
struct libro{
    int id;
    char titolo[MAX_TITOLO];
    char autore[MAX_AUTORE];
    int anno_pubblicazione;
    int copie_disponibili;
    int libero_succ;
};

// Controller di gestione dei libri, funzione con sotto-menu
int dati_libri(libro registro[], int primo_libero);

// CRUD
int nuovo_libro(libro registro[], int primo_libero);
void modifica_libro(libro registro[]);
int elimina_libro(libro registro[], int primo_libero);
int cerca_libro(libro registro[], const char titolo[]);       // ritorna l'indice

// utilità
void visualizza_header_libro();
void visualizza_libro(libro registro[], int indice);

// file
int salva_libri(libro registro[]);      // slvataggio dati su file binario
int carica_libri(libro registro[]);     // caricamento dati da file binario

#endif // LIBRI_H_INCLUDED

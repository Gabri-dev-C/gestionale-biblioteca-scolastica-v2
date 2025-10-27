#ifndef UTENTI_H_INCLUDED
#define UTENTI_H_INCLUDED

#include "utility.h"
#include "config.h"

// struttura utente
struct utente{
    int id;
    char nome[MAX_NOME];
    char cognome[MAX_COGNOME];
    int classe;
    char sezione;
    int libero_succ;
};

// Modulo per la gestione dei libri della biblioteca.
// Scritto da Gabriele Henriet

// Controller principale
int dati_utenti(utente registro[], int primo_libero);

// CRUD
int nuovo_utente(utente registro[], int primo_libero);
void modifica_utente(utente registro[]);
int elimina_utente(utente registro[], int primo_libero);
int cerca_utente(utente registro[], char cognome[], int pos_ini);

// utilità
void visualizza_header_utente();
void visualizza_utente(utente registro[], int indice);

// file
int carica_utenti(utente registro[]);   // caricamento dati da file binario
int salva_utenti(utente registro[]);    // slvataggio dati su file binario

#endif // UTENTI_H_INCLUDED

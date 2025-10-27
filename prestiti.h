#ifndef PRESTITI_H_INCLUDED
#define PRESTITI_H_INCLUDED
#include "libri.h"
#include "utenti.h"
#include "config.h"

// Modulo per la gestione dei libri della biblioteca.
// Scritto da Gabriele Henriet

struct prestito{		                // struttura prestito, combina id libro e id alunno
    int id;
    int id_libro;
    int id_utente;
    char data_prestito[MAX_DATA];
    char data_restituzione[MAX_DATA];
    int stato;			                // stato del prestito 1 attivo, 0 non attivo
    char note[MAX_NOTE];
};

// Controller principale
int dati_prestiti(prestito registro_pre[], libro registro_lib[], utente registro_ute[], int primo_libero);

// CRUD
int nuovo_prestito(prestito registro_pre[], libro registro_lib[], utente registro_ute[], int primo_libero);
int cerca_prestito(prestito registro_pre[], int id_utente, int primo_libero, int pos_ini);


// utilità
void visualizza_header_prestiti();
void visualizza_dati_prestito(prestito registro_pre[], int indice_prestito);
void visualizza_prestiti(prestito registro_pre[], int primo_libero);

// funzionalità
void restituzione_prestito(prestito registro_pre[], libro registro_lib[], utente registro_ute[], int primo_libero);

// file
int carica_prestiti(prestito registro[]);                       // carica dati da file binario
int salva_prestiti(prestito registro[]);                        // salva dati su file binario

#endif // PRESTITI_H_INCLUDED

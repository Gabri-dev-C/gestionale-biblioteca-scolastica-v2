#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

// costanti per il modulo libri
#define MAX_LIBRI 10000
#define MAX_TITOLO 30
#define MAX_AUTORE 30
#define FILE_LIBRI "libri.dat"

// costanti per il modulo utenti
#define MAX_UTENTI 10000
#define MAX_NOME 20
#define MAX_COGNOME 20
#define FILE_UTENTI "utenti.dat"

// costanti per il modulo prestiti
#define MAX_PRESTITI 700000
#define MAX_DATA 11
#define MAX_NOTE 500
#define FILE_PRESTITI "prestiti.dat"

// set di caratteri ammessi
#define ALFA_LOWERCASE "abcdefghijklmnopqrstuvwxyz"     // lettere minuscole
#define ALFA_UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"     // lettere maiuscole
#define ALFA ALFA_LOWERCASE ALFA_UPPERCASE              // minuscole + maiuscole
#define NUMERI "0123456789"
#define SPAZI " "                                       // spazio singolo
// Caratteri speciali (attenzione a '-' che deve essere ultimo
// perche' puo' essere interpretato come un in tervallo da - a)
#define PUNTEGGIATURA ".,'!?-"
#define ACCENTI "àèéìòù"

// set compositi
#define SET_TITOLO ALFA NUMERI SPAZI PUNTEGGIATURA ACCENTI          // per titolo libro
#define SET_AUTORE ALFA SPAZI ACCENTI PUNTEGGIATURA                 // per autore
#define SET_UTENTE ALFA SPAZI ACCENTI                               // per utente
#endif // CONFIG_H_INCLUDED

#include "config.h"        // tutte le costanti e nomi di file
#include "utility.h"       // funzioni di supporto come crea_menu()
#include "libri.h"         // struttura libro e funzioni correlate
#include "utenti.h"        // struttura utente e funzioni utenti
#include "prestiti.h"      // struttura prestito e funzioni relative
#include <iostream>
using namespace std;

// creo registri dei dati
libro registro_libri[MAX_LIBRI];
utente registro_utenti[MAX_UTENTI];
prestito registro_prestiti[MAX_PRESTITI];

int main(){
    char scelta;                                    // scelta utente
    string menu = "Libri;Utenti;Prestiti;";         // menu principale
    int i;                                          // indice registri

    int primo_libero_libri;                         // primo posto libero registro libri
    int primo_libero_utenti;                        // primo posto libero registro utenti
    int primo_libero_prestiti;                      // primo posto libero registro prestiti


    // carico i dati nel registro libri
    int err_carica_libri = carica_libri(registro_libri);
    if(err_carica_libri == 0){
        // inizializzazione primo_libero_libri
        i = 0;
        while(i < MAX_LIBRI){
            if(registro_libri[i].id == -2){
                primo_libero_libri = i;
                break;
            }else{
                i++;
            }
        }
        if(i >= MAX_LIBRI){
            cout << "\tAVVISO: registro pieno, impossibile aggiungere libri";
            primo_libero_libri = -1;
            premi_invio();
        }
    }else if(err_carica_libri == -1){                   // primo avvio - il file non esiste

        // inizializzo sentinelle a -1
        for(int i = 0; i < MAX_LIBRI; i++){
            registro_libri[i].id = -1;
            registro_libri[i].titolo[0] = '\0';
            registro_libri[i].autore[0] = '\0';
            registro_libri[i].anno_pubblicazione = 0;
            registro_libri[i].copie_disponibili = 0;
            registro_libri[i].libero_succ = -1;
        }

        // inizializzo primo_libero e sentinella a -2
        primo_libero_libri = 0;
        registro_libri[primo_libero_libri].id = -2;

        // creo il file libri.txt e salvo il registro
        salva_libri(registro_libri);

    }else if(err_carica_libri == -2){
        cout << "\tERRORE LIBRI: il file e' corrotto, il programma verra' chiuso";
        premi_invio();
        return 1;

    }else if(err_carica_libri == -3){
        cout << "\tERRORE LIBRI: overflow della memoria libri, il programma verra' chiuso";
        premi_invio();
        return 1;
    }


    // carico i dati nel registro utenti
    int err_carica_utenti = carica_utenti(registro_utenti);
    if(err_carica_utenti == 0){
        i = 0;
        while(i < MAX_UTENTI){
            if(registro_utenti[i].id == -2){
                primo_libero_utenti = i;
                break;
            }else{
                i++;
            }
        }

        // controllo registro pieno
        if(i >= MAX_UTENTI){
            cout << "\tAVVISO: registro pieno, impossibile aggiungere utenti";
            primo_libero_utenti = -1;
            premi_invio();
        }
    }else if(err_carica_utenti == -1){      // primo avvio - il file non esiste

        // inizializzo sentinelle a -1
        for(int i = 0; i < MAX_UTENTI; i++){
            registro_utenti[i].id = -1;
            registro_utenti[i].nome[0] = '\0';
            registro_utenti[i].cognome[0] = '\0';
            registro_utenti[i].classe = 0;
            registro_utenti[i].sezione = ' ';
            registro_utenti[i].libero_succ = -1;
        }

        // inizializzo primo_libero e sentinella a -2
        primo_libero_utenti = 0;
        registro_utenti[primo_libero_utenti].id = -2;

        // creo il file utenti.txt e salvo il registro
        salva_utenti(registro_utenti);

    }else if(err_carica_utenti == -2){
        cout << "ERRORE: il file e' corrotto, il programma verra' chiuso";
        premi_invio();
        return 1;
    }else if(err_carica_utenti == -3){
        cout << "ERRORE: overflow della memoria utenti, il programma verra' chiuso";
        premi_invio();
        return 1;
    }


    // carico i dati nel registro prestiti
    int err_carica_prestiti = carica_prestiti(registro_prestiti);

    if(err_carica_prestiti == 0){

        // inizializzazione primo_libero_prestiti
        // per i prestiti non è prevista cancellazione
        // quindi il primo posto libero è in fondo al registro
        i = 0;
        while(i < MAX_PRESTITI){
            if(registro_prestiti[i].id == -1){
                primo_libero_prestiti = i;
                break;
            }else{
                i++;
            }
        }
        if(i >= MAX_PRESTITI){
            cout << "\tAvviso: registro pieno, impossibile aggiungere prestiti";
            primo_libero_prestiti = -1;
            premi_invio();
        }
    }else if(err_carica_prestiti == -1){        // primo avvio - il file non esiste

        // inizializzo sentinella a -1
        for(int i = 0; i < MAX_PRESTITI; i++){
            registro_prestiti[i].id = -1;
            registro_prestiti[i].id_libro = -1;
            registro_prestiti[i].id_utente = -1;
            registro_prestiti[i].data_prestito[0] = '\0';
            registro_prestiti[i].data_restituzione[0] = '\0';
            registro_prestiti[i].stato = 0;
            registro_prestiti[i].note[0] = '\0';
        }

        primo_libero_prestiti = 0;

        // creo il file prestiti.txt e salvo il registro
        salva_prestiti(registro_prestiti);

    }else if(err_carica_prestiti == -2){
        cout << "ERRORE: il file e' corrotto, il programma verra' chiuso";
        premi_invio();
        return 1;
    }else if(err_carica_prestiti == -3){
        cout << "ERRORE: overflow della memoria prestiti, il programma verra' chiuso";
        premi_invio();
        return 1;
    }

    do{
        pulisci_schermo();
        crea_menu("Menu principale", menu);
        cout << "\tOperazione da svolgere: ";
        cin >> scelta;

        switch(scelta){
        case '1':
            primo_libero_libri = dati_libri(registro_libri, primo_libero_libri);
            break;
        case '2':
            primo_libero_utenti = dati_utenti(registro_utenti, primo_libero_utenti);
            break;
        case '3':
            primo_libero_prestiti = dati_prestiti(registro_prestiti, registro_libri, registro_utenti, primo_libero_prestiti);
            break;
        }
    }while(scelta != '9');
    return 0;
}

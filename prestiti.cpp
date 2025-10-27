#include "prestiti.h"
#include "utenti.h"
#include "libri.h"
#include "utility.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::cerr;
using std::setfill;
using std::endl;
using std::left;

// Funzione dati_prestiti()
// e' il controller principale della sezione prestiti
// gestisce tutti dati dei prestiti e ritorna il primo posto libero
// del registro prestiti.
int dati_prestiti(prestito registro_pre[], libro registro_lib[], utente registro_ute[], int primo_libero){

    char scelta;
    string stringa_menu = "Nuovo prestito;Restituzione libro;Visualizza prestiti";
    do{
        // sotto-menu prestiti
        crea_menu("Menu prestiti", stringa_menu);
        cout << "\tInserisci l'operazione da svolgere: ";
        cin >> scelta;
        cin.ignore();

        switch(scelta){
        case '1':
            if(primo_libero == -1){
                cerr << "\tERRORE: registro pieno, aumentare memoria registro";
                pulisci_schermo();
            }else{
                int copia_primo_libero;
                copia_primo_libero = nuovo_prestito(registro_pre, registro_lib, registro_ute, primo_libero);
                if(copia_primo_libero >= 0){
                    primo_libero = copia_primo_libero;
                }
                if(copia_primo_libero == -1){
                    cerr << "\tERRORE: libro non trovato\n";
                    premi_invio();
                }
                if(copia_primo_libero == -2){
                    cerr << "\tERRORE: utente non trovato\n";
                    premi_invio();
                }
                if(copia_primo_libero == -3){
                    cerr << "\tERRORE: id immesso non corretto\n";
                    premi_invio();
                }
            }
            break;
        case '2':
            restituzione_prestito(registro_pre, registro_lib, registro_ute, primo_libero);
            break;
        case '3':
            visualizza_prestiti(registro_pre, primo_libero);
            premi_invio();
            break;
        }
    }while(scelta != '9');

    int err = salva_prestiti(registro_pre);
    if(err == -1){
        cerr << "\tErrore apertura file, i dati non sono stati salvati, reinserirli.\n";
        premi_invio();
    }else if(err == -2){
        cerr << "\tErrore scrittura file, i dati non sono stati salvati, reinserirli.\n";
        premi_invio();
    }else{
        return primo_libero;		// ritorna il primo posto libero del vettore
    }
}


// Funzione nuovo_prestito()
// aggiunge un nuovo prestito al registro dei prestiti
// richiede tutti i dati tranne l'id che viene aggiunto in automatico
// ritorna:
// >0 la prima posizione libera del registro
// -1 se non trova il libro
// -2 se non trova l'utente
// -3 se non trova l'id dell'utente
int nuovo_prestito(prestito registro_pre[], libro registro_lib[], utente registro_ute[], int primo_libero){

    char cognome[MAX_COGNOME];		    // cognome dell'utente
    char titolo[MAX_TITOLO];		    // titolo del libro
    int ind_libro = -1;		            // indice del libro nel registro
    int ind_utente = -1;		        // indice dell'utente nel registro
    int id_libro = 0;
    int id_utente = 0;
    bool trovati = false;

    // id del prestito in automatico
    registro_pre[primo_libero].id = primo_libero + 1;

    // trovo l'id del libro
    cout << "\tInserisci il titolo del libro: ";
    cin.getline(titolo, MAX_TITOLO);
    valida_sicurezza_stringa(titolo, MAX_TITOLO, SET_TITOLO);
    ind_libro = cerca_libro(registro_lib, titolo);
    if(ind_libro == -1){
        return -1;          // titolo non trovato
    }
    id_libro = registro_lib[ind_libro].id;

    // trovo l'id dell'utente
    cout << "\tInserisci il cognome dell'utente: ";
    cin.getline(cognome, MAX_COGNOME);
    valida_sicurezza_stringa(cognome, MAX_COGNOME, SET_UTENTE);

    visualizza_header_utente();
    while((ind_utente = cerca_utente(registro_ute, cognome, ind_utente)) != -1){
        visualizza_utente(registro_ute, ind_utente);
        trovati = true;
        ind_utente++;
    }
    if(!trovati){
        return -2;                                  // cognome non trovato
    }
    cout << endl;
    cout << "\tInserisci l'id dell'utente: ";       // gestisco gli omonimi
    cin >> id_utente;
    cin.ignore();

    // trovo l'indice corretto dell'utente
    for(int i = 0; i < MAX_UTENTI; i++){
        if(registro_ute[i].id == id_utente && registro_ute[i].libero_succ == -2 && gh_strcmp(registro_ute[i].cognome, cognome) == 0){
            ind_utente = i;
            break;
        }
    }
    if(ind_utente == -1){
        return -3;                                  // id non trovato
    }

    // memorizzo in prestito gli id di alunno e libro
    registro_pre[primo_libero].id_utente = registro_ute[ind_utente].id;
    registro_pre[primo_libero].id_libro = registro_lib[ind_libro].id;

    // memorizzo gli altri dati
    cout << "\tInserisci la data del prestito: ";
    cin.getline(registro_pre[primo_libero].data_prestito, MAX_DATA);
    gh_strcpy(registro_pre[primo_libero].data_restituzione, "");
    registro_pre[primo_libero].stato = 1;
    gh_strcpy(registro_pre[primo_libero].note, "");

    // aggiorno le copie disponibili
    registro_lib[ind_libro].copie_disponibili--;

    cout << "\tPrestito memorizzato con successo\n";
    premi_invio();

    return ++primo_libero;	// ritorna la prima posizione libera del registro
}

// cerca l'utente per cognome
// visualizza i suoi prestiti aperti
// chiude il prestito selezionato
void restituzione_prestito(prestito registro_pre[], libro registro_lib[], utente registro_ute[], int primo_libero){

    char cognome_cercato[MAX_COGNOME] = "";
    int id_utente;
    int id_prestito;
    bool id_corretto = false;
    int ind_prestito = 0;
    int ind_utente;
    int i = 0;              // indice registro prestiti
    int j = 0;              // indice registro libri

    // trovo gli utenti omonimi con un prestito aperto
    pulisci_schermo();

    do{
        ind_utente = 0;
        i = 0;

        cout << "\tInserisci il cognome dell' utente: ";
        cin.getline(cognome_cercato, MAX_COGNOME);
        valida_sicurezza_stringa(cognome_cercato, MAX_COGNOME, SET_UTENTE);

        // visualizzo utenti omonimi
        visualizza_header_utente();
        while((ind_utente = cerca_utente(registro_ute, cognome_cercato, ind_utente)) != -1){
            visualizza_utente(registro_ute, ind_utente);
            ind_utente++;
        }

        // faccio inserire l'id dell'utente che restituisce il prestito
        cout << "\tInserisci l'id dell'utente: ";
        cin >> id_utente;
        cin.ignore();

        // controllo che l'id inserito corrisponda al cognome cercato
        while(i < MAX_UTENTI){
            if(registro_ute[i].id == id_utente){
                char cognome_registro[MAX_COGNOME];
                gh_strcpy(cognome_registro,registro_ute[i].cognome);
                normalizza_stringa(cognome_registro);
                normalizza_stringa(cognome_cercato);

                if(gh_strcmp(cognome_registro, cognome_cercato) == 0){
                    id_corretto = true;
                    break;
                }else{
                    cout << "\tErrore: non hai inserito un id compatibile\n";
                    break;
                }
            }
            i++;
        }
    }while(!id_corretto);

    i = 0;

    // visualizzo prestiti attivi dell'utente selezionato
    visualizza_header_prestiti();
    while((ind_prestito = cerca_prestito(registro_pre, id_utente, primo_libero, ind_prestito)) != -1){
        visualizza_dati_prestito(registro_pre, ind_prestito);
        ind_prestito++;
    }

    cout << endl;
    cout << "\tInserisci l'id del prestito da chiudere: ";
    cin >> id_prestito;
    cin.ignore();

    // trovo e chiudo il prestito
    i = 0;
    while(registro_pre[i].id != id_prestito){
        i++;
    }
    registro_pre[i].stato = 0;

    // trovo il libro e aggiorno le copie disponibili
    while(registro_lib[j].id != registro_pre[i].id_libro){
        j++;
    }
    registro_lib[j].copie_disponibili++;

    cout << endl;
    cout << "\tInserisci la data di chiusura del prestito: ";
    cin.getline(registro_pre[i].data_restituzione, MAX_DATA);
    cout << endl;
    cout << "\tInserisci le note: ";
    cin.getline(registro_pre[i].note, MAX_NOTE);

    cout << "\tPrestito chiuso";
}

// Funzione cerca_prestito()
// ritorna:
// >0 indice del prestito se trova una corrispondenza
// -1 se non trova corrispondeze
int cerca_prestito(prestito registro_pre[], int id_utente, int primo_libero, int pos_ini = 0){

    while(pos_ini < primo_libero){
        if(registro_pre[pos_ini].id_utente == id_utente && registro_pre[pos_ini].stato == 1){
            return pos_ini;
        }
        pos_ini++;
    }
    return -1;
}

void visualizza_header_prestiti(){
    int larg_id = 7;
    int larg_id_libro = 15;
    int larg_id_utente = 15;
    int larg_data_prestito = 25;
    int larg_data_restituzione = 25;
    int larg_stato = 15;
    int larg_note = 25;

    cout << left;
    cout << setfill(' ');
    cout << endl;
    cout << "\t";
    cout << setw(larg_id) << "ID";
    cout << setw(larg_id_libro) << "ID Libro";
    cout << setw(larg_id_utente) << "ID Utente";
    cout << setw(larg_data_prestito) << "Data prestito";
    cout << setw(larg_data_restituzione) << "Data restituzione";
    cout << setw(larg_stato) << "Stato";
    cout << setw(larg_stato) << "Note";
    cout << endl;
}

// visualizza i dati del prestito indicato dal parametro
void visualizza_dati_prestito(prestito registro_pre[], int indice_prestito){
    int larg_id = 7;
    int larg_id_libro = 15;
    int larg_id_utente = 15;
    int larg_data_prestito = 25;
    int larg_data_restituzione = 25;
    int larg_stato = 15;
    int larg_note = 25;

    cout << left;
    cout << setfill(' ');
    cout << endl;
    cout << "\t";
    cout << setw(larg_id) << registro_pre[indice_prestito].id;
    cout << setw(larg_id_libro) << registro_pre[indice_prestito].id_libro;
    cout << setw(larg_id_utente) << registro_pre[indice_prestito].id_utente;
    cout << setw(larg_data_prestito) << registro_pre[indice_prestito].data_prestito;
    cout << setw(larg_data_restituzione) << registro_pre[indice_prestito].data_restituzione;
    cout << setw(larg_stato);
    if(registro_pre[indice_prestito].stato){
        cout << "attivo\n";
    }else{
        cout << "non attivo\n";
    }
    cout << setw(larg_note) << registro_pre[indice_prestito].note;
}

void visualizza_prestiti(prestito registro_pre[], int primo_libero){
    visualizza_header_prestiti();
    for(int i = 0; i < primo_libero; i++){
        visualizza_dati_prestito(registro_pre, i);
    }
}

// salva il registro fino a dove è stato riempito
// ritorna:
// 0 tutto ok
// -1 errore in apertura file
// -2 errore in scrittura file
int salva_prestiti(prestito registro[]){
    FILE* fp;
    if(fopen_s(&fp, FILE_PRESTITI, "wb") == 0){
        for(int i = 0; i < MAX_PRESTITI; i++){
            if(fwrite(&registro[i], sizeof(prestito), 1, fp) != 1){
                fclose(fp);
                return -2;
            }
        }
    }else{
        return -1;
    }
    fclose(fp);
    return 0;
}

// legge dal file e momorizza nel registro
// ritorna:
// primo_libero se tutto ok
// -1 errore in apertura file
// -2 errore in lettura file
int carica_prestiti(prestito registro[]){
    FILE* fp;
    int i = 0;
    prestito buffer;
    if(fopen_s(&fp, FILE_PRESTITI, "rb") == 0){
        while(fread(&buffer, sizeof(prestito), 1, fp) == 1){
            // contrtollo overflow del vettore
            if(i >= MAX_PRESTITI){
                fclose(fp);
                return -3;
            }
            registro[i] = buffer;
            i++;
        }

        // controllo sulla fine del file per file corrotto
        // se 0 non ha superato EOF
        if(feof(fp) == 0){
            fclose(fp);
            return -2;
        }

        fclose(fp);
        return 0;
    }else{
        return -1;          // il file non esiste - primo avvio
    }
}

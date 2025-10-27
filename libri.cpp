#include "libri.h"
#include <iostream>
#include <iomanip>

// utilizzo spazio dei nomi std con limitazioni
using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::cerr;
using std::setfill;
using std::endl;
using std::left;

// Funzione dati_libri()
// e' il controller principale della sezione libri
// gestisce tutti dati dei libri e il flusso di elaborazione
int dati_libri(libro registro[], int primo_libero){
    char scelta;

    // lavoro con primo libero, ma se c'e' stato un errore imprevisto
    // nel salvataggio automatico ritorno la sua copia e non perdo
    // il valore iniziale.
    int copia_primo_libero = primo_libero;

    // stringa per il sotto-menu
    string stringa_menu = "Nuovo libro;Modifica libro;Elimina libro;Visualizza libri";

    do{
        // sotto-menu libri
        crea_menu("Menu libri", stringa_menu);
        cout << "\tInserisci l'operazione da svolgere: ";
        cin >> scelta;
        cin.ignore();

        // flusso di elaborazione
        switch(scelta){
        case '1':
            // -1 è il valore di ritorno quando si e' raggiunto MAX_LIBRI
            if(primo_libero == -1){
                cout << endl;
                cerr << "\tERRORE: registro pieno, cancellare libri";
                premi_invio();
            }else{
                primo_libero = nuovo_libro(registro, primo_libero);
            }
            break;
        case '2':
            modifica_libro(registro);
            break;
        case '3':
            primo_libero = elimina_libro(registro, primo_libero);
            break;
        case '4':
            visualizza_header_libro();
            for(int i = 0; i < MAX_LIBRI; i++){
                if(registro[i].libero_succ == -2){
                    visualizza_libro(registro, i);
                }
            }
            cout << endl;
            premi_invio();
            break;
        }
    }while(scelta != '9');

    // salvataggio su file
    int err_file = salva_libri(registro);
    if(err_file == 0){
        return primo_libero;	// ritorna la prima posizione libera del registro
    }
    if(err_file == -2){
        cout << endl;
        cerr << "\tERRORE: di scrittura sul file, reinserisci i dati";
        premi_invio();
        return copia_primo_libero;
    }
    if(err_file == -1){
        cout << endl;
        cerr << "\tERRORE: nell'apertura del file, reinserisci i dati";
        premi_invio();
        return copia_primo_libero;
    }
}

// Funzione nuovo_libro()
// aggiunge un nuovo libro al registro dei libri in posizione primo_libero
// richiede tutti i dati tranne l'id che viene messo in automatico
// ritorna:
// >0 l'indice del prossimo posto libero
// -1 se il registro e' pieno
int nuovo_libro(libro registro[], int primo_libero){

    // id automatico
    registro[primo_libero].id = primo_libero + 1;

    // input e memorizzazione dei dati del libro
    cout << endl;
    cout << "\tInserisci titolo libro: ";
    cin.getline(registro[primo_libero].titolo, MAX_TITOLO);

    // forrmatta e controlla la stringa
    valida_input_stringa(registro[primo_libero].titolo, MAX_TITOLO, SET_TITOLO);

    cout << "\tInserisci autore: ";
    cin.getline(registro[primo_libero].autore, MAX_AUTORE);

    // forrmatta e controlla la stringa
    valida_input_stringa(registro[primo_libero].autore, MAX_AUTORE, SET_AUTORE);

    cout << "\tInserisci l'anno di pubblicazione: ";
    cin >> registro[primo_libero].anno_pubblicazione;

    // controllo sull'anno immesso
    valida_anno_pubblicazione(registro[primo_libero].anno_pubblicazione);

    cout << "\tInserisci il numero di copie disponibili: ";
    cin >> registro[primo_libero].copie_disponibili;
    cin.ignore();

    // aggiornamento primo_libero
    // aggiornamento sentinella id a -2
    // aggiornamento sentinella libero_succ a -1
    int copia_primo_libero = primo_libero;
    if(registro[primo_libero].libero_succ == -1){           // posizione di fine posti occupati

        registro[primo_libero].libero_succ = -2;            // occupo il posto

        if(primo_libero + 1 < MAX_LIBRI){                   // controllo se il registro e' pieno
            primo_libero++;                                 // aggiorno primo_libero
            registro[primo_libero].id = -2;                 // aggiorno sentinella di primo_libero
            registro[primo_libero].libero_succ = -1;        // aggiorno sentinella posti occupati
        }else{
            primo_libero = -1;                              // registro pieno
        }
    }else{                                                  // posizione nella lista eliminati
        primo_libero = registro[primo_libero].libero_succ;  // aggiorno primo_libero
        registro[primo_libero].id = -2;                     // aggiorno sentinella di primo_libero
        registro[copia_primo_libero].libero_succ = -2;      // occupo il posto
    }
    cout << endl;
    cout << "\tLibro inserito con successo\n";
    premi_invio();

    return primo_libero;	                                // ritorna il prossimo libero o -1
}

// Funzione modifica_libro()
// ha come parametro il registro dei libri,
// richiama la funzione cerca_libro() che ritorna l'indice
// del libro cercato
// visualizza i dati del libro e chiede di effettuare le modifiche
void modifica_libro(libro registro[]){

    // stringa per sotto-menu
    string stringa_menu = "Titolo;Autore;Anno;Disponibilita'";
    int indice;
    char scelta;
    char titolo[MAX_TITOLO];

    cout << endl;
    cout << "\tInserisci il titolo del libro che vuoi modificare: ";
    cin.getline(titolo, MAX_TITOLO);

    // controlli su lunghezza e caratteri
    valida_sicurezza_stringa(titolo, MAX_TITOLO, SET_TITOLO);

    // ricerca per titolo e ritorna l'indice
    indice = cerca_libro(registro, titolo);

    // controllo sul titolo
    if(indice == -1){
        cout << endl;
        cerr << "\tERRORE: Il libro non e' presente\n";
        premi_invio();
    }else{
        // visualizza dati libro
        visualizza_header_libro();
        visualizza_libro(registro, indice);

        // chiedo conferma
        cout << endl;
        cout << "\tE' questo il libro da modificare (s/n): ";
        cin >> scelta;
        cin.ignore();
        if(scelta == 's' || scelta == 'S'){
            do{
                pulisci_schermo();

                // sotto-menu modifica libri
                crea_menu("Modifica libro", stringa_menu);
                cout << endl;
                cout << "\tCosa vuoi modificare: ";
                cin >> scelta;
                cin.ignore();

                switch(scelta){
                case '1':
                    cout << endl;
                    cout <<  "\tInserisci il nuovo titolo: ";
                    cin.getline(registro[indice].titolo, MAX_TITOLO);
                    cout << endl;

                    // controlli su lunghezza e caratteri
                    valida_sicurezza_stringa(registro[indice].titolo, MAX_TITOLO, SET_TITOLO);

                    cout << "\tModifiche avvenute\n";
                    premi_invio();
                    break;
                case '2':
                    cout << endl;
                    cout << "\tInserisci il nuovo autore: ";
                    cin.getline(registro[indice].autore, MAX_AUTORE);
                    cout << endl;

                    // controlli su lunghezza e caratteri
                    valida_sicurezza_stringa(registro[indice].autore, MAX_AUTORE, SET_AUTORE);
                    cout << endl;
                    cout << "\tModifiche accettate\n";
                    premi_invio();
                    break;
                case '3':
                    cout << endl;
                    cout << "\tInserisci il nuovo anno di pubblicazione: ";
                    cin >> registro[indice].anno_pubblicazione;
                    valida_anno_pubblicazione(registro[indice].anno_pubblicazione);
                    break;
                case '4':
                    cout << endl;
                    cout << "\tInserisci numero di copie: ";
                    cin >> registro[indice].copie_disponibili;
                    break;
                }
            }while(scelta != '9');
        }else{
            cout << endl;
            cout << "\tAVVISO: modifiche non effettuate\n";
            premi_invio();
            return;
        }
    }
}

// Funzione elimina_libro()
// ricerca per titolo e chiede conferma sulla cancellazione
// collega la posizione svuotata alla lista dei liberi
// ritorna:
// >0 primo posto libero nel registro
int elimina_libro(libro registro[], int primo_libero){
    int indice = 0;
    char titolo[MAX_TITOLO];
    char scelta;

    cout << endl;
    cout << "\tInserisci il titolo del libro da eliminare: ";
    cin.getline(titolo, MAX_TITOLO);

    // controlli su lunghezza e caratteri
    valida_sicurezza_stringa(titolo, MAX_TITOLO, SET_TITOLO);

    indice = cerca_libro(registro, titolo);

    if (indice == -1){
        cerr << "\tERRORE: il libro non e' presente\n";
        premi_invio();
        return primo_libero;
    }else if(registro[indice].libero_succ != -2){
        cerr << "\tERRORE: Il libro selezionato è già stato cancellato.\n";
        premi_invio();
        return primo_libero;
    }else{
        visualizza_libro(registro, indice);

        cout << "\n\tConferma cancellazione (s/n): ";
        cin >> scelta;
        cin.ignore();

        if(scelta == 's' || scelta == 'S'){

            // aggiornamento dati
            registro[indice].titolo[0] = '\0';
            registro[indice].autore[0] = '\0';
            registro[indice].anno_pubblicazione = 0;
            registro[indice].copie_disponibili = 0;
            registro[indice].libero_succ = primo_libero;

            // aggiornamento sentinelle
            registro[primo_libero].id = -1;     // aggiornamento sentinella vecchio primo_libero a -1
            primo_libero = indice;              // aggiornamento primo_libero
            registro[primo_libero].id = -2;     // aggiornamento sentinella id di primo_libero a -2

            cout << "\n\tLibro cancellato\n";
            premi_invio();
        }else{
            return primo_libero;
        }
    }
    return primo_libero;
}

// Funzione cerca_libro()
// compie una ricerca sequenziale su tutto il vettore e un confronto
// sul titolo cercato.
// ritorna l'indice del libro quindi >= 0
// ritorna -1 se non trovato.
int cerca_libro(libro registro[], const char titolo[]){

    int i = 0;                                      // indice del registro
    char titolo_registro_norm[MAX_TITOLO];          // stringa per copia normalizzata
    char titolo_cercato_norm[MAX_TITOLO];           // stringa per copia normalizzata
    gh_strcpy(titolo_cercato_norm, titolo);         // copio la stringa cercata
    normalizza_stringa(titolo_cercato_norm);        // normalizzo la stringa cercata

    while(i < MAX_LIBRI){
        if(registro[i].libero_succ == -2){
            gh_strcpy(titolo_registro_norm, registro[i].titolo);
            normalizza_stringa(titolo_registro_norm);
            if(gh_strcmp(titolo_registro_norm, titolo_cercato_norm) == 0){
                return i;
            }
        }
        i++;
    }
    return -1;
}

// Funzione visualizza_libro()
// visualizza i dati di un singolo libro in tabella
void visualizza_libro(libro registro[], int indice){

    int larg_id = 5;
    int larg_titolo = 40;
    int larg_autore = 30;
    int larg_anno = 11;
    int larg_copie = 15;

    // variabili temporanee
    char titolo_temp[MAX_TITOLO];
    char autore_temp[MAX_AUTORE];

    gh_strcpy(titolo_temp, registro[indice].titolo);
    gh_strcpy(autore_temp, registro[indice].autore);

    gh_capitalize_first(titolo_temp);
    gh_capitalize_word(autore_temp);

    cout << endl;
    cout << left;
    cout << setfill(' ');
    cout << "\t";
    cout << setw(larg_id) << registro[indice].id;
    cout << setw(larg_titolo) << titolo_temp;
    cout << setw(larg_autore) << autore_temp;
    cout << setw(larg_anno) << registro[indice].anno_pubblicazione;
    cout << setw(larg_copie) << registro[indice].copie_disponibili;
    cout << endl;
}

// Funzione visualizza_header_libro()
// visualizza l'intestazione della tabella libri
void visualizza_header_libro(){

    int larg_id = 5;
    int larg_titolo = 40;
    int larg_autore = 30;
    int larg_anno = 11;
    int larg_copie = 15;

    cout << endl;
    cout << left;
    cout << setfill(' ');
    cout << "\t";
    cout << setw(larg_id) << "ID";
    cout << setw(larg_titolo) << "Titolo";
    cout << setw(larg_autore) << "Autore";
    cout << setw(larg_anno) << "Anno";
    cout << setw(larg_copie) << "Numero copie";
    cout << endl;

}

// Funzione salva_libri()
// salva su file tutto il registro libri, ritorna:
// 0 tutto ok
// -1 errore in apertura file
// -2 errore in scittura file
int salva_libri(libro registro[]){
    FILE* fl;
    if(fopen_s(&fl, FILE_LIBRI, "wb") == 0){
        for(int i = 0; i < MAX_LIBRI; i++){
            if(fwrite(&registro[i], sizeof(libro), 1, fl) != 1){
                fclose(fl);
                return -2;
            }
        }
    }else{
        return -1;
    }
    fclose(fl);
    return 0;
}

// Funzione carica_libri()
// carica il file nel registro libri, ritorna:
// 0 tutto ok
// -1 errore in apertura file
// -2 errore in lettura file
// -3 se è andato in overflow
int carica_libri(libro registro[]){

    FILE* fl;
    libro buffer;
    int i = 0;

    if(fopen_s(&fl, FILE_LIBRI, "rb") == 0){
        while(fread(&buffer, sizeof(libro), 1, fl) == 1){
            // contrtollo overflow del vettore
            if(i >= MAX_LIBRI){
                fclose(fl);
                return -3;
            }
            registro[i] = buffer;
            i++;
        }

        // controllo sulla fine del file per file corrotto
        // se 0 non ha superato EOF
        if(feof(fl) == 0){
            fclose(fl);
            return -2;
        }

        fclose(fl);
        return 0;
    }else{
        return -1;          // il file non esiste - primo avvio
    }
}

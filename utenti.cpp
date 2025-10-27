#include "utenti.h"
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

// Funzione dati_utenti()
// e' il controller principale della sezione utenti
// gestisce tutti dati degli utenti
int dati_utenti(utente registro[], int primo_libero){
    char scelta;

    // lavoro con primo libero, ma se c'e' stato un errore imprevisto
    // nel salvataggio automatico ritorno la sua copia e non perdo
    // il valore iniziale.
    int copia_primo_libero = primo_libero;

    // stringa per il sotto-menu
    string stringa_menu = "Nuovo utente;Modifica utente;Elimina utente;Visualizza utenti";

    do{
        // sotto-menu utenti
        crea_menu("Menu utenti", stringa_menu);
        cout << "\tInserisci l'operazione da svolgere: ";
        cin >> scelta;
        cin.ignore();

        // flusso di elaborazione
        switch(scelta){
        case '1':
            // -1 è il valore di ritorno quando si e' raggiunto MAX_UTENTI
            if(primo_libero == -1){
                cerr << "\tERRORE: registro pieno, cancellare utenti";
                cout << "\n\t";
                system("PAUSE");
            }else{
                primo_libero = nuovo_utente(registro, primo_libero);
            }
            break;
        case '2':
            modifica_utente(registro);
            break;
        case '3':
            primo_libero = elimina_utente(registro, primo_libero);
            break;
        case '4':
            visualizza_header_utente();
            for(int i = 0; i < MAX_UTENTI; i++){
                if(registro[i].libero_succ == -2){
                    visualizza_utente(registro, i);
                }
            }
            cout << endl;
            premi_invio();
            break;
        }
    }while(scelta != '9');

    // salvataggio su file
    int err_file = salva_utenti(registro);
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

// Funzione nuovo_utente()
// aggiunge un nuovo utente al registro degli alunni.
// aichiede tutti i dati tranne l'id che viene messo in automatico.
// ritorna:
// >0 l'indice del prossimo posto libero
// -1 se il registro e' pieno
int nuovo_utente(utente registro[], int primo_libero){

    // id automatico
    registro[primo_libero].id = primo_libero + 1;

    // input e memorizzazione dei dati del libro
    cout << endl;
    cout << "\tInserisci il nome: ";
    cin.getline(registro[primo_libero].nome, MAX_NOME);

    // forrmatta e controlla la stringa
    valida_input_stringa(registro[primo_libero].nome, MAX_NOME, SET_UTENTE);

    cout << "\tInserisci cognome: ";
    cin.getline(registro[primo_libero].cognome, MAX_COGNOME);

    // forrmatta e controlla la stringa
    valida_input_stringa(registro[primo_libero].cognome, MAX_COGNOME, SET_UTENTE);

    cout << "\tInserisci classe: ";
    cin >> registro[primo_libero].classe;

    cout << "\tInserisci sezione: ";
    cin >> registro[primo_libero].sezione;
    cin.ignore();

    // aggiornamento primo_libero
    // aggiornamento sentinella id a -2
    // aggiornamento sentinella libero_succ a -1
    int copia_primo_libero = primo_libero;
    if(registro[primo_libero].libero_succ == -1){               // posizione di fine posti occupati

        registro[primo_libero].libero_succ = -2;                // occupo il posto

        if(primo_libero + 1 < MAX_UTENTI){                      // controllo se il registro e' pieno
            primo_libero++;                                     // aggiorno primo_libero
            registro[primo_libero].id = -2;                     // aggiorno sentinella di primo_libero
            registro[primo_libero].libero_succ = -1;            // aggiorno sentinella posti occupati
        }else{
            primo_libero = -1;                                  // registro pieno
        }
    }else{                                                      // posizione nella lista eliminati
        primo_libero = registro[primo_libero].libero_succ;      // aggiorno primo_libero
        registro[primo_libero].id = -2;                         // aggiorno sentinella di primo_libero
        registro[copia_primo_libero].libero_succ = -2;          // occupo il posto
    }

    cout << endl;
    cout << "\tUtente inserito con successo\n";
    premi_invio();

    return primo_libero;	                                    // ritorna il prossimo libero o -1
}

// Funzione modifica_utente()
// ha come parametro il registro
// richiama la funzione cerca_utente() che ritorna l'indice
// del'utente cercato.
// visualizza i dati dell'utente e chiede di effettuare le modifiche
void modifica_utente(utente registro[]){

    string stringa_menu = "Nome;Cognome;Classe;Sezione;";
    char scelta;                    // scelta del menu utente
    char cognome[MAX_COGNOME];		// utente da cercare
    int id;			                // id dell'utente trovato
    int indice = 0;		            // indice dell'utente trovato
    bool trovati = false;   	    // contatore degli alunni omonimi

    cout << endl;
    cout << "\tInserisci il cognome dell'utente: ";
    cin.getline(cognome, MAX_COGNOME);

    // controlli su lunghezza e caratteri
    valida_sicurezza_stringa(cognome, MAX_COGNOME, SET_UTENTE);

    visualizza_header_utente();

    // cerca_utente() ritorna indice
    while((indice = cerca_utente(registro,cognome, indice)) != -1){
        visualizza_utente(registro, indice);
        trovati = true;
        indice++;
    }

    // controllo su trovati e casi di omonimia
    if(!trovati){
        cout << endl;
        cerr << "\tERRORE: cognome inesistente\n";
        premi_invio();
        return;
    }else{
        // ricerca su id corretto
        cout << endl;
        cout << "\tInserisci l'id dell'utente da modificare: ";
        cin >> id;
        cin.ignore();

        indice = 0;
        while(registro[indice].libero_succ != -1 && registro[indice].id != id){
            indice++;
        }
    }

    do{
        pulisci_schermo();

        // sotto-menu modifica utente
        crea_menu("Modifica utente", stringa_menu);
        visualizza_header_utente();
        visualizza_utente(registro, indice);
        cout << endl;
        cout << "\tCosa vuoi modificare: ";
        cin >> scelta;
        cin.ignore();

        switch(scelta){
        case '1':
            cout << endl;
            cout << "\tInserisci il nuovo nome: ";
            cin.getline(registro[indice].nome, MAX_NOME);

            // controlli su lunghezza e caratteri
            valida_sicurezza_stringa(registro[indice].nome, MAX_NOME, SET_UTENTE);

            cout << endl;
            cout << "\tModifiche avvenute\n";
            premi_invio();
            break;
        case '2':
            cout << "\tInserisci il nuovo cognome: ";
            cin.getline(registro[indice].cognome, MAX_COGNOME);

            // controlli su lunghezza e caratteri
            valida_sicurezza_stringa(registro[indice].cognome, MAX_COGNOME, SET_UTENTE);

            cout << "\tModifiche avvenute\n";
            premi_invio();
            break;
        case '3':
            cout << "\tInserisci la nuova classe: ";
            cin >> registro[indice].classe;
            cin.ignore();
            cout << "\tModifiche avvenute\n";
            premi_invio();
            break;
        case '4':
            cout << "\tInserisci la nuova sezione: ";
            cin >> registro[indice].sezione;
            cin.ignore();
            cout << "\tModifiche avvenute\n";
            premi_invio();
            break;
        }
    }while(scelta != '9');
}

// Funzione elimina_utente()
// ricerca per cognome, e chiede conferma sulla cancellazione
// ritorna:
// >0 prossimo posto libero nel registro
int elimina_utente(utente registro[], int primo_libero){
    int id;
    char cognome[MAX_COGNOME];
    char scelta;
    bool trovati = false;
    int indice = 0;

    cout << endl;
    cout << "\tInserisci il cognome dell'utente da eliminare: ";
    cin.getline(cognome, MAX_COGNOME);

    valida_sicurezza_stringa(cognome, MAX_COGNOME, SET_UTENTE);

    visualizza_header_utente();
    while((indice = cerca_utente(registro, cognome, indice)) != -1){
        visualizza_utente(registro, indice);
        indice++;
        trovati = true;
    }

    if(!trovati){
        cout << endl;
        cerr << "\tERRORE: non sono stati trovati utenti con quel cognome";
        premi_invio();
        return primo_libero;
    }
    cout << endl;
    cout << "\tInserisci l'id da eliminare: ";
    cin >> id;

    indice = 0;
    while(registro[indice].id != id){
        indice++;
    }
    cout << endl;
    cout << "\tConferma cancellazione (s/n): ";
    cin >> scelta;
    cin.ignore();

    if(scelta == 's' || scelta == 'S'){

        // aggiornamento dati
        registro[indice].nome[0] = '\0';
        registro[indice].cognome[0] = '\0';
        registro[indice].classe = 0;
        registro[indice].sezione = ' ';
        registro[indice].libero_succ = primo_libero;

        // aggiornamento sentinelle
        registro[primo_libero].id = -1;     // aggiornamento sentinella vecchio primo_libero a -1
        primo_libero = indice;              // aggiornamento primo_libero
        registro[primo_libero].id = -2;     // aggiornamento sentinella id di primo_libero a -2

        cout << endl;
        cout << "\tUtente cancellato\n";
        premi_invio();
    }
    return primo_libero;
}

// Funzione cerca_utente()
// Ha come parametri il registro degli utenti,
// il cognome dell'utente da cercare.
// compie una ricerca sequenziale con controllo sul campo del cognome.
// ritorna:
// >0 l'indice dell'utente
// -1 se non trovato
int cerca_utente(utente registro[], char cognome[], int pos_ini = 0){

    int i = 0;
    char cognome_registro_norm[MAX_COGNOME];
    char cognome_cercato_norm[MAX_COGNOME];     // nel caso sia stato modificato
    gh_strcpy(cognome_cercato_norm, cognome);
    normalizza_stringa(cognome_cercato_norm);

    while(pos_ini < MAX_UTENTI){
        if(registro[pos_ini].libero_succ == -2){
            gh_strcpy(cognome_registro_norm, registro[pos_ini].cognome);
            normalizza_stringa(cognome_registro_norm);
            if (gh_strcmp(cognome_registro_norm,cognome_cercato_norm) == 0){
                return pos_ini;
            }

        }
        pos_ini++;
    }
    return -1;
}

// Funzione visualizza_utente()
// visualizza i dati di un singolo utente in tabella
void visualizza_utente(utente registro[], int indice){

    int larg_id = 5;
    int larg_nome = 20;
    int larg_cognome = 20;
    int larg_classe = 10;
    int larg_sezione = 10;

    // variebili temporanee
    char nome_temp[MAX_NOME];
    char cognome_temp[MAX_COGNOME];

    gh_strcpy(nome_temp, registro[indice].nome);
    gh_strcpy(cognome_temp, registro[indice].cognome);

    gh_capitalize_first(nome_temp);
    gh_capitalize_first(cognome_temp);

    cout << left;
    cout << setfill(' ');
    cout << endl;
    cout << "\t";
    cout << setw(larg_id) << registro[indice].id;
    cout << setw(larg_nome) << nome_temp;
    cout << setw(larg_cognome) << cognome_temp;
    cout << setw(larg_classe) << registro[indice].classe;
    cout << setw(larg_sezione) << registro[indice].sezione;
    cout << endl;

}

// Funzione visualizza_header_utente()
// visualizza la testata della tabella utenti
void visualizza_header_utente(){

    int larg_id = 5;
    int larg_nome = 20;
    int larg_cognome = 20;
    int larg_classe = 10;
    int larg_sezione = 10;

    cout << left;
    cout << setfill(' ');
    cout << endl;
    cout << "\t";
    cout << setw(larg_id) << "ID";
    cout << setw(larg_nome) << "Nome";
    cout << setw(larg_cognome) << "Cognome";
    cout << setw(larg_classe) << "Classe";
    cout << setw(larg_sezione) << "Sezione";
    cout << endl;

}

// Funzione salva_utenti()
// salva su file tutto il registro utenti, ritorna:
// 0 tutto ok
// -1 errore in apertura file
// -2 errore in scrittura file
int salva_utenti(utente registro[]){
    FILE* fu;
    if(fopen_s(&fu, FILE_UTENTI, "wb") == 0){
        for(int i = 0; i < MAX_UTENTI; i++){
            if(fwrite(&registro[i], sizeof(utente), 1, fu) != 1){
                fclose(fu);
                return -2;
            }
        }
    }else{
        return -1;
    }
    fclose(fu);
    return 0;
}

// carica il file nel registro utenti, ritorna:
// 0 tutto ok
// -1 errore in apertura file
// -2 errore in lettura file
// -3 se è andato in overflow
int carica_utenti(utente registro[]){

    FILE* fu;
    utente buffer;
    int i = 0;

    if(fopen_s(&fu, FILE_UTENTI, "rb") == 0){
        while(fread(&buffer, sizeof(utente), 1, fu) == 1){
            // contrtollo overflow del vettore
            if(i >= MAX_UTENTI){
                fclose(fu);
                return -3;
            }
            registro[i] = buffer;
            i++;
        }

        // controllo sulla fine del file per file corrotto
        // se 0 non ha superato EOF
        if(feof(fu) == 0){
            fclose(fu);
            return -2;
        }

        fclose(fu);
        return 0;
    }else{
        return -1;          // il file non esiste - primo avvio
    }
}

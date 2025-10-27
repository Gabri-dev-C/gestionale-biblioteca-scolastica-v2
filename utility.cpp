#include "utility.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::cerr;
using std::setfill;
using std::endl;
using std::left;
using std::right;

// Effettua lo split e visualizza il menu.
void crea_menu(std::string titolo_menu, std::string voci_menu){

    unsigned i = 0;			    // indice per scorrere voci_menu
    int conta_voci = 0;		    // contatore delle voci del menu
    std::string voce = "";		// voce del menu

    if (voci_menu.empty() || voci_menu.back() != ';') {
        voci_menu += ';';		// assegno ; in ultima posizione
    }

    // larghezza delle celle del menu
    int larghezza_voce = 80;
    int larghezza_scelta = 3;
    const int voce_uscita = 9;

    pulisci_schermo();

    cout << "\t\t" << titolo_menu << "\n" << endl;	// visualizza il titolo
    cout << setfill('.');
    while(i < voci_menu.size()){	    // eseguo lo split della stringa
        if(voci_menu.at(i) != ';'){	    // controllo il separatore
            voce += voci_menu.at(i);	// costruzione della voce del menu
            i++;				        // prossimo carattere
        }else{
            i++;
            conta_voci++;		        // conteggio delle voci del menu

            // visualizza la voce del menu con il numero di scelta
            cout << left << "\t" << setw(larghezza_voce) << voce << setw(larghezza_scelta) << right << conta_voci << "\n";
            voce = "";
        }
    }
    cout << left << "\t" << setw(larghezza_voce) << "Esci" << setw(larghezza_scelta)
        << right << voce_uscita << "\n\n";
}

// Funzione valida_input_stringa()
// wrapper per la gestione degli errori dell'input stringa
// richiama pulisci_stringa()
void valida_input_stringa(char buffer[], int lunghezza, const char set_caratteri[]){
    int err_input;
    do{
        err_input = pulisci_stringa(buffer, lunghezza, set_caratteri);

        if(err_input == -1){
            cerr << "\tERRORE: inserimento troppo lungo, massimo " << lunghezza << " caratteri\n";
            cout << endl;
            cin.clear();                        // resetta lo stato di errore dello stram
            cin.ignore(10000, '\n');            // svuota il buffer dello stream
            buffer[0] = '\0';                   // resetto la stringa
        }

        if(err_input == -2){
            cerr << "\tERRORE: il campo e' obbligatorio\n";
        }

        if(err_input == -3){
            cerr << "\tERRORE: hai usato caratteri non ammessi\n";
            buffer[0] = '\0';                   // resetto la stringa
        }

        if(err_input != 0){
            cout << "\tReinserisci i dati: ";
            cin.getline(buffer, lunghezza);
        }
    }while(err_input != 0);
}

// Funzione pulisci_stringa()
// pulitura dell'input per le stringhe da memorizzare
// nei registri fatta in 6 passaggi
// modifica in-place
int pulisci_stringa(char buffer[], int lunghezza, const char set_caratteri[]){

    // 1. Sicurezza: controllo lunghezza massima della stringa
    if(gh_length(buffer) >= lunghezza - 1){
        return -1;
    }

    // 2. Normalizza: trim spazi iniziali e finali
    gh_trim(buffer);

    // 3. Normalizza: rimuove doppi spazi
    gh_remove_double_space(buffer);

    // 4. Sicurezza: controllo sull'input vuoto dopo la pulizia
    if(gh_length(buffer) == 0){
        return -2;
    }

    // 5. Sicurezza: controllo sui caratteri
    bool carattere_valido = true;
    for(int i = 0; buffer[i] != '\0'; i++){
        if(gh_strchr(set_caratteri, buffer[i]) == -1){
            return -3;
        }
    }

    // 6. Normalizza: trasformo la stringa in minuscolo
    gh_toLower(buffer);

    return 0;
}

void valida_sicurezza_stringa(char s[], const int lunghezza, const char set_caratteri[]){
    int err_input;
    do{
        err_input = controllo_sicurezza_stringa(s, lunghezza, set_caratteri);

        if(err_input == -1){
            cerr << "\tERRORE: il campo e' obbligatorio\n";
            premi_invio();
        }

        if(err_input == -2){
            cerr << "\tERRORE: inserimento troppo lungo, massimo " << lunghezza << " caratteri\n";
            premi_invio();
        }

        if(err_input == -3){
            cerr << "\tERRORE: hai usato caratteri non ammessi\n";
            premi_invio();
        }

        if(err_input != 0){
            cout << endl;
            cout << "\tReinserisci i dati: ";
            cin.getline(s, lunghezza);
        }

    }while(err_input != 0);
}

// controllo_sicurezza_stringhe()
// effettua semplici controlli per le stringhe senza pulirle
// usata nelle funzioni modifica_
// ritorna:
// -1 se stringa vuota
// -2 se stringa troppo lunga
// -3 se caratteri non ammessi
// 0 se controlli superati
int controllo_sicurezza_stringa(const char buffer[], const int lunghezza, const char set_caratteri[]){

    // 1. Sicurezza: controllo sulla stringa vuota
    if(gh_length(buffer) == 0){
        return -1;
    }

    // 4. Sicurezza: controllo sulla lunghezza massima
    if(gh_length(buffer) > lunghezza - 1){
       return -2;
    }

    // 5. Sicurezza: controllo sui caratteri
    for(int i = 0; buffer[i] != '\0'; i++){
        if(gh_strchr(set_caratteri, buffer[i]) == -1){
            return -3;
        }
    }

    return 0;
}

// Funzione normalizza_stringa()
// la stringa viene pulita senza effettuare i controlli
// usata prima dei confronti tra stringhe
// modifica in-place
void normalizza_stringa(char s[]){

    // 2. Normalizza: trim spazi iniziali e finali
    gh_trim(s);

    // 3. Normalizza: rimuove doppi spazi
    gh_remove_double_space(s);

    // 6. Normalizza: trasformo la stringa in minuscolo
    gh_toLower(s);
}

// Funzione valida_anno_pubblicazione()
// wrapper per la gestione dell'input dell'anno
// di publicazione
// richiama convalida_anno()
// modifica in_place
void valida_anno_pubblicazione(int &anno){
    bool valido;

    do{
        valido = convalida_anno(anno);

        if(valido){
            return;
        }else{
            cout << "\tERRORE: l'anno inserito non e' corretto\n";
            cout << endl;
            cout << "\tReinserisci i dati: ";
            cin >> anno;
            cin.ignore();
        }

    }while(!valido);
}

// Funzione convalida_anno()
// controlla se l'anno di publicazione immesso e' coerente
// ritorna:
// true se l'anno e' coerente
// false se l'anno non e' coerente
bool convalida_anno(const int anno){
    const int ANNO_CORRENTE = 2025;
    const int ANNO_PRIMO_LIBRO = 1455;  // Bibbia di Gutenberg

    if(anno < ANNO_PRIMO_LIBRO || anno > ANNO_CORRENTE){
        return false;
    }
    return true;
}

// Funzione pulisci_schermo()
// cancella le visualizzazioni precedenti
// portabile su win e linux.
void pulisci_schermo(){
    if(system("CLS") != 0){
        system("clear");
    }
}

// Funzione premi_invio()
// pausa dopo l'output fino a che non si preme invio,
// portabile su win e linux.
void premi_invio(){
    cout << endl;
    cout << "\tPremi invio per continuare";
    cin.get();
}

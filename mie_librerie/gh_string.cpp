#include "gh_string.h"

// Funzione gh_length()
// ritorna > 0 la lunghezza della stringa senza terminatore
int gh_length(const char s[]){
    int cont = 0;
    while (s[cont] != '\0'){
        cont++;
    }
    return cont;
}

// Funzione gh_strcmp()
// ritorna 0 se uguali.
// ritorna < 0 se prima stringa è più corta.
// ritorna > 0 se prima stringa è pià lunga.
int gh_strcmp(const char s1[], const char s2[]) {
    int i = 0;
    while (s1[i] != '\0') {
        if (s1[i] == s2[i]){    // controllo carattere
            i++;
        }else{
            if(s1[i] < s2[i]) return -1;
            else return 1;
        }
    }

    if (s2[i] != '\0') return -1;    //s1 più corta di s2
    else return 0;  // sono uguali
}

// Funzione gh_strcpy()
// copia la stringa sorgente in quella di destinazione,
// assicurarsi che dest abbia spazio sufficente.
void gh_strcpy(char dest[], const char src[]){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

// Funzione gh_strcat()
// concatena s2 alla fine di s1,
// s1 deve avere spazio sufficiente.
void gh_strcat(char s1[], const char s2[]){
    int i = 0;      // indice di s1
    int j = 0;      // indice di s2

    // Trova la fine di s1
    while(s1[i] != '\0')
        i++;

    // copia tutti i caratteri di s2 in s1
    // partendo dalla fine di s1
    while(s2[j] != '\0'){
        s1[i] = s2[j];
        i++;
        j++;
    }
    // Aggiunge il terminatore di stringa
    s1[i] = '\0';
}

// Funzione gh_strrev()
// inverte la stringa s, due indici i e j
// scambia i caratteri fino a quando non si incrociano.
void gh_strrev(char s[]){
    int i = 0;
    int j = gh_length(s) - 1;
    char temp;

    // scambio i caratteri finché gli indici non si incontrano.
    while(i < j){

        // swap
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        // aggiorno gli indici.
        i++;
        j--;
    }
}

// Funzione gh_strchr()
// ricerca il carattere c nella stringa s.
// ritorna >= 0: posizione del carattere.
// ritorna -1: se non trovato.
int gh_strchr(const char s[], const char c){
    int pos = 0;

    // scansiono tutta la stringa
    while(s[pos] != '\0'){
        // Se viene trovato ritorna la posizione
        if(s[pos] == c) return pos;
        pos++;
    }
    return -1;  // carattere non trovato
}

// Funzione gh_toUpper()
// converte tutti i caratteri di s che hanno
// un valore nel range dei minuscoli della
// tabella ascii in maiuscolo ('a'=97 - 'z'=122)('A'=65 - 'Z'=90)
// modifica s in-place (modifica l'originale nel chiamante).
void gh_toUpper(char s[]){
    int i = 0;
    while(s[i] != '\0'){
        if((s[i] >= 'a') && (s[i] <= 'z')){
            s[i] = s[i] - ('a' - 'A');      // più portabile
        }
        i++;
    }
}

// Funzione gh_toLower()
// converte tutti i caratteri di s che hanno
// un valore nel range dei maiuscoli della
// tabella ascii in minuscolo ('A'=65 - 'Z'=90) ('a'=97 - 'z'=122)
// modifica s in-place (modifica l'originale nel chiamante).
void gh_toLower(char s[]){
    int i = 0;

    while(s[i] != '\0'){
        if((s[i] >= 'A') && (s[i] <= 'Z')){
            s[i] = s[i] + ('a' - 'A');      // più portabile
        }
        i++;
    }
}


// Funzione gh_trim()
// rimuove tutti gli spazi da inizio e fine stringa s.
// modifica in-place.
void gh_trim(char s[]){

    int i = 0;
    int j = 0;

    if(s[i] == '\0'){       //ERRORE: stringa vuota
        return;
    }

    // posiziono i sul primo carattere non spazio
    while(s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\r'){
        i++;
    }

    if(s[i] == '\0'){       //ERRORE: la stringa e' composta solo da spazi";
        s[0] = '\0';
        return;
    }

    while(s[i] != '\0'){    // tolgo gli spazi a inizio riga.
        s[j] = s[i];
        i++;
        j++;
    }

    i--;                    // posiziono i prima del terminatore

    // posiziono i sul primo carattere non spazio
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\r'){
        i--;
    }

    s[i+1] = '\0';              // tolgo gli spazi a fine riga.
}

// Funzione gh_remove_double_space()
// scandisce la stringa ed elimina i doppi spazi
// modifica in-place
void gh_remove_double_space(char stringa[]){
    int i = 0;
    int j = 0;
    int lunghezza = gh_length(stringa);

    // controllo stringa vuota
    if (stringa[i] == 0) return;

    while(i < lunghezza - 1){
        if(stringa[i] == ' ' && stringa[i+1] == ' '){
            j = i;
            while(stringa[j] != '\0'){
                stringa[j] = stringa[j+1];
                j++;
            }
            lunghezza--;
        }else{
            i++;
        }
    }
}

// Funzione gh_capitalize_first()
// trasforma il primo carattere della stringa
// in maiuscolo se è minuscolo, sottraendo 32 al carattere
// modifica in-place
void gh_capitalize_first(char s[]){
    if(s[0] == '0') return;     // stringa vuota

    if(s[0] >= 'a' && s[0] <= 'z'){
        s[0] = s[0] - ('a' - 'A');
    }
}

// Funzione gh_capitalize_word()
// trasforma il primo carattere di ogni
// parola della stringa in maiuscolo se è minuscolo,
// sottraendo 32 al carattere
// modifica in-place
void gh_capitalize_word(char s[]){

    gh_capitalize_first(s);     // converto il primo carattere

    // trovo le parole e converto il primo carattere di ogni parola
    for(int i = 0; i < gh_length(s); i++){
        if(s[i] == ' ' && s[i+1] >= 'a' && s[i+1] <= 'z'){
            s[i+1] = s[i+1] - ('a' - 'A');
        }
    }
}

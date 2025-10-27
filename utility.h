#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <string>
#include "gh_string.h"

// Effettua lo split e visualizza il menu con titolo e voci.
void crea_menu(std::string titolo_menu, std::string voci_menu);

// validazione dell'input utente
void valida_input_stringa(char buffer[], int lunghezza, const char set_caratteri[]);
int pulisci_stringa(char buffer[], int lunghezza, const char set_caratteri[]);
void valida_sicurezza_stringa(char s[], const int lunghezza, const char set_caratteri[]);
int controllo_sicurezza_stringa(const char buffer[], int lunghezza, const char set_caratteri[]);
void normalizza_stringa(char s[]);
void valida_anno_pubblicazione(int &anno);
bool convalida_anno(const int anno);

// utilita' per l'interfaccia
void pulisci_schermo();
void premi_invio();

#endif // UTILITY_H_INCLUDED

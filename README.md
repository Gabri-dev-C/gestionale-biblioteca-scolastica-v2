[README.md](https://github.com/user-attachments/files/23161445/README.md)
# Gestionale biblioteca scolastica v.2.0

Programma per la gestione della biblioteca scolastica in C++ con interfaccia testuale.

## Caratteristiche principali

- Gestione Utenti: anagrafica studenti e gestione degli omonimi.
- Gestione Libri: CRUD completo con ricerca intelligente.
- Gestione Prestiti: tracciamento prestiti e restituzioni.
- Ricerca Fuzzy: trova libri e utenti indipendentemente da maiuscole o minuscole.
- Interfaccia intuitiva: Menu testuali gerarchici e tabelle formattate.

## Architettura e tecnologie

- Linguaggio: C++
- Architettura: modulare con separazione MVC.
- Strutture dati: struct per ogni entità di dati.
- Memorizzazione: array statici con lista libera per ottimizzazione della memoria.
- Gestione stringhe: libreria personalizzata 'gh_string'.
- Input/Output: validazione multilivello e gestione sicura del buffer.
- Persistenza: file di binari per il salvataggio dei dati.

## Struttura del progetto

GestionaleBiblioteca/
├── main.cpp                 
├── config.h                
├── utility.[h/cpp]         # Funzioni di supporto e validazione
├── libri.[h/cpp]           # Modulo gestione libri
├── utenti.[h/cpp]          # Modulo gestione utenti  
├── prestiti.[h/cpp]        # Modulo gestione prestiti
└── mie_librerie/
    └── gh_string.[h/cpp]   # Libreria stringhe personalizzata

## Installazione e Compilazione
1. **Requisiti**: Compilatore C++ (CodeBlocks, GCC, Visual Studio)
2. **Compilazione**:
   - Apri il progetto in CodeBlocks.
   - Build → Compila.
3. **Esecuzione**: Run nell'IDE o eseguibile generato

## Utilizzo

1. Avvia il Programma.
2. Naviga i menu utilizzando i numeri.
3. Inserisci libri e utenti seguendo i prompt.
4. Gestisci i prestiti collegando libri e utenti.
5. I dati si salvano automaticamente all'uscita dei menu.

## Funzionalità dettagliate

1. Modulo Libri:
	- Inserimento nuovo libro con validazione.
	- Modifica campi esistenti.
	- Eliminazione con lista posti liberi.
	- Ricerca per titolo.
	- Visualizzazione tabellare formattata.
	
2. Modulo Utenti:
	- Registrazione studenti con dati anagrafici.
	- Gestione omonimi con ricerca incrementale.
	- Modifica dati studente.
	- Eliminazione con lista posti liberi.

3. Modulo prestiti:
	- Creazione prestito libro - utente con aggiornamento numero di copie.
	- Tracciamento stato e date del prestito.
	- Restituzione libro con aggiornamento stato del prestito, aggiornamento numero di copie.
	- Visualizzazione prestiti attivi.

4. Sistema di ricerca:
	- Normalizzazione stringhe, trim, minuscolo, rimozione spazi multipli.
	- Codici errori strutturati.
	- Recovery da stati inconsistenti.
	- Messaggi utente chiari e specifici.

## Versioni

- **[v2.0]https://github.com/Gabri-dev-C/gestionale-biblioteca-scolastica-v2)** - Versione corrente (migliorata)
- **[v1.0]https://github.com/Gabri-dev-C/gestionale-biblioteca-scolastica** - Versione precedente

## Autore e licenza

Gabriele Henriet
Licenza: MIT
Sviluppato come progetto didattico per apprendere C++ e architettura software.

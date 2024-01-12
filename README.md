# Progetto finale - Monopoly

Progetto di gruppo finale per Laboratorio di Programmazione 23-34
Implementazione di una versione semplificata del famoso gioco da tavolo Hasbro Monopoly®

## **AUTORI**
 
 - Mosele Leonardo
 - Pasetto Niccolò
 - Saladino Davide

---

## **VERSIONE 1.0**

[Repository GitHub del progetto](https://github.com/paznico/Monopoly "GitHub repo")

---

## **NOTE IN FASE DI COMPILAZIONE**

Nella scrittura del file _CMakeLists.txt_ abbiamo risconrato dei problemi con la versione di _CMake_ e _C++_
Per rendere compilabile il progetto abbimo dovuto impostare:

 - La versione minima richiesta di C++ a 14 (per utilizzare gli _shared ptr_)
 - La versione minima richiesta da CMake a 2.8, un errore di warning compare lo stesso per ricordare che in futuro questa versione non sarà più valida

Nelle nostre macchine virtuali con questi cambiamenti il progetto compilava, speriamo che in quelle della Taliercio non creino problemi

---

## **COMPILAZIONE**

Per la compilazione dei diversi file che compongono il progetto viene usato _CMake_ (v3.28.0), che genere il file specifico _make_.
Per compilarlo eseguire i seguenti passaggi nella cartella base del progetto nel terminale:

 - ``` $ mkdir build ```
 - ``` $ cd build ```
 - ``` $ cmake .. ```
 - ``` $ make ```

A questo punto i l'eseguibile e il file _log.txt_ si troveranno nella cartella _bin/_

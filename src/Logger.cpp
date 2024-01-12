/*
 * Autore file: Leonardo Mosele
*/

#include "../include/Logger.h"

Logger::Logger(void)
{
    fout.open("log.txt", std::ios_base::app); /*| std::ios::trunc);*/                                 // Open the file in the constructor
    fout << "La partita e' iniziata!";
    if (!fout.is_open())
        std::cerr << "Errore nell'apertura del file di log." << std::endl;                      // Error opening file
}

void Logger::log(const std::string& str)
{
    if(fout.is_open())
        fout << "- " << str << std::endl;                                                       // Print in log.txt str
    else
        std::cerr << "Impossibile scrivere sul file di log, il file non e' aperto correttamente." << std::endl;
}

Logger& Logger::get_instance(void)
{
    static Logger instance;
    return instance;
}

Logger::~Logger()
{
    if(fout.is_open())
        fout.close();                                                                           // Closing output
}

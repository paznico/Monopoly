/*
 * Autore file: Leonardo Mosele
*/

#include "../include/Logger.h"

Logger::Logger(void)
{
    // Open the file in the constructor
    fout.open("log.txt");
    fout << "La partita e' iniziata! \n";
    if (!fout.is_open())
        // Error opening file
        std::cerr << "Errore nell'apertura del file di log." << std::endl;
}

void Logger::log(const std::string& str)
{
    if(fout.is_open())
        // Print in log.txt str
        fout << "- " << str << std::endl;
    else
        std::cerr << "Impossibile scrivere sul file di log, il file non e' aperto correttamente." << std::endl;
}

Logger& Logger::get_instance(void)
{
    // Return instance of logge
    static Logger instance;
    return instance;
}

Logger::~Logger()
{
    // Closing output file
    if(fout.is_open())
        fout.close();
}

/*
 * Autore file: Leonardo Mosele
*/

#include "../include/Logger.h"

Logger::Logger(void)
{
    fout.open("log.txt");                                                                       // Open the file in the constructor
    fout << "La partita e' iniziata! \n";
    if (!fout.is_open())
        std::cerr << "Errore nell'apertura del file di log." << std::endl;                      // Error opening file
}

void Logger::log(const std::string& str)
{
    if(fout.is_open())
        fout << "- " << str << std::endl;                                                       // Print @param in log.txt 
    else
        // Error if the file isn't correctly open
        std::cerr << "Impossibile scrivere sul file di log, il file non e' aperto correttamente." << std::endl;
}

Logger& Logger::get_instance(void)
{
    // Create an instance to have access to the class and be able to use it in multiple classes without having to create the object
    static Logger instance;
    return instance;
}

Logger::~Logger()
{
    // Destructor that close the output in the file
    if(fout.is_open())
        fout.close();                                                                           // Closing output
}

/*
 * Autore file: Leonardo Mosele
 */

#include "../include/Logger.h"

Logger::Logger(void)
{
    fout.open("log.txt", std::ios_base::out | std::ios_base::app);  // Open the file in the constructor
}

void Logger::add_log(const std::string& str)
{
    fout << str << '\n';
}

Logger::~Logger()
{
    fout.close();
}

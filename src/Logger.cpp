/*
 * Autore file: Leonardo Mosele
 */

#include "../include/Logger.h";
using namespace std;

Logger::Logger(void)
{
    ofstream fout("log.txt", ios_base::out | ios_base::app);
}

void Logger::add_log(const std::string& str)
{
    fout<<str<<'\n';
}

Logger::~Logger()
{
    fout.close();
}
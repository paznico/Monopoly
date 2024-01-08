/*
 * Autore file: Leonardo Mosele
 */
#include "../include/Logger.h";
using namespace std;

Logger::Logger(void)
{
    ofstream fout("log.txt", ios_base::out | ios_base::app);
}

void Logger::add_log(string str)
{
    fout<<str<<'\n';
}

std::ostream& operator<<(ostream& os, std::string str)
{
    add_log(str);
    return os << str;
}
#include "../include/Logger.h";
using namespace std;

Logger::Logger(void)
{
    ofstream fout("logger.txt", ios_base::out | ios_base::app);
}

void Logger::add_log(string str)
{
    fout<<str<<'\n';
}
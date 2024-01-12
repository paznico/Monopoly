/*
 * Autore file: Leonardo Mosele
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class Logger
{       
private:
    std::ofstream fout;

public:
    /* Constructor */
    Logger(void);

    /* Functions that adds a string */
    void log(const std::string&);
    static Logger& get_instance(void);

    /* Destructor */
    ~Logger();
};

#endif
/*
 * Autore file: Leonardo Mosele
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

class Logger
{       
private:
    std::ofstream fout; 

public:
    /* Constructor */
    Logger(void);

    /* Function that adds a string */
    void add_log(const std::string&);

    /* Destructor */
    ~Logger();
};

#endif

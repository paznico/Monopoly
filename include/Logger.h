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
    Logger(void);                                           // Default

    /* Functions */
    void log(const std::string&);
    // Return a static instance of logger so we can log
    // every string from every file without creating different
    // logger objects
    static Logger& get_instance(void);

    /* Destructor */
    ~Logger();
};

#endif
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Logger
{       
        private:
                ofstream fout;
        
        public:
                /* Constructor */
                Logger(void);

                /* Function that add a string */
                void add_log(std::string);
};

#endif
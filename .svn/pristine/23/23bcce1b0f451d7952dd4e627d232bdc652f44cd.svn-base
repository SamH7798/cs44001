#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <vector>
#include <iostream>
#include<fstream>

using std::cout; using std::endl;
using std::vector; using std::string;


class Logger {
public:
        static Logger& instance() {  //myers version of instance
		static Logger lgr;
		return lgr;
	}
	
	void report(const string& appended) {
	  if (fout.is_open()) {   //checks to see if the files are open
	        fout << appended << endl;  // appends whatever string is passed
		}
	}
	
         ~Logger() { fout.close(); }  //closes file at end of program

private:
        std::ofstream fout;  // payload
        Logger() {// constructor that opens logger.txt
		fout.open("logger.txt", std::fstream::out | std::fstream::app);
	}
         //makes sure no new objects are createdx
	Logger(const Logger&) {}
	Logger& operator=(const Logger&) {}
	
};




#endif

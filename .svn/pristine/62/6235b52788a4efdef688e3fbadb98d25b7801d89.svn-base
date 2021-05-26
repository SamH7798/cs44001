// Samuel Hill 
//1-27-21
//Word Count 
// reads a file and outputs the words used and how many times each word is used

#include "wordcount.hpp"

int main(int argc, char* argv[]) {
	if (argc >= 1) {
		for (int i = 0; i < argc; ++i) {
			cout << argv[i] << " ";           //outputs arguments in command line
		}
		cout << endl << endl;
		cout << "Words used are:" << endl;
		cout << "==============="<< endl;

		std::ifstream textfile(argv[1]);    //opening the text file;
		string line;                   // line that will be retrieved from text file
		WordList wl;               

		while (!textfile.eof()) {
			getline(textfile, line);
		
			wl.splitString(line);                   // splits line into words and adds them to arrau

		}
		
		wl.print();
	}
	else {
		cout << "no files passed on command line"<< endl;
	}

}

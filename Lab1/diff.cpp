//Samuel Hill
// 1-19-21
// Reads 2 files from command line and compares and read both files
// check file name length if carrot doesnt line up

#include <iostream>
#include <fstream>
#include<string>
int main(int argc, char* argv[]) {

	if (argc == 3) {
		for (int i = 0; i < argc; ++i) {
			// for (auto e : argv)
			std::cout << argv[i] << " ";           //outputs arguments in command line
		}
		std::cout << std::endl << std::endl;

		std::ifstream file1(argv[1]);    //opening the first file
		std::ifstream file2(argv[2]);    // opening the second file

		std::string file1s;
		std::string file2s;
		
		int linenum = 1;
		
		while (!file1.eof() || !file2.eof()) { // reading both files line by line
			getline(file1, file1s);
			getline(file2, file2s);

			//int spacelen = file1s.find_first_not_of(file2s); 

	
			if (file1s != file2s) {
				int spacelen = file1s.find_first_not_of(file2s);// instance where strings mismatch

				if (linenum >= 10) {
					spacelen = spacelen + 1;  // lines up carrot for a linenum >= 10
				}
				if (linenum >= 100) {
					spacelen = spacelen + 2;  //lines up carrot for a linenum >=100
				}
				
				
				std::cout << argv[1] << ": " << linenum << ": " << file1s << std::endl; 
				std::cout << argv[2] << ": " << linenum << ": " << file2s << std::endl;
			
				std::cout << std::string(spacelen + 14, ' ') << "^" << std::endl; 
			                  // outputs a line of spaces plus carrot at mismatched point
			
			}
		
			++linenum;
		}
	
	
	}
	else {    
		std::cout << "Incorrect ammount of arguments" <<std::endl;
	}

}
// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(vector<list<string>>& roster, string fileName);

// printing a list out
void printRoster(const vector<list<string>>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last"
			<< endl; exit(1);
	}
	
	// vector of courses of students
	vector <list<string>> courseStudents;
	
	for (int i = 1; i < argc - 1; ++i) {
		vector<list<string>> roster;
		readRoster(courseStudents, argv[i]);


		
	}


	
	vector <list<string>> dropouts;        // contains all the dropouts
	



	

	readRoster(dropouts, argv[argc - 1]);


	
	int index = courseStudents.size() - 1;                      // index at desired position to delete
	for (auto it = courseStudents.end() - 1; it >= courseStudents.begin();  --it, --index) {   // loops through courseStudents fron end
		
	  for (auto id = dropouts.begin(); id != dropouts.end(); ++id) {                // loops through dropouts
			
	    if (it->front() == id->front() ) {                            // if dropout name is == to coursestudent name
				
				//courseStudents.erase(courseStudents.begin() + index);
	      courseStudents.erase(courseStudents.begin() + index);              // deletes at disered position
				

				
			}
		}	
		
		
	}
     


	printRoster(courseStudents);                 // prints roster without dropouts
	
	

}

// reading in a file of names into a list of strings
void readRoster(vector<list<string>>& roster, string fileName) {
	
	ifstream course(fileName);
	string first, last, coursefile;
	coursefile = fileName;                       // name of the file
	int pos = coursefile.find_first_of('.');           
	string coursename = coursefile.erase(pos);            // creates the course name from the file name

	

	while (course >> first >> last) {

		
	  bool found = false;                    // a bool that is true when name is found and false when it is not
	

	  for (auto it = roster.begin(); it != roster.end(); ++it) {              // loops through roster
				
			

	    if (first + ' ' + last + ":" == it->front()) {         // if name is found
					
					found = true;
					it ->push_back(coursename);            // pushes coursename to position in list
					break;
				}
				
				
			}
	                        if (!found) {                                    // if found is false
			
				  list<string> students;                          // new list of students to be pushed into vector
				  students.push_back(first + ' ' + last + ":");          // pushes back name
			
				  students.push_back(coursename);                    // pushes back coursename
				  roster.push_back(students);                      // pushes list into vector
			}
	}
	course.close();
}

// printing a list out
void printRoster(const vector<list<string>>& roster) {
  for (auto it = roster.begin(); it != roster.end(); ++it) {              //loops through vector of list
		
    for ( auto str : *it) {                // range based for loop to go though whats derefferenced in roster
			cout << str << ' ';
		}
		cout << endl;
	}			
	
}

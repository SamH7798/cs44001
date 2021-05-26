// reading a list from a fileName
#include "rosterOb.hpp"
//void readRoster(list<Student>& roster, string fileName);
// printing a list out
//void printRoster(const list<Student>& roster);
int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last" << endl; exit(1);
	}

	// vector of courses of students
	list<Student> courseStudents;

	for (int i = 1; i < argc - 1; ++i) {
		list<Student> roster;
		readRoster(courseStudents, argv[i]);

		

	}
	//	printRoster(courseStudents);

	list<Student> dropouts;
	readRoster(dropouts, argv[argc - 1]);
	//	cout << "-----Dropouts------" << endl << endl;
	//	printRoster(dropouts);
	



	
	for (auto id = dropouts.begin(); id != dropouts.end(); ++id){               // iterates through the list of dropouts
		
	  for (auto it = courseStudents.begin(); it != courseStudents.end();) {            // iteratres through the list of course students
                          
	    if (it->getFirst() == id->getFirst() && id->getLast() == it->getLast()) {      // if the  name of course students is found in dropouts
			
	      it = courseStudents.erase(it);            // erases the position where the dropout is found
				
			} else {
	                    ++it;       //if not found iterates to the next position inside the list
                        }
		
		
		}
	
	}
	//	cout<< "--------drops removed------------" << endl << endl;	
	printRoster(courseStudents);                    // prints the course students without the dropouts

}

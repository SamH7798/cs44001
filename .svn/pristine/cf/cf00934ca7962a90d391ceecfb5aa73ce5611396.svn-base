#include "rosterMap.hpp"

int main(int argc, char* argv[]) {

  
	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last" << endl; exit(1);
	}

	// map of courses of students
	map<Student, list<string>>  courseStudents;
	
	for (int i = 1; i < argc - 1; ++i) {
	
		readRoster(courseStudents, argv[i]);

	}
	
	
	map<Student, list<string>> dropouts;                  // map of dropouts
	readRoster(dropouts, argv[argc - 1]);

	for (auto id = dropouts.begin(); id != dropouts.end(); ++id) {                   //iterates  through dropouts
	  for (auto it = courseStudents.begin(); it != courseStudents.end();) {         //iterates through courseStudents
	    if (id->first.getFirst() == it->first.getFirst()                            // if first courseStudent name = dropout name            
		&& id->first.getLast() == it->first.getLast()) {           
	      it = courseStudents.erase(it);                                            // erase at current positon/ it = position afer erases
	    }                                               

	else {
	  ++it;                              // if not found iterator moves to next positoin of courseStudents                 
         	}
	  }  
	
	}  

	printRoster(courseStudents);                     // prints courseStudents with dropouts removed

}

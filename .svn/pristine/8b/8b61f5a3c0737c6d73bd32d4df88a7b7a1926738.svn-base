#ifndef rosterMap_HPP_
#define rosterMap_HPP_

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move; using std::map;
using std::pair;


class Student {
public:
	Student(string firstName, string lastName) :
		firstName_(firstName), lastName_(lastName) {}

	// move constructor, not really needed, generated automatically
	/*
	Student(Student&& org) :
		firstName_(move(org.firstName_)),
		lastName_(move(org.lastName_))
	{}
	*/
	// force generation of default copy constructor
	Student(const Student& org) = default;

	string print() const { return firstName_ + ' ' + lastName_; }

	// needed for unique() and for remove()
	friend bool operator== (Student left, Student right) {
		return left.lastName_ == right.lastName_ &&
			left.firstName_ == right.firstName_;
	}

	// needed for sort()
	friend bool operator< (Student left, Student right) {
		return left.lastName_ < right.lastName_ ||
			(left.lastName_ == right.lastName_ &&
				left.firstName_ < right.firstName_);
	}
	string getFirst()const { return firstName_; } // returns first name
	string getLast()const { return lastName_; } // returns last name
private:
	string firstName_;
	string lastName_;
};


void readRoster(map<Student, list<string>>& roster, string fileName) {
	ifstream course(fileName);
	string first, last;
	string coursefile = fileName;                           // name of the file
	int pos = coursefile.find_first_of('.');
	string courseName = coursefile.erase(pos);        // creates the course name from the name of the file
	
	
	while (course >> first >> last) {
	  bool found = false;                              // bool that is false if name is not found and true if it is found
	  list<string> courses;                           // list of string that contains the name of the course  
		
	  for (auto it = roster.begin(); it != roster.end(); ++it) {                   // iterates through roster  
			//auto find = roster.find(it->first);
	    if (it->first.getFirst() == first && it->first.getLast() == last) {              //  if name is found inside roster
	      found = true;                                                     
	      it->second.push_back(courseName);                                  // pushes back course name inside the list at the found positon 
	      break;                                          // breaks out of the loop if found
	    }     
	  }  
		
	  if (!found) {                                                                 
			//courses.push_back(courseName);
			//roster.insert(pair<Student, list<string>>(Student(first, last), courses));
			
	    courses.push_back(courseName);                        // pushed courseName inside the empty list
	    roster.emplace(Student(first, last), courses);                             // adds new student with the courseName
			
			
	  }
	
	}	
	course.close();  
}

// printing a list out
void printRoster(const map<Student, list<string>> roster) {
  for (const auto& student : roster) {                                  // range based for roster
    cout << student.first.print() << ": ";                 // prints the name of the student
    for (auto it = student.second.begin(); it != student.second.end(); ++it ) {        // loops through the list inside each position of the map
      cout << *it << " ";                      // outputs the contents of the list
			}
    cout << endl;  
	}
	// cout << endl;
}


#endif

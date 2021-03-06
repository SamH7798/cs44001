// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018
#ifndef rosterOb_HPP_
#define rosterOb_HPP_

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


class Student {
public:
	Student(string firstName, string lastName, string courseName) {
		firstName_ = firstName;
		lastName_ = lastName;
		pushCourseName(courseName);          // pushes coursename into list of string

		
	}
	
	// move constructor, not really needed, generated automatically
	/*Student(Student&& org) :
		firstName_(move(org.firstName_)),
		lastName_(move(org.lastName_))
	{}*/

	// force generation of default copy constructor
	Student(const Student& org) = default;

	string print() const { return firstName_ + ' ' + lastName_ ; }

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
	void pushCourseName(const string courseName) {
		courseName_.push_back(courseName);
	
	}
        void printList()const {                     // prints the list of strings
	
		
		for (auto str : courseName_) {
			cout << str<< " ";
		}
		
	}

private:
	string firstName_;
	string lastName_;
        list<string> courseName_;                            // list of string that contains the coursename
};
void readRoster(list<Student>& roster, string fileName) {
	ifstream course(fileName);
	string first, last;
	string coursefile = fileName;                           // name of the file
	int pos = coursefile.find_first_of('.');
	string courseName = coursefile.erase(pos);                          // creates the course name from the name of the file
	
	while (course >> first >> last) {
	
	
	  bool found = false;                                    // bool that is false if name is not found and true when it is
		
	
	                  for (auto& student : roster) {                 // range based loop that loops through roster
			    if (student.getFirst() == first && student.getLast() == last) {         //if name is found

					found = true;                                 
					student.pushCourseName(courseName);             // the course name is pushed back where student is found
					break;

				}
			}
		

			  if (!found) {                            // if found is false 
			
		
			    roster.push_back(Student(first, last, courseName));       // pushes a whole student into the list 
				
			
		}
	
	}
	
	course.close();
}

// printing a list out
void printRoster(const list<Student>& roster) {
	
                 for (const auto& student : roster) {         // range based loop that goes through list of students
            	        cout << student.print() << ": ";                 // calls on print functions
			student.printList();
			cout << endl;
			
		}
//	cout << endl;
}

#endif 

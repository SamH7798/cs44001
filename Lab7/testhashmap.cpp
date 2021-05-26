
// demoes hashmap implementation
// Mikhail Nesterenko
// 4/15/2014

#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {

  
  hashmap<int, string> employees;
    employees[123] = "Mike";
   employees[345] = "Charlie";
   employees[192] = "Joe";
   employees[752] = "Paul";
   employees[328] = "Peter";

   int num;
   string name;

   // ask to enter new employee
   cout<< "Enter New Employee Number: ";
   cin>>num;

   
   cout << "Enter New Employee Name: ";
   cin>> name;


   auto inserted = employees.insert(make_pair(num, name));

   // if id number is unique it is added if not error message is outputed
   if(inserted.second){

     cout<<"successfully added"<<endl;

   }
   else{
     cout<<"Can't add employee with same ID number"<< endl;

   }

      cout << "Enter employee number to look for: "; cin >> num;
   auto it = employees.find(num);
   if(it != nullptr){
      cout << it->first << ":" << it->second << endl;
   }
   else{
     cout << "employee not found" << endl;
	}


   // removing from a map
   cout << "Enter employee number to fire: "; cin >> num;
   
   // check if erased successfull message outputed
   //if not error message
   auto removed = employees.erase(num);
   if (removed.second){
      cout << "Employee removed successfully" << endl;
   }
   else{
     cout<<"Cannot Delete Non Exsiting Emlpoyee"<<endl;
   }

   cout << "Rehashing Employees" <<endl;
   employees.rehash(8);
   /*
	// inserting into myHash
	myHash.insert(pair<int, int>(4, 40));
	myHash.insert(pair<int, int>(10, 20));
	 myHash.insert(pair<int, int>(20, 5));
	 myHash[467] = 60;
	 myHash[445]=90;
	   
	 auto result =myHash.insert(make_pair(6, 60));   // returning pair of iterator and bool
	auto result2 = myHash.insert(make_pair(6, 61));

	// testing insert on element that should be inserted
	if (result.second) {
	  cout << "inserted successfully"<< endl;
	}
	else{
	  cout<<"not inserted"<<endl;
	}

	// testing insert on element that cant be inserted
	if (result2.second) {
		cout <<  "inserted successfully" << endl;
	}
	else {
		cout << "not inserted" << endl;
	}


	auto result3 = myHash.erase(4);
	// testing erase on element that should be erased
        if(result.second){
          cout<< "deleted successfully"<<endl;
        }
        else{
          cout<<"not found";
        }
	
	//testing on element that isnt found
	auto result4 = myHash.erase(99);
	if(result4.second){
	  cout<<"deleted successfully"<<endl;
	}
	else{
	  cout<<"not found"<<endl;
	}
	// rehashing the hash to size 8

	cout << "Rehashing myHash" << endl;
	myHash.rehash(8);


	*/
	
}



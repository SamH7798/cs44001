#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm> 
#include<numeric>
#include <iterator> 
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples {
	double weight; // oz
	string color;  // red or green
	void print() const { cout << color << ", " << weight << endl; }
};


double addWeight(double x, double y) {  // function used to add the weight used later on
	return x + y;
}


int main() {
	srand(time(nullptr));
	const double minWeight = 3.;
	const double maxWeight = 8.;

	cout << "Input crate size: ";
	int size;
	cin >> size;

	vector <Apples> crate(size);

	// assign random weight and color to apples in the crate
	// replace with generate()
	
	std::generate(crate.begin(), crate.end(), [=] {                      // generate that assigns random weight to apples in crate
		Apples a;
		a.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
		a.color = rand() % 2 == 1 ? "green" : "red";                         // if 2 it is green if 1 red
		return a;                                                      //returns the object
		});
	
	cout << "Enter weight to find: ";
	double toFind;
	cin >> toFind;

	// count_if()
	
	int cnt = std::count_if(crate.begin(), crate.end(), [=](Apples a) {             //count_if if the weight is greater than the input
	               return a.weight > toFind;                     // returns true if the weight if is greater than input
		});

	cout << "There are " << cnt << " apples heavier than "
		<< toFind << " oz" << endl;
		
	
	// find_if()
	cout << "at positions ";
	auto it = crate.begin();                 // iterator that points the the begining of crate
	
	do {
	  it = std::find_if(++it, crate.end(), [=](Apples a) {                   // iterator is equal to the position found
			return a.weight > toFind;
			});
	  cout << it - crate.begin() << ", ";                           // outputs the position
		
		
	} while (it != crate.end());                    // does this while it doesn't equal the end

	
	// max_element()
	auto maxIt = std::max_element(crate.begin(), crate.end(), [=](Apples a, Apples b) {     // returns an iterator to the position of the heaviest object
			 return a.weight < b.weight;                         // compares the weight of 2 apples
		});

	cout << "Heaviest apple weights:"<< maxIt->weight << "oz"<<endl;

	
	

	// for_each() or accumulate()
	double sum = 0;             // intial value
	auto total = std::accumulate(crate.begin(), crate.end(), sum, [=](double a, Apples b) {  // returns the total weight into double total
	 
		 return a + b.weight;                           // adds the weights and stores them into the intial value
		});
	cout << "Total apple weight is: " << total << " oz" << endl;

	
	cout << "How much should they grow: ";
	double toGrow;
	cin >> toGrow;
	// transform();
	std::transform(crate.begin(), crate.end(),crate.begin(), [=](Apples a)->Apples  {           //transforms the weight of the apples and inserts back into crate
		a.weight += toGrow;          // adds toGrow to the weight
		return a;                   // returns the object back into crate
		});

	
	
	// remove_if()
	cout << "Input minimum acceptable weight: ";
	double minAccept;
	cin >> minAccept;

	crate.erase(std::remove_if(crate.begin(), crate.end(), [=](Apples a) {             // erases the posotion returned by remove_if
		return a.weight < minAccept;
		}), crate.end());

	cout << "removed " << size - crate.size() << " elements" << endl;

	
		
	// bubble sort, replace with sort()
	std::sort(crate.begin(), crate.end(), [=](Apples a, Apples b) {
		return a.weight < b.weight;
		});
	
	
	// moving all red apples from crate to peck
	// remove_copy_if() with back_inserter()/front_inserter() or equivalents
	
	deque<Apples> peck;
	
	std::remove_copy_if(crate.begin(), crate.end(), std::front_inserter(peck), [=](Apples a) { // inserts at the front of peck when callback is true
			return a.color != "red";
			});

	crate.erase(std::remove_if(crate.begin(), crate.end(), [=](Apples a) {   // erases all the red apples in crate
			 return a.color == "red";
			 }), crate.end());

	
	
	// for_each() possibly
		 cout << "apples in the crate" << endl;
		 std::for_each(crate.begin(), crate.end(), [=](Apples a) {   // prints out each apple in crate
			 a.print();
			 });
		 cout << endl;
	
	// for_each() possibly
		 cout << "apples in the peck" << endl;
		 std::for_each(peck.begin(), peck.end(), [=](Apples a) {  // prints out each apple in peck
			 a.print();
			 });


	
	
	// prints every "space" apple in the peck
	// 
	const int space = 3;
	cout << "\nevery " << space << "\'d apple in the peck" << endl;

	
	// replace with advance()/next()/distance()
	// no iterator arithmetic
	
	
	auto id = peck.begin();
	
	while (std::distance(id, peck.end()) != 1) {  // while the distance between id and end != 1


	  if (std::distance(peck.begin(), id) % space  == 0) {   // if the distance between id and begin is evenly disible by 3

	    id->print();     // prints out that apple
		}
		
	  ++id;
	}
	
	
	
	// putting all small green apples in a jam
	// use a binder to create a functor with configurable max weight
	// accumulate() or count_if() then remove_if()
	const double weightToJam = 10.0;
	double jamWeight = 0;
	double addedWeight = 0;

	auto fp = std::bind(addWeight, std::placeholders::_1, std::placeholders::_2);  // returns functor using binder that binds addWeight
	
	jamWeight = std::accumulate(crate.begin(), crate.end(), addedWeight, [=](double a, Apples b) {  // adds up all the values inside lambda into addedWeight
		if (b.weight < weightToJam) {    
		  return fp(a, b.weight);  // adds the weight using functor if objects weight is less than weightToJam
		}
		return 0.0;  // if weight is not less than weightToJam then nothing is added

	    });
	crate.erase(std::remove_if(crate.begin(), crate.end(), [=](Apples a) {  // removes if weight is less than 10
		return a.weight < weightToJam;
		}),crate.end());
	
	cout << "Weight of jam is: " << jamWeight << endl;
	
}

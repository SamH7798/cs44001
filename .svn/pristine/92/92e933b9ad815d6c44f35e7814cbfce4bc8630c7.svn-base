#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; 
using std::multimap;
enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

struct Fruit {
	Variety v;
	string color; // red, green or orange
};


int main() {
	srand(time(nullptr));
	//vector <Fruit> tree(rand() % 100 + 1);
	multimap<Variety, string> Mtree;
	int size = rand() % 100 + 1;   // random size of the multimap

	for (int i = 0; i < size; ++i) {                    // loops through intill size is reached
		
	  Mtree.emplace(static_cast<Variety>(rand() % 3), colors[rand() % 3]);                // emplaces random fruit/ color
		
	}
	
	
	cout << "Colors of the oranges: " << endl;


	
	for (auto it = Mtree.lower_bound(Variety::orange); it != Mtree.upper_bound(Variety::orange); ++it){   // loops through the orange keys inside
	  cout << it->second << endl;  // outputs the color of the oranges inside

	}
	
}

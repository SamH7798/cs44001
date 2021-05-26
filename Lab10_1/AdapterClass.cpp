#include"AdapterClass.hpp"
int main() {
	int orgSize, difSize; ;// int for the two different sizes
	
	
	cout << "Enter Size For Square: "; // ask the user for the orginal size 
	cin >> orgSize;
	Figure* square = new SquareAdapter(orgSize); // creates a figure pointer and sets it to a newSquareAdapter of the asked size
	square->draw();
	cout << endl;

	cout << "Enter A New Size For The Square: "; // ask the user for the new size 
	cin >> difSize;
	square->resize(difSize); // resizes the square with the user input
	square->draw();

	delete square;
}

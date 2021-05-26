#include"bridgeFigures.hpp"
  int main() {
        int size;// the size of all the figures

	// character to determine the fill and border of the new figures
	char fill, diffFill, hollowBorder,enhancedBorder, enhancedFiller;

	// ask for size from user
	cout << "Enter Size of Squares :";
	cin >> size;

	// ask for the border of the hollow square
	cout << "Enter Border Character of Hollow Square: ";
	cin >> hollowBorder;

	// sets figure pointer to a new hollow square with user input as the border
	Figure* hollowS = new Square(size, static_cast<Fill*>(new Hollow(hollowBorder)));
	hollowS->draw();
	cout << endl;
	delete hollowS;

	// ask user for character to be used for a filled square
	cout << "Enter Fill Character of Solid Square:";
	cin >> fill;

	//  sets figure pointer to a new square that is filed with user input
	Figure* fillS = new Square(size, static_cast<Fill*>(new Filled(fill)));
	fillS->draw();
	cout << endl;

	// ask user for a character for a different fill to change the filled square
	cout << "Enter Character To Change Fill: ";
	cin >> diffFill;

	// invokes changeFill with user input to change the filled square
	fillS->changeFill(static_cast<Fill*>(new Filled(diffFill)));
	fillS->draw();
	delete fillS;
	cout << endl;

	// ask user for a border and fill character fo enhanced fill
	cout << "Enter Border and Fill Character For Enhanced Fill: " << endl;
	cout << "Enter Fill:";
	cin >> enhancedFiller;
	cout << "Enter Border:";
	cin >> enhancedBorder;

	// sets figure pointer to a new enahnced fill square with user inputer for the border and the fill
	Figure* enhancedS = new Square(size, static_cast<Fill*>(new EnhancedFill(enhancedFiller, enhancedBorder)));
	enhancedS->draw();
	delete enhancedS;

}

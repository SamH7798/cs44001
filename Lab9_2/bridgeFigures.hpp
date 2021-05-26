// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014


#include <iostream>

#ifndef BRIDGEFIGURES_H_
#define BRIDGEFIGURES_H_

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
  
        Fill(char fillChar, char borderChar) :fillChar_(fillChar), borderChar_(borderChar) {} // contructor changed to take a border and fill
	virtual char getBorder() = 0;
	virtual char getInternal() = 0;
	virtual ~Fill() {}
protected:
        char fillChar_; // fill character
        char borderChar_; // border character
};

// concrete body
class Hollow : public Fill {
public:
        Hollow(char borderChar) :Fill(borderChar, ' ') {} // changing contruter to take a border character and space for fill
        char getBorder() override { return fillChar_; } // returns border
        char getInternal() override { return ' '; } // returns fill which is space
	~Hollow() {}
};



// another concrete body
class Filled : public Fill {
public:
        Filled(char fillChar) :Fill(fillChar, fillChar) {} // changing contructor to place one character for the border and the fill
        char getBorder() override { return borderChar_; } // returns the border
        char getInternal() override { return fillChar_; }// returns the fill
	~Filled() {}
};

// new class that creates a fill and a border of two different characters
class EnhancedFill : public Filled {
public:
	
        EnhancedFill(char fillChar, char borderChar):Filled(fillChar){   // contructer that takes in a border and fill and uses contructer delagation for filled
	         borderChar_ = borderChar; // sets border
		 fillChar_ = fillChar; // sets filled 
	};
	~EnhancedFill() {}
};

// abstract handle
class Figure {
public:
	Figure(int size, Fill* fill) : size_(size), fill_(fill) {}

        // function that changes the fill of a figure by reseting fill to a new fill
	void changeFill(Fill* fill) {
	        fill_ = fill; // resetting the fill
	
	};
	virtual void draw() = 0;
	virtual ~Figure() {}
protected:
	int size_;
	Fill* fill_;
};

// concrete handle
class Square : public Figure {
public:
	Square(int size, Fill* fill) : Figure(size, fill) {}
	void draw() override;

};


void Square::draw() {
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j)
			if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
				cout << fill_->getBorder();
			else
				cout << fill_->getInternal();
		cout << endl;
	}
}

#endif

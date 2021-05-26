#include <iostream>
#include <vector>
#include <cstdlib>
#include<ctime>
#include "carFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
	CarLot();
	//test car now takes in positoin at cars4sale
	Car* testDriveCar(int i) { return nextCar(i); }

	// if a car is bought is is returned, requests a new one
	//now populates an array at the positon where a car is bought and replaces it
	Car* buyCar(int i) {
		Car* bought = car4sale_[i];
		car4sale_[i] =
			factories_[rand() % factories_.size()]->requestCar();
		return bought;
	}

	// returns a car at i position in cars4sale
	Car* nextCar(int i) {
		return car4sale_[i];

	}
	//returns the lotSize_
	int lotSize() {
	return lotSize_;
	
	}
	
private:
	Car* car4sale_[10]; // array holding 10 cars in lot
	vector<CarFactory*> factories_;
	int lotSize_ = 10; // size of lot which is 10 cars
    
};


CarLot::CarLot() {
	// creates 2 Ford factories and 2 Toyota factories 
	factories_.push_back(new FordFactory());
	factories_.push_back(new ToyotaFactory());
	factories_.push_back(new FordFactory());
	factories_.push_back(new ToyotaFactory());

	// fills up cars4sale with 10 random cars
	for (int i = 0; i < lotSize_; ++i) {
		car4sale_[i] = factories_[rand() % factories_.size()]->requestCar();
	}
}



CarLot* carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id) {
	if (carLotPtr == nullptr) {
		carLotPtr = new CarLot();
	}

	Car* wantedCar = new Toyota; // the desired car of the toyotaLover
	int timesLooked = 0; // int for number of times looked

	for (int i = 0; i < carLotPtr->lotSize(); ++i) { // loop that goes through the whole lot
		Car* toBuy = carLotPtr->testDriveCar(i);  // sets toBuy to next car in lot using testDriveCar

		cout << "Buyer " << id << endl;
		cout << "test driving "
			<< toBuy->getMake() << " "
			<< toBuy->getModel();

		//if toBuy is the make and model of wantedCar
		if (toBuy->getMake() == "Toyota" && toBuy->getModel() == wantedCar->getModel()) { 
			cout << " love it! buying it!" <<"Car Bought: " << wantedCar->getMake()<< " " 
				<< wantedCar->getModel()<< endl;
			//buy car is invoked and function is exited
			carLotPtr->buyCar(i);
			delete wantedCar; // deletes pointed
			return;
		}
		else { // if toBuy is not equal to wantedCar
			cout << " did not like it!" << endl;
		}
		++timesLooked; // increments timesLooked to keep track
	}
	
	// if the whole lot is looked through the function is exited
	if (timesLooked == carLotPtr->lotSize()) {
		cout << "I could not find the car I wanted Im leaving" << endl;
		delete wantedCar; // deletes pointer
		return;
	}
}

// test-drives a car
// buys it if Ford
void fordLover(int id) {
	if (carLotPtr == nullptr) {
		carLotPtr = new CarLot();
	}
	Car* wantedCar = new Ford; // the desired car of the fordLover
	int timesLooked = 0; // int for number of times looked

	for (int i = 0; i < carLotPtr->lotSize(); ++i) { // loop that goes through the whole lot
		Car* toBuy = carLotPtr->testDriveCar(i); // sets toBuy to next car in lot using testDriveCar

		cout << "Buyer " << id << endl;
		cout << "test driving "
			<< toBuy->getMake() << " "
			<< toBuy->getModel();

		//if toBuy is the make and model of wantedCar
		if (toBuy->getMake() == "Ford" && toBuy->getModel() == wantedCar->getModel()) {
			cout << " love it! buying it!" << "Car Bought: " << wantedCar->getMake() << " "
				<< wantedCar->getModel() << endl;
			//buy car is invoked and function is exited
			carLotPtr->buyCar(i);
			delete wantedCar; // deletes pointer
			return;
		}
		else {// if toBuy is not equal to wantedCar
			cout << " did not like it!" << endl;
		}
		++timesLooked; // increments timesLooked to keep track
	}
	// if the whole lot is looked through the function is exited
	if (timesLooked == carLotPtr->lotSize()) {
		cout << "I could not find the car I wanted Im leaving" << endl;
		delete wantedCar; // deletes pointer
		return;
	}

}



int main() {
	srand(time(nullptr));

	const int numBuyers = 10;
	for (int i = 0; i < numBuyers; ++i)
		if (rand() % 2 == 0)
			toyotaLover(i);
		else
			fordLover(i);

}

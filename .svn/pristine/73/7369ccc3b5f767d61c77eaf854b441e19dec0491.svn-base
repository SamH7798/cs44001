#include <string>
#include<iostream>
#include<list>
#include<set>
#include <vector>
#include <deque>
#ifndef COFFEESHACK_H_
#define COFFEESHACK_H_
using std::cout; using std::cin; using std::endl; using std::string;
using std::list; using std::set; using std::vector; using std::deque;
using std::size_t;

enum class DrinkType { small, medium, large };

// drink class
class Drink {
public:
    Drink(DrinkType type = DrinkType::small, int price = 0) :  // constructor that sets the type of drink and price
        type_(type), price_(price) {} 
    virtual double getPrice() const { return price_; }; // returns the price
    virtual std::string getName() const { return name_; }// returns the name of the drink
    void addTop() { ++numTops; } // adds the number of toppings
    int Tops() { return numTops; }  // returns the number of toppings
    void setDrinkName(const string s) { name_ = s; }; // sets the drinks name
    void setSize(const char s) {  // sets the size and price of a drink using a character
        if (s == 's') { type_ = DrinkType::small; size_ = "small"; price_ = 1.00; name_ = size_ + " coffee"; }
        if (s == 'm') { type_ = DrinkType::medium; size_ = "medium"; price_ = 2.00;name_= size_ + " coffee"; }
        if (s == 'l') { type_ = DrinkType::large; size_ = "large"; price_ = 3.00; name_ = size_ + " coffee"; }
    }

    void setPrice(const double p) { price_ = p; } // sets the price of the drink
    void setName(const string n) { name_ = n; }   // sets the name of the drink
    string getOrderName() { return name_; } // returns the name of the drink
    string getSize() { return size_; } // gets the size of the drink
   
private:
    double price_;  // price of the drink
    DrinkType type_; // type of the drink
    string size_; // size of the drink
    string name_; // name of the drink
    int numTops = 0; // number of toppings
};

class Sprinkles : public Drink { // sprinkles class that inherits from drink
public:
    Sprinkles(Drink* d) : drink_(d) {} // constructor

    double getPrice() const override { return  0.5; } // returns the price of added sprinkles
    string getName() const override {   // returns ", sprinkles" if there is more than one topping
        if (0 < drink_->Tops() ) {
            drink_->addTop();
            return  ", sprinkles";
        
        }
        else {
            drink_->addTop();
            return  " with sprinkles"; //  returns "with sprinkles" if there is 0 toppings
            
        }
       
    }

private:
    Drink* drink_; // private pointer to drink

};

class Caramel : public Drink { // carmel class that inherits from drink
public:

    Caramel(Drink* d) : drink_(d){} // constructor

    double getPrice() const override { return  0.20; } // returns the price of added carmel

    string getName() const override { // returns ", carmel" if there is more than one topping
        if (0 < drink_->Tops()) {
            drink_->addTop();
            return  ", carmel";

        }
        else {
            drink_->addTop();
            return" with carmel";   //  returns "with carmel" if there is 0 toppings

        }

    }

private:
    Drink* drink_; // private pointer to drink

};

class Foam : public Drink { // foam class that inherits from drink
public:
    Foam(Drink* d) : drink_(d) {} // constructor

    double getPrice() const override { return  0.40; }// returns the price of added foam

    string getName() const override {  // returns ", foam" if there is more than one topping
        if (0 < drink_->Tops()) {
            drink_->addTop();
            return  ", foam";

        }
        else {
            drink_->addTop();
            return " with foam" ;  //  returns "with foam" if there is 0 toppings

        }

    }

private:
    Drink* drink_; // private pointer to drink

};
class Ice : public Drink { // ice class that inherits from drink
public:
    Ice(Drink* d) : drink_(d) {} // constructor
    double getPrice() const override { return  0.10; } // returns the price of added ice

    string getName() const override {  // returns ", ice" if there is more than one topping
        if (0 < drink_->Tops()) {
            drink_->addTop();
            return ", ice";

        }
        else {
            drink_->addTop(); 
            return  " with ice";   //  returns "with ice" if there is 0 toppings

        }

    }

private:
    Drink* drink_;  // private pointer to drink

};


//observer class
class Customer{
public:
    Customer() { cout << ""; }; // default constructor for customer
    Customer(class Barista* b); // constructor for cusutomer
    virtual void notify() const = 0; // notify used to notify all the customers
   

};

// subject class
class Barista {
public:
    void registerCustomer(Customer* c) { // inserts a customer in the set
        customers_.insert(c);
    
    }
    void deregisterCustomer(Customer* c) { // erases the customer in the set
        customers_.erase(c);
    }

    void notifyCustomers() const {
        for (auto c : customers_) {      //notifies all the customers in the set       
                c->notify();            
         }   
    }
    int getSetSize() { return customers_.size(); } // returns the size of the set
private:
    set<Customer*> customers_;

};


Customer::Customer(Barista* b) { // customer constructor that registers itself
    b->registerCustomer(this);
};


class ConcreteBarista; // class declartaton 

// concrete observer
class ConcreteCustomer: public Customer{
public:
    ConcreteCustomer(const string&, ConcreteBarista* b, Drink* d); // constructor
    void notify() const override; // overridden notify
    string orderName() { // returns order name
        return order_ ->getName(); 
    }
    ConcreteCustomer() : name_(""), order_(nullptr), b_(nullptr){} // default constructor
   
    string getName() { return name_; } // returns the name of the customer
    void setName(const string name) { name_ = name; } // sets the name of the customer
    void setDrink(Drink* d) {  order_ = d; } // sets the drink
private:
    string name_; // name of the customer
    Drink* order_; // drink pointer that is the customers drink
    ConcreteBarista* b_; // pointer to concrete subject 
};

// concrete subject
class ConcreteBarista : public Barista {
public:
    ConcreteBarista(ConcreteBarista* successor = nullptr): successor_(successor) { } // constructor
    void drinkMade(const string drink, const string customerName) { // notifies all customers that a drink is made and sets the drink that is ready to serve
        drinkMade_ = drink; 
        customerName_ = customerName;
        notifyCustomers();
    }
    string getDrink() { return drinkMade_; } // returns drink made
    string getCustomerName() { return customerName_; }// returns customer's name that has the their drink ready

    virtual void handleRequest(const string drink) { // handles the request of a drink and passes it on
        if (successor_ != nullptr) {
            successor_->handleRequest(drink);
        }
        else {
            cout << "No one can make this drink" << endl;
        }
        
    }
   
  
private:
    string customerName_; // name of the customers drink that is ready
    string drinkMade_; // drink that is ready to be served
   ConcreteBarista* successor_; //pointer to the barista's successor
  

};

class JuniorBarista :public ConcreteBarista { // junior barista that inherits from barista
public:
    JuniorBarista(ConcreteBarista* successor = nullptr):ConcreteBarista(successor){} // construcor

    void handleRequest(const string drink) override { // handles the request of a drinnk
        size_t found = drink.find("with"); 
        if (found == std::string::npos) { // if with is not found meaning no toppings are added the drink is prepared 
            cout << "Drink prepared by the Junior Barista" << endl;

        }
        else {
            ConcreteBarista::handleRequest(drink); // if with is found the request is passed on
        }
    }
};

class SeniorBarista : public ConcreteBarista { // senior barista that inherits from barista
public:
    SeniorBarista( ConcreteBarista* successor = nullptr):ConcreteBarista( successor) {} // constructor

    void handleRequest(const string drink) override{ // handles the request of a drinnk
        size_t found = drink.find("foam"); 

        if (found == std::string::npos) { // if foam is not found then the drink is prepared by the senior barista
            cout << "Drink prepared by the Senior Barista " << endl;

        }
        else {
            ConcreteBarista::handleRequest(drink); // if foam is found then the request is passed on
        }
    }

};

class Manager : public ConcreteBarista { // manager that inherits from barista
public:
    Manager( ConcreteBarista* successor = nullptr) :ConcreteBarista( successor) {} // constructor

    void handleRequest(const string drink)override { // handes request if the junior and senior barista cant prepare the drink
        cout << "Drink prepared by the Manager" << endl;
    }

};






ConcreteCustomer::ConcreteCustomer(const string& name, ConcreteBarista* b, Drink* d): // constructor of concrete customer
    name_(name),b_(b), order_(d), Customer(static_cast<Barista*>(b)) {

}
void ConcreteCustomer::notify() const { // notify

    if (order_ != nullptr) { 
       
        if (b_->getDrink() == order_->getOrderName() && name_ == b_->getCustomerName()) { // if the baristas ready drink is equal the the customer's drink name
            //cout << "Testing Make Drink;" << endl;                                       // and if the customers name matches the ready customers name
            cout << name_ << ", your order Of a " << order_->getOrderName() << " is ready that will be " << order_->getPrice() << " Dollars" <<endl << endl; // cashing out dialog
          
        }
    }
 }


#endif

// Sam HIlls tree Maiden names are printed and user can see if two canidates can marry


#include <iostream>
#include <string>
#include <vector>



#ifndef TREE_H_
#define TREE_H_


using std::cout; using std::endl; using std::cin;
using std::string;
using std::vector;

class Person { // component
public:
    Person(string firstName, Person* spouse, Person* father, Person* mother) :
        firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
    const string& getFirstName() { return firstName_; }
    Person* getSpouse() { return spouse_; }
    void setSpouse(Person* spouse) { spouse_ = spouse; }
    Person* getFather() { return father_; }

    virtual void accept(class PersonVisitor*) = 0;
    virtual ~Person() {}
private:
    const string firstName_;
    Person* spouse_;
    Person* father_;
    Person* mother_;
};


// leaf
// man has a last name 
class Man : public Person {
public:
    Man(string lastName, string firstName, Person* spouse,
        Person* father, Person* mother) :
        lastName_(lastName),
        Person(firstName, spouse, father, mother) {}
    const string& getLastName() { return lastName_; }
    void accept(class PersonVisitor* visitor) override;
private:
    const string lastName_;
};

// composite
// woman has a list of children
class Woman : public Person {
public:
    Woman(vector<Person*> children,
        string firstName,
        Person* spouse,
        Person* father, Person* mother) :
        children_(children),
        Person(firstName, spouse, father, mother) {}
    const vector<Person*>& getChildren() {
        return children_;
    }
    void setChildren(const vector<Person*>& children) {
        children_ = children;
    }
    void accept(class PersonVisitor* visitor) override;
private:
    vector<Person*> children_;
};

// abstract visitor
class PersonVisitor {
public:
    virtual void visit(Man*) = 0;
    virtual void visit(Woman*) = 0;

 // -----------------------------------


    virtual ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor* visitor) {
    visitor->visit(this);
    if (this->getSpouse() != nullptr) {
        visitor->visit(static_cast<Woman*>(this->getSpouse())); // visits the mans spouse to get all the names
       
    }
}
static int x;
void Woman::accept(PersonVisitor* visitor) {
    // children traversal through mother only
    // father's children are not traversed so as not 
    // to traverse them twice: for mother and father
    visitor->visit(this);
   
    // traversing descendants
    if (this->getSpouse() != nullptr) {
        visitor->visit(static_cast<Man*>(this->getSpouse()));
    }
    for (auto child : children_) {
        //visitor->visit(child);
        child->accept(visitor);
       
       
    }

}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << " " <<
            m->getLastName() << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << " ";
        if (w->getSpouse() != nullptr)
            cout << static_cast<Man*> (w->getSpouse())->getLastName();
        else if (w->getFather() != nullptr)
            cout << static_cast<Man*> (w->getFather())->getLastName();
        else
            cout << "Doe";
        cout << endl;
    }


};
class MaidenName :public PersonVisitor { // maiden name vistor that inherits from personvisitor
    void visit(Man* m)override {
        cout << ""; // men have no maiden name
    }
    void visit(Woman* w)override { // gets the womens maden name
        if (w->getFather() != nullptr) { // if father exist then gets fathers last name
            cout << w->getFirstName() << "'s maiden name is: " << static_cast<Man*> (w->getFather())->getLastName() << endl;
        }
        else { // if father doesnt exist then maiden name is doe
            cout << w->getFirstName() << "'s maiden name is: " << "Doe";
            cout << endl;
        }
    
    }


};
class Compatibility : public PersonVisitor {//class that inherits from person vistior
public:
    Compatibility(string canidate1 = "", string canidate2 = ""):canidate1_(canidate1), canidate2_(canidate2) {} // constructor
    void visit(Man* m) override {  // visit for man pointer that sets the canidate sets p1 or p2 based on string
        //cout << "Man Visited" << endl;
            
        if ((m->getFirstName() + " " + m->getLastName()) == canidate1_) { // sees if the mans name is equal to the canidate1 if so the canidate is set
           // Person* p1 = static_cast<Person*>(m);
            p1 = m; // the first canidate is set
            //cout << "Person 1 set to man" << p1->getFirstName()<< endl;
        }
        if ((m->getFirstName() + " " + m->getLastName()) == canidate2_) {// sees if the mans name is equal to the canidate1 if so the canidate is set
            // Person* p2 = static_cast<Person*>(m);
            p2 = m; // second canidate is set
          //  cout << "Person 2 set to man: " <<p2->getFirstName() <<endl;
        }

    
    }
    void visit(Woman* w)override { // sees if the women name is equal to the canidates name sets p1 or p2 based on string 
     /*  cout << "Women Visited" << endl;
        cout << "canidate1: " << canidate1_ << endl;
        cout << "canidate2: " << canidate2_ << endl;
        */
        string wName = (w->getFirstName() + " "); // string used to get the womans full name
        if (w->getSpouse() != nullptr) { wName += static_cast<Man*> (w->getSpouse())->getLastName(); } // adds on spouses last name if spouse exist
        else if (w->getFather() != nullptr) { wName += static_cast<Man*> (w->getFather())->getLastName(); } // adds farths last name if there is no spouse and father exist
        else { wName += "Doe"; } // if father and spouse dont exist last name is doe
        
        if (wName == canidate1_) {// sees if the womans name is equal to the canidate1 if so the canidate is set
            p1 = w; // canidate is set
           // cout << "Person 1 set to Woman" << p1->getFirstName() << endl;
        }
        if (wName == canidate2_) {// sees if the womans name is equal to the canidate2 if so the canidate is set
            p2 = w; // canidate is set
            //cout << "Person 2 set to Woman:" << p2->getFirstName() << endl;
        }
       
      
    }

    bool canMarry() { // bool function that sees if p1 and p2 can marry once they are set
        if (p1 == nullptr || p2 == nullptr) { // if either canidate doesn't exist then false is returned
            cout << "enter valid canidate" << endl; return false;
        }
        string canidate1LastName = canidate1_, canidate2LastName = canidate2_;// strings modified to get the last name of both canidates
        int pos = canidate1LastName.find_first_of(" ");
        canidate1LastName.erase(canidate1LastName.begin(), canidate1LastName.begin()+ pos + 1); // gets the last name of canidate1 based on pos
       

        pos = canidate2LastName.find_first_of(" ");
        canidate2LastName.erase(canidate2LastName.begin(), canidate2LastName.begin() + pos + 1); // gets the last name of canidate1 based on pos
       
        if (canidate1_ == canidate2_) { // one person cannot marry themselves 
             return false;
        }
      
    
        if (p1->getSpouse() != nullptr && p2->getSpouse() != nullptr) { // if either of them have a spouse they cannot marry
            return false;
        }
        

        // checks to see of mother or fathers are the same incase of a step parent situation
        if (p1->getFather() != nullptr && p2->getFather() != nullptr) {
                // if last names are differesnt they may have the one of the same parents
            if (p1->getFather()->getFirstName() + static_cast<Man*>(p1->getFather())->getLastName()
                == p2->getFather()->getFirstName() + static_cast<Man*>(p2->getFather())->getLastName()) { // if fathers are the same
               // cout << " Same Dad" << endl;
                return false;  
            }
            if (p1->getFather()->getSpouse() != nullptr && p2->getFather()->getSpouse() != nullptr) {
                if (p1->getFather()->getSpouse()->getFirstName() + static_cast<Man*>(p1->getFather())->getLastName()  // if mothers are the same
                    == p2->getFather()->getSpouse()->getFirstName() + static_cast<Man*>(p2->getFather())->getLastName()) {
                    return false;
                }
            
            
            }
         }
        if (canidate1LastName == canidate2LastName) { // if last names are the same meaning may be siblings or have parent child-relationship
            return false;
        }
        
        return true;
    }
 
    
    void setCanidate1(const string s) { // sets canidate one with string input
         canidate1_ = s;
    }

    void setCanidate2(const string s){ // sets canidate two with string input
        canidate2_ = s;
    }
   // bool getCanMarry() const { return canMarry_; }
private:
    Person* p1 = nullptr; // person one that is set eventually using canidate1 string input
    Person* p2 = nullptr; // person two that is set eventually using canidate2 string input
    string canidate1_; // string that is asked by the user and is used to find the person in the tree
    string canidate2_; // string that is asked by the user and is used to find the person in the tree
    //bool canMarry_ = false;
};
class ChildrenPrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << ": ";
        Woman* spouse = static_cast<Woman*>(m->getSpouse());
        if (spouse != nullptr)
            printNames(spouse->getChildren());
        cout << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << ": ";
        printNames(w->getChildren());
        cout << endl;
    }

  
  

 
private:
    void printNames(const vector<Person*>& children) {
        for (const auto c : children)
            cout << c->getFirstName() << ", ";
    }
};







#endif

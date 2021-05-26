#include"tree.hpp"


// demonstrating the operation
int main() {

    // setting up the genealogical tree      
    // the tree is as follows
    //    
    //
    //       James Smith  <--spouse-->   Mary 
    //	                                  |
    //	                                 children -------------------------
    //	                                  |              |                |
    //	                                  |              |                |
    //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
    //	                                  |
    //	                                 children------------
    //	                                  |                 |
    //                                     |                 |
    //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
    //	       |
    //	     children
    //	       |
    //          |
    //	     Susan


    // first generation
    Man* js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman* ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);

    // second generation
    Woman* ps = new Woman({}, "Patricia", nullptr, js, ms);
    Man* wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);

    vector<Person*> marysKids = { ps,
                       new Man("Smith", "Robert", nullptr, js, ms),
                       new Woman({}, "Linda", nullptr, js, ms) };
    ms->setChildren(marysKids);

    // third generation
    Man* mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person*> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) };
    ps->setChildren(patsKids);

    Woman* jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person*> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);


    // defining two visitors
    ChildrenPrinter* cp = new ChildrenPrinter;
    NamePrinter* np = new NamePrinter;

    // executing the traversal with the composite
    // and the specific visitor

    cout << "\nNAME LIST\n";
    ms->accept(np);

    cout << endl << endl;
    
    cout << "CHILDREN LIST\n";
    ms->accept(cp);
    
    //cout << "\nJAMES' CHILDREN\n";
    //js->accept(cp);
    // prints the maiden names of all the woman
    cout << endl << endl;
    MaidenName* mn = new MaidenName;
    cout << "Maiden names of all women" << endl;
    ms->accept(mn);
    cout << endl << endl;

    // ask the user for 2 canidates and sees if they can marry
    string candidate1, candidate2;
    Compatibility* cmp = new Compatibility;
    cout << "Check for marriage compatibility" << endl;
    cout << "Enter first candidate: ";
   std::getline(std::cin, candidate1);
    cmp->setCanidate1(candidate1);
   
    cout << "Enter second candidate: ";
    std::getline(std::cin, candidate2);
    cmp->setCanidate2(candidate2);
    
    
    
    ms->accept(cmp);
    if (cmp->canMarry()) {
        cout << "Can Marry" << endl;
    }
    else {
        if (candidate1 == "Susan Johnson" || candidate2 == "Susan Johnson") { cout << "A minior(Susan Johnson) cannot marry" << endl; }
        cout << "Can't Marry" << endl;
    }

 
}

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>


#ifndef OBSERVERREGISTRY_H_
#define OBSERVERREGISTRY
using std::cout; using std::endl;
using std::map; using std::set;
using std::string;

class Observer;
class Subject;

class EventRegistry {
public:
    static void registerObserver(string, Observer*); //replaced parameter with string
    static void deregisterObserver(string, Observer*); //replaced parameter with string
    static void handleMessage(Subject*);
private:
    static map<string, set<Observer*>> observerMap_; // replaced first type with a string
};


// initialize the static map
map<string, set<Observer*>> EventRegistry::observerMap_;


class Observer {
public:
    Observer(const string& name) : name_(name) {}
    string getName() const { return name_; }
    void subscribe(string s) { EventRegistry::registerObserver(s, this); } //replaced parameter with string
    void unsubscribe(string s) { EventRegistry::deregisterObserver(s, this); } //replaced parameter with string
    void handleMessage(Subject*);
private:
    string name_;
};

class Subject {
public:
    Subject(const string& name) : name_(name) {}
    string getName() const { return name_; }
    void generateMessage() {
        cout << name_ << " sent a message" << endl;
        EventRegistry::handleMessage(this);
    }
private:
    string name_;
};

void EventRegistry::registerObserver(string s, Observer* o) { //replaced parameter with string
    observerMap_[s].insert(o);
    cout << o->getName() << " subscribed to " << s << endl;
}

void EventRegistry::deregisterObserver(string s, Observer* o) { //replaced parameter with string
    observerMap_[s].erase(o);
    cout << o->getName() << " unsubscribed from " << s << endl;
}

void EventRegistry::handleMessage(Subject* s) {
    for (auto e : observerMap_[s->getName()])
        e->handleMessage(s);
}

void Observer::handleMessage(Subject* s) {
    cout << name_ << " received message from " << s->getName() << endl;
}


#endif

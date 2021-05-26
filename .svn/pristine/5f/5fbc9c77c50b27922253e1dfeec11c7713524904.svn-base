//Sam Hill's State Pattern Process model
#include <iostream>
#include <string>
#include <vector>
#include<deque>


#ifndef STATEPATTERN_H_
#define STATEPATTERN_H_
using std::cin; using std::cout; using std::endl; using std::string;
using std::vector; using std::deque;

class State;

class Process {
public:
	Process();
	//behaviors
	void admitted();
	void interrupt();
	void ioWait();
	void ioCompletion();
	void schedularDispatch();
	void exit();
	
	string report(); // reports the state
	
	

	void changState(State* s) { //changes state of process
		state_ = s;
	}
	int returnID() { return pID; } // returns the id for each process

	void setID(int i) { pID = (i+ 1); }; // sets the process id for each process

	//clone used for prototype
	Process* clone() { return new Process(); }
	

private:

	int pID = 0; // process ID
	State* state_; // current state for process

};



class State {

public:
	//state virtual functions to be overrided by concrete classes
	virtual void admitted(Process*) {}
	virtual void interrupt(Process*) {}
	virtual void ioWait(Process*) {}
	virtual void ioCompletion(Process*) {}
	virtual void schedularDispatch(Process*) {}
	virtual void exit(Process*) {}
	
	
	virtual string report() = 0;
	// changes the state for the process with a new state and process's change state function 
	void changeState(Process* p, State* s) {
		p->changState(s);
		
	}
	
};

// class used for a new process
class NewP : public State {
public:
	//New instance
	static State* instance() {
		static State* onlyInstance = new NewP;
		return onlyInstance;
	}
	string report() override {
		return "is being made";
	}
	NewP() {}

	void admitted(Process*) override; //NewP uses admitted to change state to ready
private:
	//put in private to avoid new creation
	NewP(const NewP&) {}
	NewP& operator=(const NewP&) {}

	

};

// class used for the ready state
class Ready : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Ready;
		return onlyInstance;
	}

	string report() override {
		return "is Ready";
	}

	void schedularDispatch(Process*) override; // ready uses schedualrDispatch to change state to running


};

// class used for the running state
class Running : public State {
public:

	static State* instance() {
		static State* onlyInstance = new Running;
		return onlyInstance;
	}
	string report() override {
		return "is Running";
	}

	void interrupt(Process* p) override; // uses interrupt for change state to ready again
	void ioWait(Process* p) override;  // uses ioWait to for change state to waiting
	void exit(Process* p) override;  // uses exit to change state to termiate
};

//class used for waiting state
class Waiting : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Waiting;
		return onlyInstance;
	}
	string report() override {
		return "is Waiting";
	}
	void ioCompletion(Process* p)override; // uses ioCOmpletion to change state to ready

};

// class used for the Terminated state
class Terminated :public State {
public:
	static State* instance() {
		static State* onlyInstance = new Terminated;
		return onlyInstance;
	}
	string report() override {
		return "is Terminated";
	}


};

//State functions that change state with changeState and a instance of next state

//----New State Functions-------------
void NewP::admitted(Process* p) { 
	
	changeState(p, Ready::instance());
}

//---- Ready Functions------------
void Ready::schedularDispatch(Process* p) {
	changeState(p, Running::instance());
}
//----- Running Functions----------
void Running::interrupt(Process *p) {
	changeState(p, Ready::instance());
}

void Running::ioWait(Process *p) {
	changeState(p, Waiting::instance());
}

void Running::exit(Process* p) {
	changeState(p, Terminated::instance());
}
//------- Waiting Functions-----
void Waiting::ioCompletion(Process* p) {
	changeState(p, Ready::instance());
}


// process contructer that sets default state to New
Process::Process() {
	
	state_ = NewP::instance();
}

// behaviors of process class
void Process::admitted() {   state_->admitted(this); };
void Process::interrupt() { state_->interrupt(this); }
void Process::ioWait() { state_->ioWait(this); }
void Process::ioCompletion() { state_->ioCompletion(this); }
void Process::schedularDispatch() { state_->schedularDispatch(this); }
void Process::exit() { state_->exit(this); }

string Process::report() { return state_->report(); }






#endif

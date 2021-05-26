#include "StatePattern.hpp"


int main() {
	srand(time(NULL));
	deque<Process*> readyQueue, waitingQueue; // ready queue and waiting queue
	int runningDec, waitingDec; // ints that decide that action of a running process and a waitng one

	// Process prototype
	Process prototypeProcess;

	// filling the ready queue with 4 processes
	for (int i = 0; i < 4; ++i) {
		readyQueue.push_back(prototypeProcess.clone());
	}
	// setting the ID for each process
	for (int i = 0; i < readyQueue.size(); ++i) {
		readyQueue[i]->setID(i);
	}
	 
	//setting all the processes to ready inside the ready queue
	for (int i = 0; i < readyQueue.size(); ++i) {
		cout << "Process " << readyQueue[i]->returnID() <<" " << readyQueue[i]->report() << endl;
		readyQueue[i]->admitted();
		cout << "Process " << readyQueue[i]->returnID() << " " << readyQueue[i]->report() << endl;
	
	}

	cout << endl;
		// runs if at least of the queues are not empty
	while (!readyQueue.empty() || !waitingQueue.empty()) {
		runningDec = (rand() % 3) + 1;
		waitingDec = (rand() % 2) + 1;

		if (readyQueue.size()!= 0) { // as long as the ready queue is not empty
			readyQueue.front()->schedularDispatch();  // calls schedualar dispatch to set head of queue is running
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl; // process status
			//cout << "---This Is Running-------" << endl;

		//	cout << "Ready Queue Size: " << readyQueue.size() << endl;
			//cout << "Waiting Queue Size: " << waitingQueue.size() << endl <<endl;
		}
		

		if (runningDec == 1 && readyQueue.size() != 0 ) { // if runningDec is 1 process is terminated
			
			readyQueue.front()->exit(); // sets head of ready queue to terminated state
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl; // process status
			readyQueue.pop_front(); //deletes the head of the ready queue
			

			//cout << "Ready Queue Size: " << readyQueue.size() << endl;
			//cout << "Waiting Queue Size: " << waitingQueue.size() << endl << endl;;
		}
		if (runningDec == 2 && readyQueue.size() != 0) {  // if runningDec is 2 process is interrupted
			readyQueue.front()->interrupt(); // uses interrput to make process ready again
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl; // process status
			readyQueue.push_back(readyQueue.front()); // puts process in the back of the ready queue
			readyQueue.pop_front(); // removes the duplicate of the process that is in the front

			//cout<< "Ready Queue Size: "<< readyQueue.size() << endl;
			//cout << "Waiting Queue Size: " << waitingQueue.size() << endl<<endl;
		}
		if (runningDec == 3 && readyQueue.size() != 0) { // if 3 process goes to waiting
			readyQueue.front()->ioWait(); // uses ioWait to put the process in waiting
			cout << "Process " << readyQueue.front()->returnID() << " " << readyQueue.front()->report() << endl; // process status
			waitingQueue.push_front(readyQueue.front());  // puts the head of the back waiting queue  
			readyQueue.pop_front(); // removes the copy

			//cout << "Ready Queue Size: " << readyQueue.size() << endl;
			//cout << "Waiting Queue Size: " << waitingQueue.size() << endl << endl;
		}
		
		
		if (waitingDec == 1 && waitingQueue.size() != 0) { // waitingDec is 1
			waitingQueue.back()->ioCompletion(); // uses ioCompletion to make the process ready again
			//cout << "------------This Is Waitng" << endl;
			cout << "Process " << waitingQueue.back()->returnID() << " " << waitingQueue.back()->report() << endl; // process status
			readyQueue.push_back(waitingQueue.back()); // puts the tail of the waiting queue inside the ready queue
			waitingQueue.pop_back(); // removes the copy
		
		}

	
	
	
	}
	

}

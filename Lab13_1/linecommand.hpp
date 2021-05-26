#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <deque>

#ifndef LINECOMMAND_H_
#define LINECOMMAND_H_

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;
using std::deque;


// originator
class Document {
public:
    Document(vector <string> lines = {}) : lines_(lines) {}

    void insert(int line, const string& str) {
        int index = line - 1;
        if (index <= lines_.size() + 1) {
            lines_.insert(lines_.begin() + index, str);
        }
        else {
            cout << "line out of range" << endl;
        }
    }

    string remove(int line) {
        const int index = line - 1;
        string deletedLine = "";
        if (index < lines_.size()) {
            deletedLine = lines_[index];
            lines_.erase(lines_.begin() + index);
        }
        else
            cout << "line out of range" << endl;
        return deletedLine;
    }

    void show() {
        for (int i = 0; i < lines_.size(); ++i)
            cout << i + 1 << ". " << lines_[i] << endl;
    }


   // class Memento* createMemento() const;
    //void rollBack(class Memento*);

private:
    vector<string> lines_;
};



//static int commandLine = 1 ;
// abstract command
class Command {
public:
    Command(Document* doc) : doc_(doc) {}
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual void showHistory() = 0;
    virtual void setID(int) = 0; // sets command id
    virtual int getID() = 0; // gets command id
   
    virtual char getType() = 0; // gets command type
    virtual int getLine() = 0; // gets line
    virtual string getString() = 0; //gets string that was inserted
    virtual ~Command() {}
protected:
    Document* doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
    InsertCommand(Document* doc, int line, const string& str) :
        Command(doc), line_(line), str_(str) {}
    void execute() override { doc_->insert(line_, str_); }
    void unexecute() override { doc_->remove(line_);  }
    void showHistory() override { cout << id_ << ". Inserted Line " << line_ << endl; }
    void setID(int i) override{ id_ = i; }
   
    //get commands
    int getID()override { return id_; }
    char getType() override { return type_; }
    int getLine() override { return line_; }
    string getString() override{ return str_; }
    
private:
    int line_;
    string str_;
    int id_ = 0; // history id
    char type_ = 'i'; // insert command type
};

class EraseCommand : public Command {
public:
    EraseCommand(Document* doc, int line) :
        Command(doc), line_(line), str_("") {}
    void execute() override { str_ = doc_->remove(line_);}
    void unexecute() override { doc_->insert(line_, str_); }
    void showHistory() override { cout << id_ << ". Erased Line " << line_ << endl;}
    void setID(int i) override { id_ = i; }
    
    //get commands
    int getID()override { return id_; }  
    char getType() override { return type_; }
    int getLine() override { return line_; }
    string getString() override{ return str_; }
    
private:
    int line_;
    string str_;
    int id_ = 0; // history id
    char type_ = 'e'; // command type
};
static int commandLine;
// client
class DocumentWithHistory {
public:
    DocumentWithHistory(const vector<string>& text = {}) : doc_(text) {}

    void insert(int line, string str) {
        Command* com = new InsertCommand(&doc_, line, str);
        com->execute();
        doneCommands_.push(com);
        
      //  com->setID(commandLine);//-----------------------
        //++commandLine;
        deque<Command*> organizer; // deque used to set the id of all the commands
        //std::stack<Command*>tmp = doneCommands;//-------------------------
        int i = 1;
        while (!doneCommands_.empty()) {
            organizer.push_front(doneCommands_.top()); // puts the top command inside the front of the deque
            doneCommands_.pop();
        }
        for (auto c : organizer) { // range based for organizer

            c->setID(organizer.size() - (organizer.size() - i)); // sets the id of the commands
            ++i;
        }

        this->purgeCommands(); // erases all the commands
        while (!organizer.empty()) {
            doneCommands_.push(organizer.back()); // puts the commands back into doneCommands_ with ID
            organizer.pop_back();
        }
    //---------------------------------------------------------
    }

    void erase(int line) {
        Command* com = new EraseCommand(&doc_, line);
        com->execute();
        doneCommands_.push(com);
        deque<Command*> organizer; // deque used to set the id of all the commands
        //std::stack<Command*>tmp = doneCommands;//-------------------------
        int i = 1;
        while (!doneCommands_.empty()) {
            organizer.push_front(doneCommands_.top()); // puts the top command inside the front of the deque
            doneCommands_.pop(); 
        }
        for (auto c : organizer) { // range based for organizer

            c->setID(organizer.size() - (organizer.size() - i)); // sets the id of the commands
            ++i;
        }

        this->purgeCommands();  // erases all the commands
        while (!organizer.empty()) {
            doneCommands_.push(organizer.back()); // puts the commands back into doneCommands_ with ID
            organizer.pop_back();
        }
    }
    void redo(int id) {//------------------redo------------------------
        std::stack<Command*>tmp = doneCommands_; // tmp that is equal to doneCommands
        Command* redo;
        while (!tmp.empty()) {
            if (tmp.top()->getID() == id) { // finds the command with the command that needs to be redone
                if (tmp.top()->getType() == 'e') { // if type is an erase type
                    redo = new EraseCommand(&doc_, tmp.top()->getLine()); // redo is a erase command with the same constructor values
                }
                else { // if it is an erase typep
                    redo = new InsertCommand(&doc_, tmp.top()->getLine(), tmp.top()->getString()); // redo is a insert command with the same constructor values
                }
                
               
                doneCommands_.push(redo);
                redo->execute();
                //tmp.pop();
                break;
            }
            tmp.pop();
        }

        deque<Command*> organizer; // deque used to set the ids
       
        int i = 1;
        while (!doneCommands_.empty()) {
            organizer.push_front(doneCommands_.top()); // puts the top of doneCommands_ into the front of organizer
            doneCommands_.pop();
        }
        for (auto c : organizer) {

            c->setID(organizer.size() - (organizer.size() - i)); // sets ID of the commands
            ++i;
        }

        this->purgeCommands(); // erases all the commands
        while (!organizer.empty()) {
            doneCommands_.push(organizer.back()); // puts all the commands into the stack
            organizer.pop_back();
        }
        
    
    }
    void undo() {
        if (doneCommands_.size() != 0) {
            Command* com = doneCommands_.top();
            doneCommands_.pop();
            com->unexecute();
            delete com; // don't forget to delete command
        }
        else
            cout << "no commands to undo" << endl;
    }
    void showCommands() {
        std::stack<Command*> tmp = doneCommands_; // tempary stack used to go through done commands
        while (!tmp.empty()) {
           tmp.top()->showHistory(); // shows history of the done commands
           tmp.pop();
        }
    }
    void purgeCommands() {
        while (!doneCommands_.empty()) {
            doneCommands_.pop(); // erases all the commands
        }
        commandLine = 0;
    }

    void show() { doc_.show(); }

    class Memento* createMemento() const; //-----------------------
    void rollBack(class Memento*);

private:
    Document doc_;
    std::stack<Command*> doneCommands_;
};
//-----------------addapting memento with document with history-----------------------------

class Memento {
public:
    Memento(const DocumentWithHistory& doc) : doc_(doc) {}
    const DocumentWithHistory& getState() const { return doc_; }
private:
    const DocumentWithHistory doc_;
};
Memento* DocumentWithHistory::createMemento() const {
    // copying the Document itself
    return new Memento(*this);
}

void DocumentWithHistory::rollBack(Memento* mem) {
    *this = mem->getState();  // copying back
}





#endif

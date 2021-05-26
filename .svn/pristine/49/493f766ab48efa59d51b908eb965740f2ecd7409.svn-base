#include"linecommand.hpp"



int main() {
    DocumentWithHistory doc({
      "Lorem Ipsum is simply dummy text of the printing and typesetting",
      "industry. Lorem Ipsum has been the industry's standard dummy text",
      "ever since the 1500s, when an unknown printer took a galley of",
      "type and scrambled it to make a type specimen book. It has",
      "survived five centuries." });


    char option;
    int redoOption;
    Memento* checkpoint = nullptr;
    do {
        doc.show();
        cout << endl;

        cout << "Enter option (i)nsert line (e)rase line (u)undo last command (c)heckpoint roll(b)ack (h)history(r)edo command : ";
        cin >> option;

        int line; string str;
        switch (option) {
        case 'i': // used to insert
            cout << "line number to insert: ";
            cin >> line;
            cout << "line to insert: ";
            cin.get(); // removes end-of-line character so getline() works correctly
            getline(cin, str);
            doc.insert(line, str);
            break;

        case 'e': // used to erase
            cout << "line number to remove: ";
            cin >> line;
            doc.erase(line);
            break;

        case 'u': // used tp undo
            doc.undo();
            break;
        
        case 'c': // used to create a checkpoint
            checkpoint = doc.createMemento();
            doc.purgeCommands();// erases all the commands once a checkpoint is made
            break;
        case 'b': // used to rollback
            if (checkpoint != nullptr) {
                doc.rollBack(checkpoint);
                delete checkpoint; checkpoint = nullptr;
            }
            break;
        case 'h': // used to show the history
           
            doc.showCommands();
            cout << endl;
            break;

        case 'r': // used to redo a command
            cout << "enter command number:";
            cin >> redoOption;
            doc.redo(redoOption);
            break;
        }
      




    } while (option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'r' || option == 'h' || option == 'b');

}

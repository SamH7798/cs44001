#include"observerregistry.hpp"

int main() {
    Observer olaf("Observer Olaf"), olga("Observer Olga");
    Subject  sue("Subject Sue"), steve("Subject Steve");

    olaf.subscribe(sue.getName()); olaf.subscribe(steve.getName()); // can now subscribe with the name of the subject
    olga.subscribe(sue.getName());

    cout << endl;

    sue.generateMessage();
    steve.generateMessage();

    cout << endl;
    olga.unsubscribe(sue.getName()); // can now  unsubscribe with the name of the subject
    sue.generateMessage();
}

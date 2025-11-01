#include <QCoreApplication>

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Stack.h"
#include "OpType.h"
#include <stdexcept>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::out_of_range;
using namespace std::chrono_literals;
using std::this_thread::sleep_for;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LinkedList<string> document;
    Stack<Operation> undoStack, redoStack;

    int option = 0;
    int pos = 0;
    string word = "";

    do{

        cout << "\n === Mini Editor Text === \n" <<endl;
        cout << "1. Insert a word" <<endl;
        cout << "2. Delete a word" <<endl;
        cout << "3. Replace a word" <<endl;
        cout << "4. Show document" <<endl;
        cout << "5. Undo an action" <<endl;
        cout << "6. Reundo an action" <<endl;
        cout << "7. Exit" <<endl;

        cout << "\n| Choose an option: ";
        cin >> option;

        switch(option){
        case 1:
            cout << "\n === Insert a Word === \n" <<endl;
            cout << "| Set the position: ";
            cin >> pos;
            cout << "\n| Write the word: ";
            cin >> word;
            document.insert(pos, word);
            undoStack.push({OpType::Insert, pos, "", word});
            redoStack.clear();
            break;
        case 2:
            cout << "\n === Delete a Word === \n" <<endl;
            cout << "| Set the position: ";
            cin >> pos;
            try{
                string oldValue = document.at(pos);
                document.erase(pos);
                undoStack.push({OpType::Delete, pos, oldValue, ""});
                redoStack.clear();
            }catch(out_of_range e){
                cout << e.what() << endl;
            }
            break;
        case 3:
            cout << "\n === Replace a Word === \n" <<endl;
            cout << "| Set the position: ";
            cin >> pos;
            cout << "\n| Write the word: ";
            cin >> word;
            try {
                string oldValue = document.at(pos);
                document.replace(pos, word);
                undoStack.push({ OpType::Replace, pos, oldValue, word });
                redoStack.clear();
            } catch (out_of_range e) {
                cout << e.what() << endl;
            }
            break;
        case 4:
            cout << "\n === Document === \n" <<endl;
            document.print();
            break;
        case 5: {
            cout << "\n === Undo Tool ===" <<endl;

            if (undoStack.empty()) {
                cout << "\n| Nothing to undo!" <<endl;
                break;
            }

            Operation op = undoStack.top();
            undoStack.pop();

            if (op.type == OpType::Insert) {
                document.erase(op.pos);
                redoStack.push({ OpType::Insert, op.pos, "", op.newValue });
            }
            else if (op.type == OpType::Delete) {
                document.insert(op.pos, op.oldValue);
                redoStack.push({ OpType::Delete, op.pos, op.oldValue, "" });
            }
            else if (op.type == OpType::Replace) {
                document.replace(op.pos, op.oldValue);
                redoStack.push({ OpType::Replace, op.pos, op.oldValue, op.newValue });
            }

            cout << "\n| Undo action executed!" <<endl;
            break;
        }
        case 6: {
            cout << "\n === Redo Tool ===" << endl;

            if (redoStack.empty()) {
                cout << "\n| Nothing to redo!" << endl;
                break;
            }

            Operation op = redoStack.top();
            redoStack.pop();

            if (op.pos < 0 || op.pos > document.size()) {
                cout << "\n| Cannot redo: Invalid position [" << op.pos << "]!" << endl;
                break;
            }

            try {
                if (op.type == OpType::Insert) {
                    document.insert(op.pos, op.newValue);
                    undoStack.push({ OpType::Insert, op.pos, "", op.newValue });
                } else if (op.type == OpType::Delete) {
                    if (document.size() == 0) {
                        cout << "\n| Nothing to delete during redo!" << endl;
                        break;
                    }
                    document.erase(op.pos);
                    undoStack.push({ OpType::Delete, op.pos, op.oldValue, "" });
                } else if (op.type == OpType::Replace) {
                    document.replace(op.pos, op.newValue);
                    undoStack.push({ OpType::Replace, op.pos, op.oldValue, op.newValue });
                }
            } catch (out_of_range& e) {
                cout << e.what() << endl;
            }

            cout << "\n| Redo action executed!" << endl;
            break;
        }
        case 7:
            cout << "\n| Clearing all the data";

            for (int i = 0; i < 3; ++i) {
                cout << "." << std::flush;
                sleep_for(1000ms);
            }

            document.clear();
            undoStack.clear();
            redoStack.clear();
            cout << "\n| Data has been successfully cleared!" <<endl;
            cout << "\n| Have a great day!" <<endl;
            break;
        default:
            cout << "\n| This option doesnt exists!" <<endl;
            break;
        }


    }while(option != 7);

    return a.exec();
}

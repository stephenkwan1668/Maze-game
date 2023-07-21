#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
//http://www.cplusplus.com/reference/cctype/isdigit/
//https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
///(1) int > (2)string(check) > (3)new int
////(1)convert input from int to string(int > string)
// OR instead of (1), cin directly
////(2)loop throughtout the string : 4bb
////(2)isidigit > store digit of every iteration/index[i]
////(3)if it is digit  string stream  ( string convert to int)
////stringstream  >>  if stringstream(name) >> int temp variable
////use endl before print
////
using namespace std;
class Stack {
public:
    bool isEmpty() {
        // returns true if stack has no elements stored
        if(elements.size() == 0) {
            return true;
        }
        return false;
    }
    int top() {
        // returns element from top of the stack
        // throws runtime_error("stack is empty")
        int lastElement;
        if(!isEmpty()) {
            lastElement =  elements.at(elements.size() - 1);
        }
        else {
            return 0;
        }
        return lastElement;
    }
    int pop() {
        // returns element from top of the stack and removes it
        // throws runtime_error("stack is empty")
        if(!isEmpty()){
            int lastIndexValue;
            lastIndexValue = elements.at(elements.size() - 1);
            elements.erase(elements.begin() + elements.size() - 1);
            return lastIndexValue;
        }
        else{
            throw runtime_error("error: stack is empty\n");
        }
    }
    void push(int valueInput) {
        // puts a new element on top of the stack
        elements.push_back(valueInput);
    }
private:
    vector<int> elements;
};
void printStack(Stack stack) {
    if (!stack.isEmpty()) {
        cout << "[" << stack.top();
        stack.pop();
        while (!stack.isEmpty()) {
            cout << "," << stack.top();
            stack.pop();
        }
        cout << "]" << endl;
    }
    else{
        cout << "[]" << endl;
    }
}
void pushCheck(string& functionCalling, Stack& stack, string& inputNumber) {
    char space = ' ';
    string input;
    int notSpace = -1;
    int numberToPush;

    for (int i = 0; i < inputNumber.size(); ++i) {
        if(inputNumber.at(i) != ' ')
        {
            notSpace = i;
            break;
        }
    }
    if(notSpace < 0)
    {
        throw runtime_error("error: not a number\n");
    }
    input = inputNumber.substr(notSpace, inputNumber.size());

    if (isdigit(input.at(0))) {
        stringstream(input) >> numberToPush;
        stack.push(numberToPush);
    } else {
        throw runtime_error("error: not a number\n");
    }
}
void inputUtil(Stack &stack) {
    string functionCalling;
    try {
        while (!(functionCalling == "end")) {
            cout << "stack>\n";
            string inputNumber;
            cin >> functionCalling;

            if (functionCalling.compare("end") == 0 || cin.eof()) {
                break;
            }

            if (functionCalling.compare("push") == 0) {
                getline(cin, inputNumber);
                pushCheck(functionCalling, stack, inputNumber);

            } else if (functionCalling.compare("list") == 0) {
                printStack(stack);
            } else if (functionCalling.compare("top") == 0) {
                cout << stack.top() << endl;
            } else if (functionCalling.compare("pop") == 0) {
                cout << stack.pop() << endl;
            } else {
                throw runtime_error("error: invalid command\n");
            }
        }
    }



    catch (runtime_error &excpt) {
        cout << excpt.what();
        inputUtil(stack);
    }
}


int main() {
    Stack stack;
    inputUtil(stack);
    return 0;
}
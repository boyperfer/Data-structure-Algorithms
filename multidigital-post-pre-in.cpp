// Hoang Nguyen
// TARRANT COUNTY COLLEGE
// COSC 2436-86002
// Program 1
// Written for GCC
#include <ctype.h>

#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

// the function return the precedence of operators
int prec(char c) {
    switch (c) {
        case '^':
            return 100;
        case '/':
        case '*':
            return 10;
        case '-':
        case '+':
            return 1;
        default:
            return 0;
    }
}

// Convert Infix to Postfix
string convertToPostfix(string infix) {
    // declare variables
    stack<char> operatorStack;  // the operator stack
    string postfix;

    for (int i = 0; i < infix.length(); i++) {
        char nextCharacter = infix[i];
        // if the next character is an operand, add it to the postfix
        if (isOperand(nextCharacter)) {
            char afterNextCharacter = infix[i + 1];
            // if the next of nextCharacter is operand, just add nextCharacter
            // to postfix
            if (isOperand(afterNextCharacter)) {
                postfix += nextCharacter;
            }
            // otherwise add a space followed by nextCharacter
            else {
                postfix += nextCharacter;
                postfix += ' ';
            }
        }

        // if the nextCharacter is operators
        else if (prec(nextCharacter)) {
            // while the stack is not empty and the precedence of the
            // nextCharacter is smaller or equal to the precedence of the
            // stack's top entry, pop the top entry to the postfix.
            // Otherwise, push the operator into the stack.
            while (!operatorStack.empty() &&
                   prec(infix[i]) <= prec(operatorStack.top())) {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            operatorStack.push(nextCharacter);
        }

        // if the nextCharacter is ( put it to the stack
        else if (nextCharacter == '(') {
            operatorStack.push('(');
        }

        // if the nextCharacter is ),
        else if (nextCharacter == ')') {
            // do a loop, which pops the top entry to the postfix and add a
            // space, until the stack meets the '(' character
            while (operatorStack.top() != '(') {
                postfix += operatorStack.top();
                postfix += ' ';
                operatorStack.pop();
            }
            // pop the '(' character
            operatorStack.pop();
        }
    }
    // Pop all the rest of the stack's operators to the postfix
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        postfix += ' ';
        operatorStack.pop();
    }
    return postfix;
}

// Convert Postfix to Infix
string convertToInfix(string postfix) {
    stack<string> infix;
    string digits;  // digits to push properly into the infix
    for (int i = 0; postfix[i] != '\0'; i++) {
        char nextCharacter = postfix[i];
        // if the nextCharacter is an operand
        if (isOperand(nextCharacter)) {
            char nextNextCharacter = postfix[i + 1];
            // assign nextCharacter to digits
            digits += nextCharacter;
            // if the next of nextCharacter is a space, push digits to the
            // infix. Otherwise do another loop
            if (nextNextCharacter == ' ') {
                infix.push(digits);
                digits.clear();
            }
        }
        // if the nextCharacter is an operator
        else if (prec(nextCharacter)) {
            // Pop the first top entry to op1
            string op1 = infix.top();
            infix.pop();
            // Pop the second top entry to op2
            string op2 = infix.top();
            infix.pop();
            // Put the operator between op2 and op1, and push the result to the
            // infix
            infix.push(op2 + postfix[i] + op1);
        }
    }
    return infix.top();
}

int main() {
    string input;
    cout << "what express to convert (infix or postfix or quit): ";
    getline(cin, input);

    // loop until input met quit
    while (input != "quit") {
        if (input == "infix") {
            string postfix;
            cout << "Enter the postfix expression: " << endl;
            getline(cin, postfix);
            cout << "Infix expression: " << convertToInfix(postfix) << endl;
        } else if (input == "postfix") {
            string infix;
            cout << "Enter the infix expression: " << endl;
            getline(cin, infix);
            cout << "Postfix expression: " << convertToPostfix(infix) << endl;
        } else {
            // if the input is different than infix or postfix or quit, loop
            // again.
            cout << "what express to convert (infix or postfix or quit): ";
            getline(cin, input);
        }
        cout << "what express to convert (infix or postfix or quit): ";
        getline(cin, input);
    }

    return 0;
}

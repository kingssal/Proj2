#include "inf_int.h"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    string input;
    inf_int num1, num2, result;
    char op;

    while (true) {
        cout << "Input: ";
        getline(cin, input);

        if (input == "0") {
            break;
        }

        stringstream ss(input);
        ss >> num1 >> op >> num2;

        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            default:
                cout << "Invalid operator!" << endl;
                continue;
        }

        cout << "Result: " << result << endl;
    }

    return 0;
}

#include <iostream>
using namespace std;

// function declaration
bool accept();
bool accept2();
bool accept3();

int main()
{
	int q;

	if (accept())
	{
		cout << "Success\n";
	}
	if (accept2())
	{
		cout << "Success\n";
	}
	else
	{
		cout << "Failed\n";
	}
	if (accept3())
	{
		cout << "Success\n";
	}
	else
	{
		cout << "Failed\n";
	}

	cin >> q; //just to stop at the command window
}

bool accept()
{
	cout << "Do you want to proceed (y or n)?\n"; // write question, The \n character at the end of the output string represents a newline
	char answer = 0;
	cin >> answer; // read answer >> operator (‘‘get from’’)
	if (answer == 'y') return true;
	return false;
}

bool accept2()
{
	cout << "Do you want to proceed (y or n)?\n"; // write question
	char answer = 0;
	cin >> answer; // read answer
	switch (answer) { // A switch-statement tests a value against a set of constants
	case 'y': //The case constants must be distinct
		return true;
	case 'n':
		return false;
	default: // If no default is provided, no action is taken if the value doesn’t match any case constant.
		cout << "I'll take that for a no.\n";
		return false;
	}
}

bool accept3()
{
	int tries = 1;
	while (tries<4) { //The while-statement executes until its condition becomes false.
		cout << "Do you want to proceed (y or n)?\n"; // write question
		char answer = 0;
		cin >> answer; // read answer
		switch (answer) {
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			cout << "Sorry, I don't understand that.\n";
			++tries; // increment
		}
	}
	cout << "I'll take that for a no.\n";
	return false;
}
#include <iostream>
#include <string.h>
#include "biblio.h"

using namespace std;

struct Hash_table
{
	string Key = "";
	string Info = "";
};

Hash_table* Hash;

void Init(int Num) {
	Hash = new Hash_table[Num];
}

int main()
{
	int Num = 0, Choose, position = 0;
	string str1 = "", str2 = "";
	cout << "Enter the maximum number of elements: " << endl;
	cin >> Num;
	while (Num <= 0) {
		cout << "Return enter:\n";
		cin >> Num;
	}
	Init(Num);
	while (1)
	{
		cout << " 1-Insert \n 2-Delete \n 3-Find \n 4-Exit \n ";
		cin >> Choose;
		switch (Choose)
		{
		case 1:
			cout << "Enter key \n";
			cin >> str1;
			cout << "Enter info \n";
			cin >> str2;
			Add(Hash, str1, str2);
			break;
		case 2:
			cout << "Enter key \n";
			cin >> str1;
			Delete(Hash, str1);
			break;
		case 3:
			cout << "Enter key \n";
			cin >> str1;
			View(Hash, str1);
			break;
		case 4:
			exit(true);
			break;
		default:
			cout << "Try again" << endl;
			break;
		}
	}
	return 0;
}


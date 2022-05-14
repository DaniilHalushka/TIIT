#include <iostream>
#include <string>
#include "biblio.h"

using namespace std;
struct Hash_table
{
	string Key = "";
	string Info = "";
};


string Delete(Hash_table* Hash, string key)
{
	int Num;
	Num = Find(Hash, key);
	if (Num != -1)
	{
		Hash[Num].Key = "";
		Hash[Num].Info = "";
	
		cout << "Deleted" << endl;
	}
	else
		cout << "Not find" << endl;
	return Hash[Num].Key;
}

int Find(Hash_table* Hash, string key)
{
	int Num = 0;
	int i = 0;
	while (i < 10000)
	{
		Num = (Function1(key) + i * Function2(key)) % 10;
		if (Hash[Num].Key == key) break;
		else Num = -1;
		i++;
	}
	return Num;
}//поиск по ключу

void View(Hash_table* Hash, string key)
{
	int Num = Find(Hash, key);
	if (Num != -1)
		cout << Hash[Num].Info << endl;
	else
		cout << "Not find" << endl;
}//вывод найденного

string Add(Hash_table* Hash, string key, string info)
{
	int Num = 0;
	int i = 0;
	while (i < 10000)
		{
			Num = (Function1(key) + i * Function2(key)) % 10;
			if (Hash[Num].Key == "")
			{
				Hash[Num].Info = info;
				Hash[Num].Key = key;
				cout << "Added sucsessfully" << endl;
				break;
			}
			i++;
		}
	return Hash[Num].Key;
}

int Function1(string str)
{
	int key = 0;
	for (int i = 0; i < str.length(); i++)
	{
		key += (int)str[i] * (str.length() - i);
	}
	return key;
}//значение строки в хэш

int Function2(string str)
{
	int key = 0;
	for (int i = 0; i < str.length(); i++)
	{
		key += (int)str[i] * 2 / (i+1);
	}
	return key;
}//значение строки в хэш
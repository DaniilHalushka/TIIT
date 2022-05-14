#pragma once
#include <string>

using namespace std;

#ifndef hsh_H
#define hsh_H

struct Hash_table;
void View(Hash_table* Hash, string key);
string Add(Hash_table* Hash,string key, string info);
int Find(Hash_table* Hash, string key);
int Function1(string str);
int Function2(string str);
string Delete(Hash_table* Hash, string str);

#endif
#ifndef SAVEMANAGER_HPP_INCLUDED
#define SAVEMANAGER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> lireSauvegardeScore(string const& path);
vector<int> convertSauvegardeScore(vector<string> scores);
void enregistrerSauvegardeScore(string path, int score);
void tri_bulles(vector<int> &scores);
int str2int (string str);
void resetSauvegardeScore(string path);

#endif // SAVEMANAGER_HPP_INCLUDED

#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

char stringToChar(string str) {
	int g = 0;
	for (int i = 0; i < 8; i++) {
		g += ((int)str[i]-(int)'0') * (int)pow(2, 7 - i);
	}
	return (char)g;
}

vector<char> fromStringToChars(string text, vector<pair<string,string>> vec) {
	vector<char> vecChar = vector<char>();
	string str = "", str2 = "";
	for (int i = 0; i < text.length(); i++) {
		int g = vec.size();
		while (string(1, text[i]+128) != vec[--g].first);
		str += vec[g].second;
		if (str.length() >= 8) {
			str2 = str.substr(0, 8);
			vecChar.push_back(stringToChar(str2));
			str.erase(0, 8);
		}
	}
	return vecChar;
}
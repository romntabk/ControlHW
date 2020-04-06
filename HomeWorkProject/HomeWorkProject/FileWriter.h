#pragma once

#pragma once
#define uchar unsigned char
#include <string>
#include<fstream>

using namespace std;

class FileWriter
{
private:
	ofstream file;
	string fname;
	char *data;
	int size;

public:
	FileWriter(string fname, char *data, int size)
	{
		this->fname = fname;
		this->data = data;
		this->size = size;
	}
	FileWriter(string fname, vector<char> data, int size) {
		this->fname = fname;
		this->size = size;
		char* chars = new char[size];
		for (int i = 0; i < size; i++) {
			chars[i] = data[i];
		}
		this->data = chars;
	}
	void Write()
	{
		file = ofstream(fname, ios::binary);
		file.write(data, size);

		file.close();
	}
};
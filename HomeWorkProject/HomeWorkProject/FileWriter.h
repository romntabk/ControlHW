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

	void Write()
	{
		file = ofstream(fname, ios::binary);
		file.write(data, size);

		file.close();
	}
};
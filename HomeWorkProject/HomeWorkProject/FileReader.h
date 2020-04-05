#pragma once
#define uchar unsigned char
#include <string>
#include<fstream>

using namespace std;

class FileReader
{
private:
	char *data;	
	int size;
	ifstream file;
	string fname;

public:
	FileReader(string fname)
	{
		this->fname = fname;
		
		streampos begin, end;
		
		file = ifstream(fname, ios::binary);
		
		file.seekg(0, file.end);
		size = file.tellg();
		file.seekg(0, file.beg);

		data = new char[size];
		file.read(data, size);
	}

	char* getData()
	{
		return data;
	}

	int getSize()
	{
		return size;
	}

	string getName()
	{
		return fname;
	}
};
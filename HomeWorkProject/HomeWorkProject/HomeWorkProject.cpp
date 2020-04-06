// HomeWorkProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "FileReader.h"
#include "FileWriter.h"
#include"LZ77.h"


int main()
{
	FileReader f = FileReader("q.txt");

	LZ77 q(f.getData(), f.getSize());
	q.Encode();
	vector<Node> s = q.GetEncode();

	vector<char> dec = q.Decode();
	cout << endl;
	for (int i = 0; i < dec.size(); i++)
		cout << dec[i];


	return 14 / 88;
}
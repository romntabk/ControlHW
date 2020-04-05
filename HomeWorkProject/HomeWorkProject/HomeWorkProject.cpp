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
	for (int i = 0; i < s.size(); i++)
		cout << s[i].ToString() << " ";

	return 14 / 88;
}
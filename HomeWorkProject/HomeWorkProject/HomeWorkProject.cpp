// HomeWorkProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "FileReader.h"
#include "FileWriter.h"
#include"LZ77.h"
#include<string>

int main()
{
	FileReader f = FileReader("q.txt");

	LZ77 q(f.getData(), f.getSize());
	q.Encode();
	
	char *w = q.EncodeBytes();
	int wsize = q.GetSizeBytes();
	
	q.SetCode(q.DecodeBytes(w, wsize));
	vector<char> a = q.Decode();

	FileWriter writer("q_encode.txt", w, wsize);
	
	std::cout << "DECODED";
	std::cout << std::endl << std::endl;
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i];

	return 14 / 88;
}
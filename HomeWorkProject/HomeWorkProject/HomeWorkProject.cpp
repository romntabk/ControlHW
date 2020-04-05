
#include <iostream>
#include "Huffman.h"
#include "FileReader.h"
#include "FromStringToChar.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	FileReader fileReader = FileReader("input.txt");
	cout << string(fileReader.getData(),fileReader.getSize());
	vector<pair<string, string>> vecs = HuffCoding(fileReader.getData(),fileReader.getSize());
	vector<char> chars = fromStringToChars(string(fileReader.getData(), fileReader.getSize()), vecs);
	for (int i = 0; i < chars.size(); i++) {
		cout << (int)chars[i] << " ";
	}
}

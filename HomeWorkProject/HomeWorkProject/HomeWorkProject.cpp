
#include <iostream>
#include "Huffman.h"
#include "FileReader.h"
#include "FromStringToChar.h"
#include "FileWriter.h"
int main()
{
	setlocale(LC_ALL, "Russian");
	FileReader fileReader = FileReader("input.txt");
	//cout << string(fileReader.getData(),fileReader.getSize());
	vector<pair<string, string>> vecs = HuffCoding(fileReader.getData(),fileReader.getSize());
	vector<char> chars = fromStringToChars(string(fileReader.getData(), fileReader.getSize()), vecs);
	for (int i = 0; i < chars.size(); i++) {
		cout << (int)chars[i] << " ";
	}
	cout << fileReader.getData();
	FileWriter fw = FileWriter("output.txt", chars, chars.size());
	fw.Write();
	FileReader decode = FileReader("output.txt");
	vector<char> chacha = HuffDecoding(decode.getData(), decode.getSize(), vecs);
	FileWriter fwDecode = FileWriter("opaopa.txt", chacha, chacha.size());
	fwDecode.Write();
}

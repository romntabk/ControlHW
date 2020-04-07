#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
#include "FileReader.h"
#include "FileWriter.h"

using namespace std;

class Node
{

public:
	unsigned int offset;
	unsigned int length;
	char next;

	Node(int a, int b, char c)
	{
		offset = a;
		length = b;
		next = c;
	}

	Node() { offset = length = 0;
	next = 0; }

	string ToString()
	{
		return "(" + to_string(offset) + ", " + to_string(length) + ", " + next + ")";
	}

	Node(char a[sizeof(9)])
	{

	}
};
union converter
{
	unsigned int s;
	char byte[sizeof(int)];
	converter() {}
	converter(char b[sizeof(int)]) { for (int j = 0; j < sizeof(int); j++) byte[j] = b[j]; }
};
class LZ77
{
private:
	char *data;
	int size;
	vector<Node> encode = vector<Node>();

	int buff_pos = 0;
	int buff_size = 0;

	const int MAX_BUFF_SIZE = 5;

	int bytes_size;

	int pos = 0;

	void Encode()
	{
		while (buff_pos + buff_size < size)
		{
			Node match = FindMatche(pos, buff_pos);


			cout << match.ToString() << endl;
			encode.push_back(match);
		}
	}

	Node FindMatche(int pos, int &buff_pos)
	{
		// 1 find all matches
		vector<int> matches = vector<int>();

		/*if (buff_pos != 0)
			buff_pos -= 1;*/

		int first_char = buff_size + buff_pos;

		if (buff_size == 0)
		{
			buff_size++;
			return Node(0, 0, data[0]);
		}

		for (int i = buff_pos; i < buff_pos + buff_size; i++)
		{
			if (data[i] == data[first_char])
				matches.push_back(i);
		}

		Node max;

		for (int c = 0; c < matches.size(); c++)
		{
			Node match;

			int i = matches[c];
			int step = 0;
			//     IN BUFF						 IN DATA
			//while (data[i - step % buff_size] == data[i + buff_size - (matches[c] - buff_pos)])
			while (data[i - step * buff_size] == data[i + buff_size - (matches[c] - buff_pos)])
			{
				match.length += 1;
				i++;
				if (i - step * buff_size - buff_pos >= buff_size)
					step += 1;
			}
			match.offset = buff_size - (matches[c] - buff_pos);

			match.next = data[buff_pos + buff_size + match.length];

			if (buff_pos + buff_size + match.length >= size)
			{
				buff_pos = buff_pos + match.length;
				match.next = '\0';
				return match;
			}
			if (max.length <= match.length)
				max = match;
		}

		if (buff_size >= MAX_BUFF_SIZE)
		{
			buff_pos += max.length + 1;
		}

		if (buff_size < MAX_BUFF_SIZE)
		{
			buff_size += max.length + 1;
			if (buff_size > MAX_BUFF_SIZE)
			{
				buff_size = MAX_BUFF_SIZE;
				//buff_pos += buff_size;
				buff_pos += (max.length + 1) - (MAX_BUFF_SIZE - (max.length + 1)) - 1;
				//buff_pos -= 1;
			}
		}

		if (max.length == 0)
			return Node(0, 0, data[buff_pos + buff_size - 1]);
		return max;
	}

	vector<Node>  GetEncode()
	{
		return encode;
	}

	char* EncodeBytes()
	{
		bytes_size = (sizeof(int) * 2 + sizeof(char))* encode.size();
		char *p = new char[bytes_size];

		converter con;

		int c = 0;
		for (int i = 0; i < encode.size(); i++)
		{
			con.s = encode[i].offset;
			for (int w = 0; w < sizeof(int); w++)
			{
				p[c++] = con.byte[w];
			}
			con.s = encode[i].length;
			for (int w = 0; w < sizeof(int); w++)
			{
				p[c++] = con.byte[w];
			}
			p[c++] = encode[i].next;
		}
		return p;
	}

	vector<Node> DecodeBytes(char *q, int size)
	{
		vector<Node> code = vector<Node>();
		converter con;
		int qi = 0;
		for (int i = 0; i < bytes_size / (sizeof(int) * 2 + sizeof(char)); i++)
		{
			Node tmp = Node();
			char b[sizeof(int)];

			for (int c = 0; c < sizeof(int); c++)
				b[c] = q[qi++];
			con = converter(b);
			tmp.offset = con.s;

			for (int c = 0; c < sizeof(int); c++)
				b[c] = q[qi++];
			con = converter(b);
			tmp.length = con.s;

			tmp.next = q[qi++];
			
			code.push_back(tmp);
		}

		return code;


	}

	int GetEncodeSize()
	{
		return encode.size();
	}

	vector<char> Decode()
	{
		vector<char> decode = vector<char>();
		int q = 0;
		for (int i = 0; i < encode.size(); i++)
		{
			if (encode[i].length > 0)
			{
				int start = decode.size() - encode[i].offset;
				for (int c = 0; c < encode[i].length; c++)
				{
					decode.push_back(decode[start + c]);
				}
			}
			decode.push_back(encode[i].next);
		}
		if (decode[decode.size() - 1] == '\0')
			decode.pop_back();
		return decode;
	}

	void SetCode(vector<Node> q)
	{
		encode = q;
	}

	int GetSizeBytes()
	{
		return bytes_size;
	}	  
public:
	LZ77()
	{

	}
	LZ77(char *data, int size)
	{
		this->data = data;
		this->size = size;
	}

	LZ77(string start)
	{
		EncodeFile(start);
		DecodeFile(start + "_encoded");
	}
	void EncodeFile(string name)
	{
		// open
		FileReader reader = FileReader(name);
		// read
		data = reader.getData();
		size = reader.getSize();
		// encode
		Encode();
		// node->char*
		char *encoded_data = EncodeBytes();
		// bytes_size - size here

		// write 
		FileWriter writer = FileWriter(name + "_encoded", encoded_data, bytes_size);
		writer.Write();

		delete[] encoded_data;
	}

	void DecodeFile(string name)
	{
		// open
		FileReader reader = FileReader(name);
		// read
		data = reader.getData();
		size = reader.getSize();
		// decode
		encode = DecodeBytes(data, size);
		// vector<char> to char*
		vector<char> decoded_dataVec = Decode();
		char *decoded = new char[sizeof(char) * decoded_dataVec.size()];
		for (int i = 0; i < decoded_dataVec.size(); i++)
			decoded[i] = decoded_dataVec[i];
		// write
		FileWriter writer = FileWriter(name + "_decoded", decoded, decoded_dataVec.size());
		writer.Write();

		delete[] decoded;
		delete[] data;

	}
};

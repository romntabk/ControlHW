#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>


using namespace std;

class Node
{

public:
	int offset = 0;
	int length = 0;
	char next = 0;

	Node(int a, int b, char c)
	{
		offset = a;
		length = b;
		next = c;
	}

	Node() {}

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
	int s;
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
public:
	LZ77()
	{

	}
	LZ77(char *data, int size)
	{
		this->data = data;
		this->size = size;
	}

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
			while (data[i - step *  buff_size] == data[i + buff_size - (matches[c] - buff_pos)])
			{
				match.length += 1;
				i++;
				if (i - step * buff_size >= buff_size)
					step += 1;
			}
			match.offset = buff_size - (matches[c] - buff_pos);

			match.next = data[buff_pos + buff_size + match.length];

			if (buff_pos + buff_size + match.length >= size)
			{
				buff_pos = buff_pos + match.length;
				match.next = -1;
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
				buff_pos += (max.length);
				buff_size = MAX_BUFF_SIZE;
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
		bytes_size = sizeof(Node) * encode.size();
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
		for (int i = 0; i < size / 9; i++)
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
			// out
			for (int q = 0; q < decode.size(); q++)
				cout << decode[q];
			cout << "   : " << i;
			cout << endl;
		}
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
};

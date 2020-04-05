#pragma once
#include<vector>
#include<iostream>


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

	Node FindMatche(int pos, int buff_pos)
	{
		// 1 find all matches
		vector<int> matches = vector<int>();
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

		Node match;
		Node max;

		for (int c = 0; c < matches.size(); c++)
		{
			int i = matches[c];
			int step = 0;
			//     IN BUFF						 IN DATA
			while (data[i - step * buff_size] == data[i + buff_size])
			{
				match.length += 1;
				if (i - step * buff_size > buff_size + i)
					step += 1;
				i++;
			}
			match.offset = buff_size - matches[c];

			match.next = data[buff_pos + buff_size + match.length];
			
			if (max.length < match.length)
				max = match;
		}
		
		if (buff_size < MAX_BUFF_SIZE)
			buff_size++;
		if (max.length == 0)
			return Node(0, 0, data[pos + buff_size - 1]);
		return max;
	}

	int pos = 0;
public:

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
			if (buff_size >= MAX_BUFF_SIZE)
				buff_pos += match.length + 1;
			pos += match.length;
			cout << match.ToString() << endl;
			encode.push_back(match);
		}		
	}

	vector<Node>  GetEncode()
	{
		return encode;
	}

	int GetEncodeSize()
	{
		return encode.size();
	}


};

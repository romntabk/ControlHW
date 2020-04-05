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
};

class LZ77
{
private:
	char *data;
	int size;
	vector<Node> encode = vector<Node>();

	int buff_pos = 0;
	int buff_size = 10;

	int pos = 0;
public:

	LZ77(char *data, int size)
	{
		this->data = data;
		this->size = size;
	}

	bool Endode()
	{
		while (pos < size)
		{
			Node match = FindMatche(pos, buff_pos);
			buff_pos += match.length + 1;
			pos += match.length;
			match.next = data[pos];
			encode.push_back(match);
		}
	}

	Node FindMatche(int pos, int buff_pos)
	{
		// 1 find all matches
		vector<int> matches = vector<int>();
		int first_char = pos + 1;
		for (int i = buff_pos; i < buff_pos + buff_size; i++)
		{
			if (data[i] == data[first_char])
				matches.push_back(i);
		}

		vector<Node> node_maches = vector<Node>();

		Node match;
		Node max;
		for (int c = 0; c < matches.size(); c++)
		{
			int i = buff_pos;
			int step = 0;
			//     IN BUFF    IN DATA
			while (data[i - step * buff_size] == data[i + buff_size])
			{
				match.length += 1;
				if (i - step * buff_size > buff_size + i)
					step += 1;
			}
			match.offset = buff_size - matches[c];
			match.next = data[first_char];
			if (max.length < match.length)
				max = match;
		}
	}

};

/*
//  — исходная строка
// функция возвращает список блоков
list<Node> encodeLZ77(string s):
   list<Node> ans = []
   pos = 0
   while pos < s.length:
	   offset, length = findMatching(buffer, pos)   // ищем слово в словаре
	   shiftBuffer(length + 1)                      // перемещаем скользящее окно
	   pos += length
	   ans.push({offset, length, s[pos]})           // добавляем в ответ очередной блок
   return ans

*/
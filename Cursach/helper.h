#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

namespace abs_departmentspace
{


	bool Empty(string s)
	{
		if (s.length() < 1)
			return true;
		return false;
	}

	char to_lower(unsigned char c)
	{
		if (c >= 65 && c <= 90)
			return c + 32;
		if (c >= 192 && c <= 223)
			return c + 32;
		return c;
	}
	string to_lower(string s)
	{
		for (int i = 0; i < s.length(); i++)
			s[i] = to_lower((int)s[i]);
		return s;
	}
	int ReadInt(istream & fin)
	{
		char buffer[31] = "\0";
		if (fin.getline(buffer, 255))
		{
			return atoi(buffer);
		}
		return 1;
	}
	bool ReadBool(istream & fin)
	{
		string s;
		getline(fin, s);
		if (s.length() > 0)
		{
			if (to_lower(s) == "y" || s == "1")
				return true;
		}
		return false;
	}
	string ReadString(istream & fin)
	{
		string s;
		if (getline(fin, s))
		{
			return s;
		}
		return "";
	}
	bool ReadString(istream & fin, string & s)
	{
		getline(fin, s);
		if (s.length() > 0)
			return true;
		return false;
	}

	
	string ReadString(char * text, bool not_null = false)
	{
		string s = "";
		while (true)
		{
			cout << text;
			if (not_null)
				cout << " (не может быть пустым)";
			cout << ":\n";
			getline(cin, s);
			if (!not_null || s.length() != 0) return s;
		}
		return "";
	}
	int ReadInt(char * text, bool not_null = true)
	{
		char buffer[31] = "\0";
		int t = 0;
		while (true)
		{
			cout << text << ":\n";
			cin.getline(buffer, 255);
			t = atoi(buffer);
			if (t > 0) return t;
			if (!not_null) return 0;
		}
		return -1;
	}
	int ReadInt(char * text, int mn, int mx)
	{
		char buffer[31] = "\0";
		int t = 0;
		while (true)
		{
			cout << text << " (>=" << mn << " <=" << mx << ") :\n";
			cin.getline(buffer, 255);
			t = atoi(buffer);
			if (t >= mn && t<= mx) return t;
		}
		return -1;
	}
	bool ReadBool(char * text)
	{
		string s;
		while (true)
		{
			cout << text << ":\n";
			getline(cin, s);
			if (s.length() > 0)
			{
				if (to_lower(s) == "y" || s == "1")
					return true;
				if (to_lower(s) == "n" || s == "0")
					return false;
			}
		}
		return false;
	}

	string cipher(string s) //shifrovanie
	{
		for (int i = 0; i < s.length(); i++)
			s[i] = s[i] ^ 153;
		return s;
	}

	void EditValue(char * text, string & prev)
	{
		char text2[127];
		strcpy(text2, text);
		strcat(text2, " (для пропуска нажмите Enter)");
		string s = ReadString(text2, false);
		if (!Empty(s))prev = s;
	}

	void EditValue(char * text, int & prev)
	{
		char text2[127];
		strcpy(text2, text);
		strcat(text2, " (для пропуска нажмите Enter)");
		int k = ReadInt(text2, false);
		if (k > 0) prev = k;
	}


	string ReadPass(char * text)
	{
		string pass;

		while (true)
		{
			unsigned char c = 0;
			pass = "";

			cout << text << ":\n";
			
			while (true)
			{
				c = _getch();
				if (c == 13 & !pass.empty())
				{
					cout << "\n";

					break;
				}

				if (c == 8)
				{
					if (!pass.empty())
					{
						pass.erase(pass.length() - 1);
						cout << (char)8 << ' ' << char(8);
					}
				}
				else if(c > 31)
				{
					cout << '*';
					pass += (char)c;
				}
			}

			if (pass.length() != 0)
				break;
			
		}

		return pass;
	}


	
}
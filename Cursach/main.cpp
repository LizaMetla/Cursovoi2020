// Cursach.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <map>

#include "fruit_department.h"
#include "milk_department.h"
#include "bread_department.h"
#include "fish_department.h"
#include "vegetables_department.h"
#include "meat_department.h"
#include "access.h"

using namespace std;
using namespace abs_departmentspace;

store * st;

void reset_color() {
	//printf("\x1b[0m");
}
void set_color(string color) {
	printf(color.c_str());
}


namespace abs_departmentspace
{
	map<string, access *> users;
	ostream& operator <<(ostream& fout, access *& u)
	{
		fout << u->GetType() << "\n";
		fout << u->name << "\n";
		fout << cipher(u->pass) << "\n";
		if (u->reciepts.size() > 0) {
			
			for (int i = 0; i < u->reciepts.size(); i++)
			{
				if (u->reciepts[i].size() > 0) {
					fout << "RC" << "\n";
					for (int j = 0; j < u->reciepts[i].size(); j++) {
						u->reciepts[i][j]->Write(fout);
					}
					fout << "\n";
				}

			}
			
		}
		fout << "\n";
		
		
		return fout;
	}

	istream& operator >>(istream& fin, access *& u) //peregruzka operatora >>
	{
		string name, pass, type;
		vector<vector<abs_department *>> reciepts; //vector iz vectora productov
		type = ReadString(fin);
		name = ReadString(fin);
		pass = cipher(ReadString(fin));
		reciepts = store::ReadReciepts(fin);
		if (Empty(type) || Empty(name) || Empty(pass))
			u = NULL;
		else
		{
			if (type == "A")
				u = new admin(st, name, pass, reciepts);
			else if(type == "U") u = new user(st, name, pass, reciepts);
		}
		return fin;
	}
	void PrintUsers()
	{
		ofstream fout("users.in");
		for (map<string, access *>::iterator i = users.begin(); i != users.end(); i++)//iterator
		{
			fout << (*i).second;

		}
		fout.close();
	}
	void ShowUsers()
	{
		for (map<string, access *>::iterator i = users.begin(); i != users.end(); i++)//iterator
		{
			(*i).second->Info();
			cout << "\n";

		}
	}
	void DeleteUsers() {
		map<string, access *> users_temp;
		for (map<string, access *>::iterator i = users.begin(); i != users.end(); i++)//iterator
		{
			(*i).second->Info();
			cout << "\n������� 1, ����� ������� ������������...";
			cout << "\n";
			char c = _getch();
			if (c != '1')
			{

				users_temp.insert(*i);
			}

		}
		cout << "\n �� ������������� ������ ������� �������������...\n";
		if (users.size() != users_temp.size()) {
			cout << "\n������� 1, ����� ����������� �������� �����������e�...\n";
			char c = _getch();
			if (c == '1')
			{
				users = users_temp;
				PrintUsers();
			}
		}
		

	}
	void EditUser() {
		for (map<string, access *>::iterator i = users.begin(); i != users.end(); i++)//iterator
		{
			(*i).second->Info();
			cout << "\n������� 1, ����� �������� ��� ������������ ..." ;
			cout << "\n";
			char c = _getch();
			if (c == '1')
			{
				string new_name = "";
				
				while (true)
				{
					new_name = ReadString("������� ����� ��� ������������: ");
					multimap<string, access *>::iterator i = users.find(new_name);
					if (i != users.end())
					{
						cout << "��� ������������ ��� ������.\n";
						system("pause");
					}
					else {
						break;
					}
				}
				(*i).second->name = new_name;
				cout << "\n������� 1, ����� ���������� �������������� ...";
				cout << "\n";
				char c1 = _getch();
				if (c1 != '1')
				{
					break;

				}
			}
			

		}
		PrintUsers();
	}
}

void InitConsole()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

bool InitStore()
{
	try
	{
		st = new store("items.in");//inizialization object classa STORE	
		return true;
	}
	catch (...)//vse vidi oshiok = orabotchik oshiok
	{
		return false;
	}
}

void AddUser(access * a)
{
	multimap<string, access *>::iterator i = users.find(a->name);
	if (i == users.end())
	{
		users.insert(make_pair(a->name, a));
	}
	users_count = users.size();
}

bool InitUsers()
{
	try
	{
		users = map<string, access *>(); //map vseh userov

		ifstream fin("users.in");
		access * u = NULL; //sozdatel pustogo ukazatelya na class dostupa =polzovatel, admin, gost'
		
		while (true)
		{
			fin >> u;//ukazatel na fail iz FIN berem polzovatelya + s peregruzkoi|>>|
			if (u == NULL)
				break;
			AddUser(u);
		}

		fin.close();

		return true;
	}
	catch (...)
	{
		return false;
	}
}



void Clear()
{
	while (users.size() > 0)
	{
		multimap<string, access *>::iterator i = users.begin();
		access * u = (*i).second;
		users.erase(i);
		delete u;
	}
	users_count = 0;
	if (st) delete st;
}

void Request(access * u)
{
	//u->Info();
	u->Request();
	st->Restore();
}

void Login()
{
	system("cls");
	int count_log = 3;
	int count_pass = 3;
	
	string name, pass;
	cout << "--------------------------------\n";
	cout << "---------���� � �������---------\n";
	cout << "--------------------------------\n";
	while (count_log > 0) {

		name = ReadString(">>������� ��� ������������", false);


		multimap<string, access *>::iterator i = users.find(name);
		if (i != users.end())
		{
			access * u = (*i).second;

			while (count_pass > 0) {
				pass = ReadPass(">>������� ������");


				if (u->Login(pass))
				{
					cout << ">>�� ������� ����������������.\n";
					system("pause");
					Request(u);
					return;
				}
				else {
					count_pass--;
					cout << ">>�������� ������.\n>>��������� ���� ������! \n>>������� ��� ����� ������: " << count_pass << " .\n";
					if (count_pass == 0) {
						return;
					}
				}
			}
		}
		else { 
			count_log--;
			cout << "��� ������������ �� ����������.\n��������� ���� ������!!! \n� ��� �������� "<< count_log << " ������� �� ���� ������.\n"; 
			
		}

		//system("pause");
	}
	
}

void Register(string user_type)
{
	string name, pass;

	int count_log = 3;
	int count_pass = 3;

	cout << "--------------------------------\n";
	cout << "-----------�����������----------\n";
	cout << "--------------------------------\n";

	//while (count_log > 0) {

	
		name = ReadString(">>������� ��� ������������", true);
		//FALSE=TRUE
	
		pass = ReadPass(">>������� ������");
		access * u;
		multimap<string, access *>::iterator i = users.find(name);
		if (i != users.end())
		{
			cout << "��� ������������ ��� ������.";
			system("pause");
		}
		else
		{
			if (user_type == "U") {
				u = new user(st, name, pass, {});
			}
			else {
				u = new admin(st, name, pass, {});
			}
		
			AddUser(u);
			PrintUsers();
			cout << "������� ������.\n";
			system("pause");
			Request(u);
		}
	//}
}

void Show()
{
	access * u = new guest(st);
	Request(u);
}

int view_main_menu() 
{

	char ch = 0;
	char pointer = '>';
	int choice = 0;
	while (1) {
		if (ch != '\n') {
			cls;

			if (ch == 80)//����
				choice++;
			if (ch == 72)//�����
				choice--;
			if (choice > 4)
				choice = 0;
			if (choice < 0)
				choice = 4;
			if (ch == 13)//enter
				return choice;
			printf(" .________________________________________________.\n");
			printf(" |_______������� ����������������� �������________|  \n");
			printf(" |__________________������� ����__________________|  \n");
			if (choice == 0) {
				//set_color("\x1b[38;5;15m]");
				printf(" |       %c ����� � ��� ������������ �������.      |\n", pointer);
				reset_color();
			}
			else
				printf(" |         ����� � ��� ������������ �������.      |\n");
			if (choice == 1) {
				//set_color("\x1b[38;5;15m");
				printf(" |       %c ������� ����� �������.                 |\n", pointer);
				reset_color();
			}

			else
				printf(" |         ������� ����� �������.                 |\n");
			if (choice == 2) {
				//set_color("\x1b[38;5;15m");
				printf(" |       %c ������� ����� ������� ��������������   |\n", pointer);
				reset_color();
			}

			else
				printf(" |         ������� ����� ������� ��������������   |\n");
			if (choice == 3) {
				//set_color("\x1b[38;5;15m");
				printf(" |       %c ����� ��� �����.                       |\n", pointer);
				reset_color();
			}

			else
				printf(" |         ����� ��� �����.                       |\n");
			if (choice == 4) {
				//set_color("\x1b[38;5;15m");
				printf(" |       %c ����� �� ���������.                    |\n", pointer);
				reset_color();
			}

			else
				printf(" |         ����� �� ���������.                    |\n");
		}
		printf(" |________________________________________________|\n");
		printf(" .________________________________________________.\n");

		ch = _getch();
	}
}

int main_menu() 
{
	bool flag = false;
	do
	{
		cls;

		switch (view_main_menu())
		{
			case 0: Login(); break;
			case 1: Register("U"); break;
			case 2: Register("A"); break;
			case 3: Show(); break;
			case 4: Clear(); return 0;
			//case 5: {cls;
			//	printf("�� ��������!\n");
			//	flag = true;
			//	break; }
			default: { cls;
				printf("������ ������ ���� ���!\n");
				pause;
				break;
			}
		}

	} while (!flag);

}

int main()
{
	InitConsole();//kodirovka
	system("color 0B");
	
	//
	if (!InitStore() || st == NULL)
	{
		cout<<"��������� ������ ��� ������������� ��������. ��������� ����� ���������.\n";
		system("pause");
		return -1;
	}
	if (!InitUsers() || st == NULL)
	{
		cout << "��������� ������ ��� ������������� ���������. ��������� ����� ���������.\n";
		system("pause");
		return -1;
	}

	while (true)
	{
		int res;
		res = main_menu();
		if (res == 0)
			return res;
		/*
		system("cls");

		cout << "\n*������� ����������������� �������*\n\n";
		cout << "1 - ����� � ��� ������������ �������.\n";
		cout << "2 - ������� ����� �������.\n";
		cout << "3 - ������� ����� ������� ��������������.\n";
		cout << "4 - ����� ��� �����.\n";
		cout << "0 - ����� �� ���������.\n";
		cout << "�������� ����������� �������.\n";

		string s = "";
		getline(cin, s);
		if (s.length() != 1) continue;
		int c = s[0] - '0';

		switch (c)
		{
			case 1: Login(); break;
			case 2: Register("U"); break;
			case 3: Register("A"); break;
			case 4: Show(); break;
			case 0: Clear(); return 0;
		}
		*/
	}
    return 0;
}


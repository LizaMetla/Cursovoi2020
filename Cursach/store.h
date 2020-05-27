#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#include "helper.h"
#include "fruit_department.h"
#include "milk_department.h"
#include "bread_department.h"
#include "fish_department.h"
#include "vegetables_department.h"
#include "meat_department.h"
#include "abs_department.h"
#include "custom.h"

#define cls system("cls");  // ��� ��������� ���������,������ system("cls"),����� cls;
#define pause system("pause");
#define printf printf_s

using namespace std;

namespace abs_departmentspace
{
	int users_count = 0;

	class store
	{
	public:
		store(string input_path)
		{
			this->input_path = input_path;
			Restore();
		}

		void Add()
		{
			abs_department * h = Readabs_department();
			if (h != NULL)
			{
				t.push_back(h);
				Update();
			}
			system("pause");
		}

		abs_department * Remove(abs_department *& h, int count)
		{
			abs_department * hh = NULL;
			if (h != NULL)
			{
				vector<abs_department *>::iterator i = find(t.begin(), t.end(), h);
				if (i != t.end())
				{
					h->RemoveCount(count, hh);
					if (h->GetCount() <= 0)
					{
						t.erase(i);
					}					
				}
			}
			//Update();
			return hh;
		}
		static abs_department * Readabs_department(istream & fin)
		{
			string type = ReadString(fin);
			if (type == "FT")
			{
				fruit_department * p = new fruit_department();
				p->Read(fin);//chtenie iz faila svoistv productov
				return p;
			}
			if (type == "B")
			{
				bread_department * v = new bread_department();
				v->Read(fin);
				return v;
			}
			if (type == "MT")
			{
				meat_department * s = new meat_department();
				s->Read(fin);
				return s;
			}
			if (type == "MK")
			{
				milk_department * h = new milk_department();
				h->Read(fin);
				return h;
			}
			if (type == "V")
			{
				vegetables_department * r = new vegetables_department();
				r->Read(fin);
				return r;
			}
			if (type == "F")
			{
				fish_department * ff = new fish_department();
				ff->Read(fin);
				return ff;
			}
			if (type == "C")
			{
				custom * c = new custom();
				c->Read(fin);
				return c;
			}
			return NULL;
		}

		static vector<vector<abs_department *>> ReadReciepts(istream & fin) {
			vector<abs_department *> products = {  };
			vector<vector<abs_department *>> reciepts = { };
			abs_department * h;
			string type = ReadString(fin);
			while (true) {
				
				if (type == "RC") {
					while (true)
					{
						h = Readabs_department(fin);
						if (h == NULL)
							break;
						products.push_back(h);

					}
					reciepts.push_back(products);
					products.clear();
					type = ReadString(fin);
				}
				else{
					break;
				}
			}

			return reciepts;
		}
		void Update()
		{
			ofstream fout(input_path);
			for (int i = 0; i < t.size(); i++)
			{
				t[i]->Write(fout);
			}
		}

		void Restore()
		{
			ifstream fin(input_path);
			abs_department * h;//UKAZATEL CLASSA RODITELYA
			t.clear();//VECTOR T cuda zapisivautsya vse producti
			while (true)
			{
				h = Readabs_department(fin);//chtenie po 1 productu s sohraneniem v vector T
				if (h == NULL)
					break;
				t.push_back(h);
			}
		}

		vector<abs_department *> & Print()
		{
			tt.clear();
			for (int i = 0; i < t.size(); i++)
				tt.push_back(t[i]);

			return tt;
		}

		int view_sort_menu()
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
					if (choice > 5)
						choice = 0;
					if (choice < 0)
						choice = 5;
					if (ch == 13)//enter
						return choice;
					printf(" ._______________________________________________________________________.\n");
					printf(" |________________������� ����������������� �������______________________|  \n");
					printf(" |___________________________���� c���������_____________________________|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c ���������� �� �������� ��������.                           |\n", pointer);
						//reset_color();
					}
					else
						printf(" |            ���������� �� �������� ��������.                           |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ���������� �� ����������(�� ������������ �� ������������)  |\n", pointer);
						//reset_color();
					}

					else
						printf(" |            ���������� �� ����������(�� ������������ �� ������������)  |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ���������� �� ����������(�� ������������ �� ������������)  |\n", pointer);
						//reset_color();
					}

					else
						printf(" |            ���������� �� ����������(�� ������������ �� ������������)  |\n");
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ���������� �� ���� (�� ����������� �� �����������).        |\n", pointer);
						//reset_color();
					}

					else
						printf(" |            ���������� �� ���� (�� ����������� �� �����������).        |\n");
					if (choice == 4) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ���������� �� ���� (�� ����������� �� �����������).        |\n", pointer);
						//reset_color();
					}

					else
						printf(" |            ���������� �� ���� (�� ����������� �� �����������).        |\n");
					if (choice == 5) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����� � ������� ����.                                      |\n", pointer);
						//reset_color();
					}

					else
						printf(" |            ����� � ������� ����.                                      |\n");
					

				}
				printf(" |_______________________________________________________________________|\n");
				printf(" ._______________________________________________________________________.\n");

				ch = _getch();
			}
		}

		vector<abs_department *> & Sort()
		{
			tt.clear();
			for (int i = 0; i < t.size(); i++)
				tt.push_back(t[i]);

			bool flag = false;
			do
			{
				cls;

				switch (view_sort_menu())
				{
				case 0: return SortByCountLt(); break;
				case 1: return SortByCountLt(); break;
				case 2: return SortByCountGt(); break;
				case 3: return SortByCostLt(); break;
				case 4: return SortByCostGt(); break;
					//se 7: if (Exit()) return;
				case 5: {cls;
					//printf("�� ��������!\n");
					flag = true;
					break; }
				default: { cls;
					printf("������ ������ ���� ���!\n");
					pause;
					break;
				}
				}

			} while (!flag);
			tt.clear();
			return tt;
			
		}

		/*
		vector<abs_department *> & Sort()
		{
			tt.clear();
			for (int i = 0; i < t.size(); i++)
				tt.push_back(t[i]);

			while (true)
			{
				system("cls");
				cout << "*������� ����������������� �������*\n";
				cout << "�� ���������� � �������� �������������� ��������.\n";

				cout << "1 - ���������� �� �������� ��������.\n";
				cout << "2 - ���������� �� ����������(�� ������������ �� ������������).\n";
				cout << "3 - ���������� �� ����������(�� ������������ �� ������������).\n";
				cout << "4 - ���������� �� ���� (�� ����������� �� �����������).\n";
				cout << "5 - ���������� �� ���� (�� ����������� �� �����������).\n";
				cout << "�������� ����������� �������.\n";

				string s = "";
				getline(cin, s);
				if (s.length() != 1) continue;
				int c = s[0] - '0';

				system("cls");
				switch (c)
				{
				case 1: return SortByCountLt(); break;
				case 2: return SortByCountLt(); break;
				case 3: return SortByCountGt(); break;
				case 4: return SortByCostLt(); break;
				case 5: return SortByCostGt(); break;

				}
			}
			return tt;
		}*/


		vector<abs_department *> & SortByName() {
			abs_department *temp;
			for (int i = 0; i < tt.size() - 1; i++)
			{
				for (int j = 0; j < tt.size() - i - 1; j++)
				{
					if (tt[j]->GetName() > tt[j + 1]->GetName())
					{
						temp = tt[j + 1];
						tt[j + 1] = tt[j];
						tt[j] = temp;
					}
				}
			}
			return tt;

		}
		vector<abs_department *> & SortByCountLt() {
			abs_department *temp;
			for (int i = 0; i < tt.size() - 1; i++)
			{
				for (int j = 0; j < tt.size() - i - 1; j++)
				{
					if (tt[j]->GetCount() > tt[j + 1]->GetCount())
					{
						temp = tt[j + 1];
						tt[j + 1] = tt[j];
						tt[j] = temp;
					}
				}
			}
				return tt;
		
		}
		vector<abs_department *> & SortByCountGt() {
			abs_department *temp;
			for (int i = 0; i < tt.size() - 1; i++)
			{
				for (int j = 0; j < tt.size() - i - 1; j++)
				{
					if (tt[j]->GetCount() < tt[j + 1]->GetCount())
					{
						temp = tt[j + 1];
						tt[j + 1] = tt[j];
						tt[j] = temp;
					}
				}
			}
			return tt;

		}

		vector<abs_department *> & SortByCostLt() {
			abs_department *temp;
			for (int i = 0; i < tt.size() - 1; i++)
			{
				for (int j = 0; j < tt.size() - i - 1; j++)
				{
					if (tt[j]->GetSingleCount() > tt[j + 1]->GetSingleCount())
					{
						temp = tt[j + 1];
						tt[j + 1] = tt[j];
						tt[j] = temp;
					}
				}
			}
			return tt;

		}



		vector<abs_department *> & SortByCostGt() {
			abs_department *temp;
			for (int i = 0; i < tt.size() - 1; i++)
			{
				for (int j = 0; j < tt.size() - i - 1; j++)
				{
					if (tt[j]->GetSingleCount() < tt[j + 1]->GetSingleCount())
					{
						temp = tt[j + 1];
						tt[j + 1] = tt[j];
						tt[j] = temp;
					}
				}
			}
			return tt;

		}
		

		void Info(string added_text = "")
		{
			cout << "������� � ������� : " << t.size() << ".\n";
			cout << "���������������� ������������� : " << users_count << ".\n";
		}

		vector<abs_department *> & FindName()
		{
			string to_find = ReadString("������� ����� ��� ������ �� ��������. Enter ��� ������. ", false);

			tt.clear();
			if (!to_find.empty()) {
				for (int i = 0; i < t.size(); i++)
					if (t[i]->ContainsText(to_find))
						tt.push_back(t[i]);
			}
			
			return tt;
		}

		vector<abs_department *> & Find()
		{
			int value, value2, cost_value;
			string type;
			ReadPredicate(type, value, value2, cost_value);			

			tt.clear();
			if (!type.empty()) {
				for (int i = 0; i < t.size(); i++)
					if (t[i]->UserPredicate(type, value, value2, cost_value))
						tt.push_back(t[i]);
				sort(tt.begin(), tt.end(), abs_department::CostComparer);
			}
			

			
			return tt;
		}

		
	private:
		string input_path;
		vector<abs_department *> t;
		vector<abs_department *> tt;

		static abs_department * Readabs_department()
		{
			cout << "__________�������� ��� ������________\n";
			cout << "FT - ���������;\nB - �������; \nMT - ������;\n";
			cout << "MK - ��������; \nV - �������;\nF - ������\n";
			cout << "C - ��� ������\n";
			string type = ReadString("������� ��������", true);
			if (type == "FT")
			{
				fruit_department * p = new fruit_department();
				p->Read();
				return p;
			}
			if (type == "B")
			{
				bread_department * v = new bread_department();
				v->Read();
				return v;
			}
			if (type == "MT")
			{
				meat_department * s = new meat_department();
				s->Read();
				return s;
			}
			if (type == "MK")
			{
				milk_department * h = new milk_department();
				h->Read();
				return h;
			}
			if (type == "V")
			{
				vegetables_department * r = new vegetables_department();
				r->Read();
				return r;
			}

			if (type == "F")
			{
				fish_department * ff = new fish_department();
				ff->Read();
				return ff;
			}
			if (type == "C")
			{
				custom * c = new custom();
				c->Read();
				return c;
			}
			return NULL;
		}

		

		static void ReadPredicate(string & type, int & value, int & value2, int & cost_value)
		{
			value = 0;
			value2 = 0;
			cost_value = 0;
			cout << "_______�������� ��� ��������_______ \n";
			cout << "FT - ������ B - ������� MT - ������ ��������� \n";
			cout << "MK - �������� ��������� V - �����\n";
			type = ReadString("������� ��������. Enter - �����.", false);
			if (type == "FT" || type == "MT" || type == "V" || type == "F")
			{
				value = ReadInt("������� ����� (��., ����� �����)", false);
			}
			if (type == "B")
			{
				value2 = ReadInt("������� ���������� ������ (��.)", false);
			}
			if (type == "MK")
			{
				value = ReadInt("������� ����� �������� (��.)", false);
			}
			if (! type.empty()) {
				cost_value = ReadInt("������� ������������ ���������", false);
			}
			
		}
	};
}
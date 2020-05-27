#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "helper.h"
#include "store.h"

#define cls system("cls");  // ��� ��������� ���������,������ system("cls"),����� cls;
#define pause system("pause");
#define printf printf_s

using namespace std;

namespace abs_departmentspace
{

	class access
	{
		

	private:
		string pass = "";
	protected:
		store * st;
	public:
		friend ostream& operator <<(ostream& fout, access *& u);
		friend istream& operator >>(istream& fin, access *& u);
		friend void PrintUsers();
		friend void ShowUsers();
		friend void DeleteUsers();
		friend void EditUser();
		friend int ReadInt();

		string name = "";
		vector<vector<abs_department *>> reciepts;

		access(store * st, string name, string pass, vector<vector<abs_department *>> reciepts)
		{
			this->st = st;
			this->pass = pass;
			this->name = name;
			this->reciepts = reciepts;
		}
		access(const access& other)
		{
			this->st = st;
			pass = other.pass;
			name = other.name;
			this->reciepts = reciepts;
		}
		bool Login(string pass)
		{
			if (pass == this->pass)
				return true;
			return false;
		}

		void ProcessAll(vector<abs_department *> & tt, string text)
		{	
			system("cls");
			
			if (tt.size() != 0)
			{
				cout << text << ".\n";
				for (int i = 0; i < tt.size(); i++)
				{
					cout << "�����: " << i + 1<< "\n";
					tt[i]->Write();
					cout << "\n";
				}
				int num = ReadInt("��� �������� ��� ���������, �������� ��� �����. Enter ��� ������", false);
				if(num > 0 && num <= tt.size()) {
					num--;
					system("cls");
					tt[num]->Write();
					Process(tt[num]);
				}
				else if (num == 0)
					cout << "�����!\n";
				else
					cout << "���������� �������� �� ����������!\n";
				cout << "�������� ��������.\n";
				system("pause");
			}

				

			cout << "\n";
		}
		
		virtual string GetType() = 0;
		virtual void Request() = 0;
		virtual void Info(string added_text = "") = 0;
		virtual bool Exit() = 0;
		virtual void Process(abs_department *&) = 0;
		//void reset_color();//������� ��� ����� �����
	};

	class admin : public access
	{
	public:
		admin(store * st, string name, string pass, vector<vector<abs_department *>> reciepts)
			: access(st, name, pass, reciepts)
		{
		}

		string GetType()
		{
			return "A";
		}


		void request_view() {
			char ch = 0;
			
		}

		

		void reset_color() {
			//printf("\x1b[0m");
		}
		void set_color(string color) {
			printf(color.c_str());
		}
		

		int view_admin_menu()
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
					if (choice > 7)
						choice = 0;
					if (choice < 0)
						choice = 7;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______������� ����������������� �������_______|  \n");
					printf(" |______________���� ��������������_____________|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c ������� ��� ������.               |\n", pointer);
						reset_color();
					}
					else
						printf(" |            ������� ��� ������.               |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����� ������� �� ��������.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����� ������� �� ��������.        |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c �������� ����� �������.           |\n", pointer);
						reset_color();
					}

					else
						printf(" |            �������� ����� �������.           |\n");
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ������� �������.                  |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ������� �������.                  |\n");
					if (choice == 4) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����������.                       |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����������.                       |\n");
					if (choice == 5) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����������� ���-�� �� ��������.   |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����������� ���-�� �� ��������.   |\n");
					if (choice == 6) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ���������� ��������������.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ���������� ��������������.        |\n");
					
					if (choice == 7) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����� �� ��������.                |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����� �� ��������.                |\n");

				}
				printf(" |______________________________________________|\n");
				printf(" .______________________________________________.\n");

				ch = _getch();
			}
		}

		void Request()
		{

			bool flag = false;
			do
			{
				cls;

				switch (view_admin_menu())
				{
				case 0: ProcessAll(st->Print(), "������ ���� ���������"); break;
				case 1: ProcessAll(st->FindName(), "������� ��������� ��������"); break;
				case 2: st->Add(); break;
				case 3: ProcessAll(st->Print(), "������ ���� ���������"); break;
				case 4: ProcessAll(st->Sort(), "������ ���� ��������������� ��������� ���������"); break;
				case 6: UsersControl(); break;
				case 5: Info(); break;
				//se 7: if (Exit()) return;
				case 7:{cls;
					printf("�� ��������!\n");
					flag = true;
					break; }
				default: { cls;
					printf("������ ������ ���� ���!\n");
					pause;
					break;
				}
				}

				} while (!flag);
		}
		


		

		void Info(string added_text = "")
		{
			cout << "�������� �������������� ��������.\n";
			cout << "��� ������������: " << name << ".\n";
			st->Info();
			if (!added_text.empty())
				cout << added_text << "\n";
			system("pause");
		}

		bool Exit()
		{
			return true;
		}

		void UsersControl() {
			bool flag = false;
			do
			{
				cls;

				switch (view_user_control_menu())
				{
				case 0: ShowUsers(); break;
				case 1: DeleteUsers(); break;
				case 2: EditUser(); break;
				
				case 3: {cls;
					
					flag = true;
					break; }
				default: { cls;
					printf("������ ������ ���� ���!\n");
					pause;
					break;
				}
				}

			} while (!flag);


		}
		int view_user_control_menu()
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
					if (choice > 3)
						choice = 0;
					if (choice < 0)
						choice = 3;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______������� ����������������� �������_______|  \n");
					printf(" |_______���� �������� ��� ��������������_______|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c ������ ���� �������������.        |\n", pointer);
						reset_color();
					}
					else
						printf(" |            ������ ���� �������������.        |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c �������� �������������.           |\n", pointer);
						reset_color();
					}

					else
						printf(" |            �������� �������������.           |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c �������������� �������������.     |\n", pointer);
						reset_color();
					}

					else
						printf(" |            �������������� �������������.     |\n");
					
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����� � ���� ��������������.      |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����� � ���� ��������������.      |\n");

				}
				printf(" |______________________________________________|\n");
				printf(" .______________________________________________.\n");

				ch = _getch();
			}
		}
		void Process(abs_department *& h)
		{
			cout << "\n������� 1, ����� �������� �������� ��������,\n";
			cout << " 2, ����� ������� �������� �� ������ ���������,\n";
			cout << " ��� ����� ������� ��� �����������...\n";
			
			char c = _getch();
			switch (c)
			{
			case '1': 
				h->Edit(); 
				st->Update(); 
				return;
			case '2': 
				st->Remove(h, h->GetCount()); 
				st->Update();
				cout << "����� ������.\n";
				system("pause");
				return;
			}
		}
	};

	class user : public access
	{
	public:
		user(store * st, string pass, string name, vector<vector<abs_department *>> reciepts)
			: access(st, pass, name, reciepts)
		{
		}
		void reset_color() {
			//printf("\x1b[0m");
		}
		void set_color(string color) {
			printf(color.c_str());
		}

		string GetType()
		{
			return "U";
		}
		int view_user_menu()
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
					if (choice > 6)
						choice = 0;
					if (choice < 0)
						choice = 6;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______������� ����������������� �������_______|  \n");
					printf(" |______________���� ������������_______________|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c ������� � ������ �������.         |\n", pointer);
						reset_color();
					}
					else
						printf(" |            ������� � ������ �������.         |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����� ������� �� ��������.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����� ������� �� ��������.        |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ������� � ������ � ��������.      |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ������� � ������ � ��������.      |\n");
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ���������� ������� ������.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ���������� ������� ������.        |\n");
					if (choice == 4) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����������� ���-�� �� ��������.   |\n", pointer);
						
						reset_color();
					}

					else
						printf(" |            ����������� ���-�� �� ��������.   |\n");
						
					if (choice == 5) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����������.                       |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����������.                       |\n");
					
					if (choice == 6) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����� �� ��������.                |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����� �� ��������.                |\n");

				}
				printf(" |______________________________________________|\n");
				printf(" .______________________________________________.\n");

				ch = _getch();
			}
		}

		void Request()
		{

			bool flag = false;
			do
			{
				cls;

				switch (view_user_menu())
				{

				case 0: ProcessAll(st->Find(), "������� ��������� ������"); break;
				case 1: ProcessAll(st->FindName(), "������� ��������� ������"); break;
				case 2: Buy(); break;
				case 3: ShowReceipts(); break;
				case 4: Info(); break;
				case 5: ProcessAll(st->Sort(), "������ ���� ��������������� ��������� ���������"); break;
				case 6: if (Exit()) return;
				case 8: {cls;
					printf("�� ��������!\n");
					flag = true;
					break; }
				default: { cls;
					printf("������ ������ ���� ���!\n");
					pause;
					break;
				}
				}

			} while (!flag);
		}


		void Info(string added_text = "")
		{
			cout << "������� ����������.\n";
			cout << "��� ������������: " << name << ".\n";
			if (!added_text.empty())
				cout << added_text << "\n";
			system("pause");
		}
		void ShowReceipts() {
			if (reciepts.size() > 0)
			{
				cout << " ���� ������� ������ :\n";
				for (int i = 0; i < reciepts.size(); i++)
				{
					int cost = 0;
					cout << "-------------  �" << i + 1 << " --------------\n";
					for (int j = 0; j < reciepts[i].size(); j++) {
						reciepts[i][j]->WriteShort();
						cost += reciepts[i][j]->GetCost();
					}
					cout << "�����: "<< cost << "\n";
					cout << "\n--------------------------------\n\n";
				}
			}else{
				cout << " ���� ������� ������ �����!!! \n";
			}
			system("pause");
		}
		void Buy(){
			

			int cost = 0;
			if (tb.size() > 0)
			{
				cout << "� ������� ��������� ��������� ������ :\n";
				for (int i = 0; i < tb.size(); i++)
				{
					tb[i]->WriteShort();
					cost += tb[i]->GetCost();
				}
				cout << "\n�������� ����� : " << cost << ".\n";
				cout << "������� 1, ����� ������ ������ � �������,\n ��� ����� ������� ��� �����������...\n";
				char c = _getch();
				if (c == '1')
				{
					
					reciepts.push_back(tb);
					
					tb.clear();
					PrintUsers();
					cout << "����������� ������ �� ����� "<<cost<<". ������� �� �������!\n";
					st->Update();
					system("pause");					
				}
			}				
			else
			{
				cout << "������� �����. ���������� �������� ������.\n";
				system("pause");
			}
		}

		bool Exit()
		{
			return true;
		}

		void Process(abs_department *& h)
		{
			cout << "\n������� 1, ����� �������� ����� � �������,\n ��� ����� ������� ��� �����������...\n";
			char c = _getch();
			if (c == '1')
			{
				int count = ReadInt("�������, ������� ������ ������ �������", 0, h->GetCount());
				if (count <= 0)
					return;
				abs_department * hh = st->Remove(h, count);
				if (hh != NULL)
					tb.push_back(hh);
			}
		}

	private:
		vector<abs_department *> tb;
		
	};

	class guest : public access
	{
	public:
		guest(store * st)
			: access(st, "�����", "", { {} })
		{
		}

		string GetType()
		{
			return "G";
		}

		void reset_color() {
			//printf("\x1b[0m");
		}
		void set_color(string color) {
			printf(color.c_str());
		}

		int view_guest_menu()
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
					if (choice > 3)
						choice = 0;
					if (choice < 0)
						choice = 3;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______������� ����������������� �������_______|  \n");
					printf(" |_________________���� �����___________________|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c ������� � ��������� �������       |\n", pointer);
						reset_color();
					}
					else
						printf(" |            ������� � ��������� �������       |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ������� � ������ �������.         |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ������� � ������ �������.         |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c ����� ������� �� ��������.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            ����� ������� �� ��������.        |\n");
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c �������� �������� �������.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            �������� �������� �������.        |\n");
					

				}
				printf(" |______________________________________________|\n");
				printf(" .______________________________________________.\n");

				ch = _getch();
			}
		}

		void Request()
		{

			bool flag = false;
			do
			{
				cls;

				switch (view_guest_menu())
				{
				case 0: ProcessAll(st->Print(), "������ ���� �������"); break;
				case 1: ProcessAll(st->Find(), "������� ��������� ������"); break;
				case 2: ProcessAll(st->FindName(), "������� ��������� ������"); break;
				case 3: return;
				//case 4: {cls;
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
		/*
		void Request()
		{
			while (true)
			{
				system("cls");
				cout << "*������� ����������������� �������*\n";
				cout << "1 - ������� � ��������� �������.\n";
				cout << "2 - ������� � ������ �������.\n";
				cout << "3 - ����� ������� �� ��������.\n";
				cout << "0 - �������� �������� ������.\n";
				cout << "�������� ����������� �������.\n";

				string s = "";
				getline(cin, s);
				if (s.length() != 1) continue;
				int c = s[0] - '0';

				system("cls");
				switch (c)
				{
				case 1: ProcessAll(st->Print(), "������ ���� �������"); break;
				case 2: ProcessAll(st->Find(), "������� ��������� ������"); break;
				case 3: ProcessAll(st->FindName(), "������� ��������� ������"); break;
				case 0: return;
				}
			}
		}
		*/

		void Info(string added_text = "")
		{
			cout << "�� ��� �������� � ������ ������ ��������.\n";
			if (!added_text.empty())
				cout << added_text << "\n";
			system("pause");
		}

		bool Exit()
		{
			return true;
		}

		void Process(abs_department *& h)
		{
			cout << "\n������� ����� ������� ��� �����������...\n";
			_getch();
		}
	};
}
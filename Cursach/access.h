#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "helper.h"
#include "store.h"

#define cls system("cls");  // для упрощения написания,вместо system("cls"),пишем cls;
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
					cout << "Номер: " << i + 1<< "\n";
					tt[i]->Write();
					cout << "\n";
				}
				int num = ReadInt("Для действий над продуктом, выберите его номер. Enter для выхода", false);
				if(num > 0 && num <= tt.size()) {
					num--;
					system("cls");
					tt[num]->Write();
					Process(tt[num]);
				}
				else if (num == 0)
					cout << "Выход!\n";
				else
					cout << "Выбранного продукта не существует!\n";
				cout << "Просмотр завершен.\n";
				system("pause");
			}

				

			cout << "\n";
		}
		
		virtual string GetType() = 0;
		virtual void Request() = 0;
		virtual void Info(string added_text = "") = 0;
		virtual bool Exit() = 0;
		virtual void Process(abs_department *&) = 0;
		//void reset_color();//функция для смены цвета
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

					if (ch == 80)//вниз
						choice++;
					if (ch == 72)//вверх
						choice--;
					if (choice > 7)
						choice = 0;
					if (choice < 0)
						choice = 7;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______Магазин продовольственных товаров_______|  \n");
					printf(" |______________Меню администратора_____________|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c Вывести все товары.               |\n", pointer);
						reset_color();
					}
					else
						printf(" |            Вывести все товары.               |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Найти продукт по названию.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Найти продукт по названию.        |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Добавить новый продукт.           |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Добавить новый продукт.           |\n");
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Удалить продукт.                  |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Удалить продукт.                  |\n");
					if (choice == 4) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Сортировки.                       |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Сортировки.                       |\n");
					if (choice == 5) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Просмотреть инф-ию об аккаунте.   |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Просмотреть инф-ию об аккаунте.   |\n");
					if (choice == 6) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Управление пользователями.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Управление пользователями.        |\n");
					
					if (choice == 7) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Выйти из аккаунта.                |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Выйти из аккаунта.                |\n");

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
				case 0: ProcessAll(st->Print(), "Список всех продуктов"); break;
				case 1: ProcessAll(st->FindName(), "Найдены следующие продукты"); break;
				case 2: st->Add(); break;
				case 3: ProcessAll(st->Print(), "Список всех продуктов"); break;
				case 4: ProcessAll(st->Sort(), "Список всех отсортированных продуктов продуктов"); break;
				case 6: UsersControl(); break;
				case 5: Info(); break;
				//se 7: if (Exit()) return;
				case 7:{cls;
					printf("До свидания!\n");
					flag = true;
					break; }
				default: { cls;
					printf("Такого пункта меню нет!\n");
					pause;
					break;
				}
				}

				} while (!flag);
		}
		


		

		void Info(string added_text = "")
		{
			cout << "Аккаунте администратора магазина.\n";
			cout << "Имя пользователя: " << name << ".\n";
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
					printf("Такого пункта меню нет!\n");
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

					if (ch == 80)//вниз
						choice++;
					if (ch == 72)//вверх
						choice--;
					if (choice > 3)
						choice = 0;
					if (choice < 0)
						choice = 3;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______Магазин продовольственных товаров_______|  \n");
					printf(" |_______Меню действий над пользователями_______|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c Список всех пользователей.        |\n", pointer);
						reset_color();
					}
					else
						printf(" |            Список всех пользователей.        |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Удаление пользователей.           |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Удаление пользователей.           |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Редактирование пользователей.     |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Редактирование пользователей.     |\n");
					
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Выйти в меню администратора.      |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Выйти в меню администратора.      |\n");

				}
				printf(" |______________________________________________|\n");
				printf(" .______________________________________________.\n");

				ch = _getch();
			}
		}
		void Process(abs_department *& h)
		{
			cout << "\nНажмите 1, чтобы изменить описание продукта,\n";
			cout << " 2, чтобы удалить продукта из списка продуктов,\n";
			cout << " или любую клавишу для продолжения...\n";
			
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
				cout << "Товар удален.\n";
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

					if (ch == 80)//вниз
						choice++;
					if (ch == 72)//вверх
						choice--;
					if (choice > 6)
						choice = 0;
					if (choice < 0)
						choice = 6;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______Магазин продовольственных товаров_______|  \n");
					printf(" |______________Меню пользователя_______________|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c Перейти к поиску товаров.         |\n", pointer);
						reset_color();
					}
					else
						printf(" |            Перейти к поиску товаров.         |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Найти продукт по названию.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Найти продукт по названию.        |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Перейти к работе с корзиной.      |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Перейти к работе с корзиной.      |\n");
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Посмотреть историю счетов.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Посмотреть историю счетов.        |\n");
					if (choice == 4) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Просмотреть инф-ию об аккаунте.   |\n", pointer);
						
						reset_color();
					}

					else
						printf(" |            Просмотреть инф-ию об аккаунте.   |\n");
						
					if (choice == 5) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Сортировки.                       |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Сортировки.                       |\n");
					
					if (choice == 6) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Выйти из аккаунта.                |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Выйти из аккаунта.                |\n");

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

				case 0: ProcessAll(st->Find(), "Найдены следующие товары"); break;
				case 1: ProcessAll(st->FindName(), "Найдены следующие товары"); break;
				case 2: Buy(); break;
				case 3: ShowReceipts(); break;
				case 4: Info(); break;
				case 5: ProcessAll(st->Sort(), "Список всех отсортированных продуктов продуктов"); break;
				case 6: if (Exit()) return;
				case 8: {cls;
					printf("До свидания!\n");
					flag = true;
					break; }
				default: { cls;
					printf("Такого пункта меню нет!\n");
					pause;
					break;
				}
				}

			} while (!flag);
		}


		void Info(string added_text = "")
		{
			cout << "Аккаунт покупателя.\n";
			cout << "Имя пользователя: " << name << ".\n";
			if (!added_text.empty())
				cout << added_text << "\n";
			system("pause");
		}
		void ShowReceipts() {
			if (reciepts.size() > 0)
			{
				cout << " Ваша история счетов :\n";
				for (int i = 0; i < reciepts.size(); i++)
				{
					int cost = 0;
					cout << "-------------  №" << i + 1 << " --------------\n";
					for (int j = 0; j < reciepts[i].size(); j++) {
						reciepts[i][j]->WriteShort();
						cost += reciepts[i][j]->GetCost();
					}
					cout << "Сумма: "<< cost << "\n";
					cout << "\n--------------------------------\n\n";
				}
			}else{
				cout << " Ваша история счетов пуста!!! \n";
			}
			system("pause");
		}
		void Buy(){
			

			int cost = 0;
			if (tb.size() > 0)
			{
				cout << "В корзине находятся следующие товары :\n";
				for (int i = 0; i < tb.size(); i++)
				{
					tb[i]->WriteShort();
					cost += tb[i]->GetCost();
				}
				cout << "\nИтоговая сумма : " << cost << ".\n";
				cout << "Нажмите 1, чтобы купить товары в корзине,\n или любую клавишу для продолжения...\n";
				char c = _getch();
				if (c == '1')
				{
					
					reciepts.push_back(tb);
					
					tb.clear();
					PrintUsers();
					cout << "Приобретены товары на сумму "<<cost<<". Спасибо за покупку!\n";
					st->Update();
					system("pause");					
				}
			}				
			else
			{
				cout << "Корзина пуста. Попробуйте добавить товары.\n";
				system("pause");
			}
		}

		bool Exit()
		{
			return true;
		}

		void Process(abs_department *& h)
		{
			cout << "\nНажмите 1, чтобы добавить товар в корзину,\n или любую клавишу для продолжения...\n";
			char c = _getch();
			if (c == '1')
			{
				int count = ReadInt("Введите, сколько единиц товара выбрать", 0, h->GetCount());
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
			: access(st, "Гость", "", { {} })
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

					if (ch == 80)//вниз
						choice++;
					if (ch == 72)//вверх
						choice--;
					if (choice > 3)
						choice = 0;
					if (choice < 0)
						choice = 3;
					if (ch == 13)//enter
						return choice;
					printf(" .______________________________________________.\n");
					printf(" |______Магазин продовольственных товаров_______|  \n");
					printf(" |_________________Меню гостя___________________|  \n");
					if (choice == 0) {
						//set_color("\x1b[38;5;15m]");
						printf(" |          %c Перейти к просмотру товаров       |\n", pointer);
						reset_color();
					}
					else
						printf(" |            Перейти к просмотру товаров       |\n");
					if (choice == 1) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Перейти к поиску товаров.         |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Перейти к поиску товаров.         |\n");
					if (choice == 2) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Найти продукт по названию.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Найти продукт по названию.        |\n");
					if (choice == 3) {
						//set_color("\x1b[38;5;15m");
						printf(" |          %c Покинуть гостевой доступт.        |\n", pointer);
						reset_color();
					}

					else
						printf(" |            Покинуть гостевой доступт.        |\n");
					

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
				case 0: ProcessAll(st->Print(), "Список всех товаров"); break;
				case 1: ProcessAll(st->Find(), "Найдены следующие товары"); break;
				case 2: ProcessAll(st->FindName(), "Найдены следующие товары"); break;
				case 3: return;
				//case 4: {cls;
				//	printf("До свидания!\n");
				//	flag = true;
				//	break; }
				default: { cls;
					printf("Такого пункта меню нет!\n");
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
				cout << "*Магазин продовольственных товаров*\n";
				cout << "1 - перейти к просмотру товаров.\n";
				cout << "2 - перейти к поиску товаров.\n";
				cout << "3 - найти продукт по названию.\n";
				cout << "0 - покинуть гостевой доступ.\n";
				cout << "Выберите необходимую команду.\n";

				string s = "";
				getline(cin, s);
				if (s.length() != 1) continue;
				int c = s[0] - '0';

				system("cls");
				switch (c)
				{
				case 1: ProcessAll(st->Print(), "Список всех товаров"); break;
				case 2: ProcessAll(st->Find(), "Найдены следующие товары"); break;
				case 3: ProcessAll(st->FindName(), "Найдены следующие товары"); break;
				case 0: return;
				}
			}
		}
		*/

		void Info(string added_text = "")
		{
			cout << "Вы вне аккаунта и можете только смотреть.\n";
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
			cout << "\nНажмите любую клавишу для продолжения...\n";
			_getch();
		}
	};
}
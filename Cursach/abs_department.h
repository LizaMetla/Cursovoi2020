#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "helper.h"

using namespace std;


namespace abs_departmentspace
{
	class abs_department
	{
	protected:

		string name = "";
		string manufacturer = "";
		string description = "";
		int cost = 0;
		int count = 1;

	public:
		static const string input_path;
		abs_department()
		{
		}

		~abs_department()
		{

		}

		virtual abs_department * Clone() = 0;

		virtual string GetType() = 0;

		virtual bool ContainsText(string text)
		{
			text = to_lower(text);
			return to_lower(name).find(text) != name.npos ||
				to_lower(manufacturer).find(text) != manufacturer.npos ||
				to_lower(description).find(text) != description.npos;
		}

		virtual bool UserPredicate(string type, int value, int value2, int cost_value)
		{
			return ((GetType() == type) || (type == "")) && 
				((cost_value <= 0) || (cost <= cost_value));
		}

		void RemoveCount(int count, abs_department *& remainder)
		{
			remainder = this->Clone();
			this->count -= count;
			remainder->count = count;
		}

		int GetCost()
		{
			return cost * count;
		}

		int GetCount()
		{
			return count;
		}
		string GetName()
		{
			return name;
		}
		int GetSingleCount()
		{
			return cost;
		}
		virtual void Read(istream & fin)//u abstractnogo producta
		{
			name = ReadString(fin);
			manufacturer = ReadString(fin);
			description = ReadString(fin);
			cost = ReadInt(fin);
			count = ReadInt(fin);
			if (count < 1)count = 1;
		}

		virtual void Write(ostream & fout)
		{
			fout << GetType() << "\n";
			fout << name << "\n";
			fout << manufacturer << "\n";
			fout << description << "\n";
			fout << cost << "\n";
			fout << count << "\n";
		}

		virtual void Read()
		{
			name = ReadString("Введите название", true);
			manufacturer = ReadString("Введите название фирмы-производителя");
			description = ReadString("Добавьте описание");
			cost = ReadInt("Введите стоимость за одну единицу");
			count = ReadInt("Введите доступное количество");
			if (count < 1)count = 1;
		}

		virtual void Write()
		{
			if (!Empty(name)) cout << "Название : " << name << ".\n";
			if (!Empty(manufacturer)) cout << "Производитель : " << manufacturer << ".\n";
			if (!Empty(description)) cout << description << "\n";
			cout << "Стоимость : " << cost << " за единицу, доступное количество : " << count << ".\n";
		}

		virtual void Edit()
		{
			EditValue("Введите название", name);
			EditValue("Введите название фирмы-производителя", manufacturer);
			EditValue("Введите описание", description);
			EditValue("Введите стоимость за одну единицу", cost);
			EditValue("Введите доступное количество", count);
			if (count < 1)count = 1;
		}

		virtual void WriteShort()
		{
			cout << "Продукт: " << name << "\n";
			cout << "Количество: " << count << "\n";
			if (!manufacturer.empty())
			cout << "Производитель: " <<  manufacturer << "\n";
		}

		static bool CostComparer(abs_department * h1, abs_department * h2) //sravnenie zen
		{
			return h1->cost < h2->cost;
		}
	};
}
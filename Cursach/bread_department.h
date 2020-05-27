#pragma once

#include <string>
#include <iostream>
#include "helper.h"
#include "abs_department.h"

using namespace std;

namespace abs_departmentspace
{
	class bread_department : public abs_department
	{
	protected:
		int volume;
	public:
		
		bread_department()
		{
		}

		bread_department(const bread_department& other)
		{
			name = other.name;
			manufacturer = other.manufacturer;
			description = other.description;
			cost = other.cost;
			count = other.count;
			volume = other.volume;
		}

		~bread_department()
		{

		}
		abs_department * Clone()
		{
			return new bread_department(*this);
		}

		string GetType()
		{
			return "B";
		}
		virtual void Read(istream & fin)
		{
			abs_department::Read(fin);
			volume = ReadInt(fin);

		}

		virtual void Write(ostream & fout)
		{
			abs_department::Write(fout);
			fout << volume << "\n";
		}

		void Read()
		{
			abs_department::Read();
			volume = ReadInt("Введите количество товара (ед.): ");
		}

		void Edit()
		{
			abs_department::Edit();
			EditValue("Введите количество товара (ед.)", volume);
		}

		void Write()
		{

			abs_department::Write();
			cout << "Количество : " << volume << " ед.\n";
		}

		virtual bool UserPredicate(string type, int value, int value2, int cost_value)
		{
			return ((value2 <= 0) || (volume >= value2)) &&
				abs_department::UserPredicate(type, value, value2, cost_value);
		}
	};
}
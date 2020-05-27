#pragma once

#include <string>
#include <iostream>
#include "helper.h"
#include "abs_department.h"

using namespace std;

namespace abs_departmentspace
{
	class milk_department : public abs_department
	{
	protected:
		int volume;
	public:
		milk_department()
		{
		}

		milk_department(const milk_department& other)
		{
			name = other.name;
			manufacturer = other.manufacturer;
			description = other.description;
			cost = other.cost;
			count = other.count;
			volume = other.volume;
		}

		~milk_department()
		{

		}
		abs_department * Clone()
		{
			return new milk_department(*this);
		}

		string GetType()
		{
			return "MK";
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
			volume = ReadInt("Введите объем: ", true);
		}

		void Edit()
		{
			abs_department::Edit();
			EditValue("Введите объем продукта", volume);
		}

		void Write()
		{
			
			abs_department::Write();
			cout << "Вес : " << volume << ".\n";
		}

		virtual bool UserPredicate(string type, int value, int value2, int cost_value)
		{
			return ((value2 <= 0) || (volume >= value2)) &&
				abs_department::UserPredicate(type, value, value2, cost_value);
		}
	};
}
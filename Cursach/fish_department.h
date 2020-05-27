#pragma once

#include <string>
#include <iostream>
#include "helper.h"
#include "abs_department.h"

using namespace std;

namespace abs_departmentspace
{
	class fish_department : public abs_department
	{
	protected:
		int volume;
		string country;

	public:

		fish_department()
		{
		}

		fish_department(const fish_department& other)
		{
			name = other.name;
			manufacturer = other.manufacturer;
			description = other.description;
			cost = other.cost;
			count = other.count;
			volume = other.volume;
			country = other.country;
		}

		~fish_department()
		{

		}
		abs_department * Clone()
		{
			return new fish_department(*this);
		}

		string GetType()
		{
			return "F";
		}
		virtual void Read(istream & fin)
		{
			abs_department::Read(fin);
			volume = ReadInt(fin);
			country = ReadString(fin);

		}

		virtual void Write(ostream & fout)
		{
			abs_department::Write(fout);
			fout << volume << "\n";
			fout << country << "\n";
		}

		void Read()
		{
			abs_department::Read();
			volume = ReadInt("Введите массу (гр., целое число)");
			country = ReadString("Введите страну производителя: ", true);
		}

		void Edit()
		{
			abs_department::Edit();
			EditValue("Введите массу (гр., целое число))", volume);
			EditValue("Введите страну производителя: ", country);
		}

		void Write()
		{

			abs_department::Write();
			cout << "Масса : " << volume << "гр.\n";
			cout << "Cтрана производителя : " << country << "\n";
		}

		virtual bool UserPredicate(string type, int value, int value2, int cost_value)
		{
			return ((value2 <= 0) || (volume >= value2)) &&
				abs_department::UserPredicate(type, value, value2, cost_value);
		}
	};
}
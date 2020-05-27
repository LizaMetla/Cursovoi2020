#pragma once

#include <string>
#include <iostream>
#include "helper.h"
#include "abs_department.h"

using namespace std;

namespace abs_departmentspace
{
	class fruit_department : public virtual abs_department
	{
	protected:
		int volume;
	public:
		fruit_department()
		{
		}

		fruit_department(const fruit_department& other)
		{
			name = other.name;
			manufacturer = other.manufacturer;
			description = other.description;
			cost = other.cost;
			count = other.count;
			volume = other.volume;
		}

		~fruit_department()
		{

		}

		abs_department * Clone()
		{
			return new fruit_department(*this);
		}

		string GetType()
		{
			return "FT";
		}
		virtual void Read(istream & fin)
		{
			abs_department::Read(fin);
			volume = ReadInt(fin);//iz abstraktnogo v konkretni putem dobavleniya opedelennih strok
		}

		virtual void Write(ostream & fout)
		{
			abs_department::Write(fout);
			fout << volume << "\n";
		}

		void Read()
		{
			abs_department::Read();
			volume = ReadInt("Введите массу фруктов: ");
		}

		void Edit()
		{
			abs_department::Edit();
			EditValue("Введите массу фруктов", volume);
		}

		void Write()
		{
			abs_department::Write();
			cout << "Масса: " << volume << ".\n";
		}

		virtual bool UserPredicate(string type, int value, int value2, int cost_value)
		{
			return abs_department::UserPredicate(type, value, value2, cost_value) && ((value2 <= 0) || (volume >= value2));
		}
	};
}
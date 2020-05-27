#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "helper.h"
#include "abs_department.h"

using namespace std;

namespace abs_departmentspace
{
	class custom : public abs_department
	{
	protected:
		string type = "";

	public:
		custom()
		{
		}
		
		custom(const custom& other)
		{
			name = other.name;
			manufacturer = other.manufacturer;
			description = other.description;
			cost = other.cost;
			count = other.count;
			type = other.type;
		}

		~custom()
		{

		}

		abs_department * Clone()
		{
			return new custom(*this);
		}

		string GetType()
		{
			return "C";
		}

		bool ContainsText(string text)
		{
			text = to_lower(text);
			return to_lower(type).find(text) != type.npos ||
				abs_department::ContainsText(text);
		}

		void Read(istream & fin)
		{
			abs_department::Read(fin);
			type = ReadString(fin);
		}

		void Write(ostream & fout)
		{
			abs_department::Write(fout);
			fout << type << "\n";
		}

		void Read()
		{
			type = ReadString("¬ведите тип продукта", true);
			abs_department::Read();
		}

		void Write()
		{
			cout << type << " " << name<<".\n";
			abs_department::Write();
		}
	};
}
#pragma once

#include <string>
#include <iostream>
#include "helper.h"
#include "abs_department.h"

using namespace std;

namespace abs_departmentspace
{
	class vegetables_department : public abs_department
	{
	protected:
		int volume;
	public:
		vegetables_department()
		{
		}

		vegetables_department(const vegetables_department& other)
		{
			name = other.name;
			manufacturer = other.manufacturer;
			description = other.description;
			cost = other.cost;
			count = other.count;
			volume = other.volume;
		}

		~vegetables_department()
		{

		}
		abs_department * Clone()
		{
			return new vegetables_department(*this);
		}

		string GetType()
		{
			return "V";
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
			volume = ReadInt("������� ����� (��., ����� �����)");
		}

		void Edit()
		{
			abs_department::Edit();
			EditValue("������� ����� (��., ����� �����)", volume);
		}

		void Write()
		{
			abs_department::Write();
			cout << "����� : " << volume << "��.\n";
		}

		virtual bool UserPredicate(string type, int value, int value2, int cost_value)
		{
			return ((value2 <= 0) || (volume >= value2)) &&
				abs_department::UserPredicate(type, value, value2, cost_value);
		}
	};
}
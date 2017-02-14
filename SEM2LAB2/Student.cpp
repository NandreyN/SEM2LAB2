#include "Student.h"
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

Student::Student(const string& toParse)
{
	this->parseAndInit(toParse);
}

Student::Student(const Student& st)
{
	this->_marks = st.getMarks();
	this->_surname = st.getSurname();
	this->_groupNumber = st.getGroup();
}

Student::~Student()
{
}

std::string Student::getSurname() const
{
	return this->_surname;
}

int Student::getGroup() const
{
	return this->_groupNumber;
}

std::vector<int> Student::getMarks() const
{
	return this->_marks;
}

bool Student::operator<(const Student& another)const
{
	return this->_surname < another.getSurname() ? true : false;
}

bool Student::operator>(const Student& another)const
{
	return !this->operator<(another);
}

bool Student::operator<=(const Student& another)const
{
	return !(this->operator>(another));
}

bool Student::operator>=(const Student& another)const
{
	return !this->operator<=(another);
}

bool Student::operator==(const Student& another) const
{
	return (another.getSurname() == this->_surname) ? true : false;
}

bool Student::operator!=(const Student& another)const
{
	return !this->operator==(another);
}

bool Student::doneWithSession() const
{
	int a = count_if(this->_marks.begin(), this->_marks.end(), [](int m) {return m < 4; });
	return (a == 0) ? true : false;
}

int Student::getSum() const
{
	return accumulate(this->_marks.begin(), this->_marks.end(), 0);
}

void Student::parseAndInit(const std::string& line)
{
	//Linnik 11 4 4 9 9
	std::istringstream iss(line);
	iss >> this->_surname;
	iss >> this->_groupNumber;

	while (!iss.eof())
	{
		string mark;
		iss >> mark;
		this->_marks.push_back(atoi(mark.c_str()));
	}
}

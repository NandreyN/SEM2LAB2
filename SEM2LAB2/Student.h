#pragma once
#include <vector>
#include <string>
#include <sstream>
#include  <iostream>
#include <iterator>

class Student
{
public:
	Student(const std::string&);
	Student(const Student&);

	~Student();

	std::string getSurname() const;
	int getGroup() const;
	std::vector<int> getMarks() const;

	bool operator<(const Student&) const;
	bool operator>(const Student&) const;
	bool operator<=(const Student&)const;
	bool operator>=(const Student&)const;
	bool operator==(const Student&)const;
	bool operator!=(const Student&)const;

	bool doneWithSession() const;
	int getSum() const;
private:
	void parseAndInit(const std::string&);
	std::vector<int> _marks;
	std::string _surname;
	int _groupNumber;
};

inline std::ostream& operator<<(std::ostream& s, const Student& student)
{
	s << student.getSurname() << " " << student.getGroup() << " ";
	auto marks = student.getMarks();
	std::copy(marks.begin(),marks.end(), std::ostream_iterator<int>(s, " "));
	s << std::endl;
	return s;
}
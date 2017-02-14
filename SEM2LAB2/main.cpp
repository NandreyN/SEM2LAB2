// 15,17 mod 4/3/5
#include <iostream>
#include<fstream>
#include <assert.h>
#include <string>
#include <vector>
#include <iterator>
#include<algorithm>
#include "Student.h"
#include <map>

using namespace std;

int main()
{
	ifstream in("in.txt");
	assert(in.is_open());

	vector<Student> students;

	while (!in.eof())
	{
		string data;
		getline(in, data);
		Student a(data);
		students.push_back(a);
	}

	assert(students.size() != 0);

	sort(students.begin(), students.end(), [](const Student& st1, const Student& st2) {return st1 < st2; });

	string surnameToRemove;
	cin >> surnameToRemove;

	auto it = remove_if(students.begin(), students.end(), [&surnameToRemove](const Student& st)
	{
		return surnameToRemove == st.getSurname();
	});

	if (it != students.end())
		students.erase(it);

	copy(students.begin(), students.end(), ostream_iterator<Student>(cout, "\n"));

	multimap<string, Student> stMap;
	for (int i = 0; i < students.size(); i++) // not by ref!
		stMap.insert(make_pair(students[i].getSurname(), students[i]));

	typedef  multimap<string, Student> ::iterator iter;
	cout << "--------------" << endl;

	for_each(stMap.begin(), stMap.end(), [](const pair<string, Student>& pr) {if (!pr.second.doneWithSession()) cout << pr.second; });

	cout << "Input group number" << endl;
	int reqGroup;
	cin >> reqGroup;
	cout << "max : ";

	iter stud = find_if(stMap.begin(), stMap.end(), [&reqGroup](const pair<string, Student>& pr) {return pr.second.getGroup() == reqGroup; });
	//assert(stud != stMap.end());
	iter bgn = stMap.begin();
	while (bgn != stMap.end())
	{
		if (bgn->second.getGroup() == reqGroup)
			if (bgn->second.getSum() > stud->second.getSum())
				stud = bgn;
		++bgn;
	}
	cout << stud->second;

	in.close();
	return 0;
}
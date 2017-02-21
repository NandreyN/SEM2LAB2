#include <iostream>
#include  <vector>
#include <fstream>
#include "Route.h"
#include <map>
#include <assert.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <numeric>
#include <functional>

using namespace std;
int main()
{
	// 15 mod 3 = 0 => a ) vector
	//  map key=> a) driver
	// (4)	15 mod 4 = 3 => d)
	//		17 mod 4 = 1 => b)
	// (5)	15 mod 3 = 0 => a)
	//		17 mod 3 = 2 => c)
	// (6)	15 mod 5 = 0 = > a)
	//		17 mod 5 = 2 => c)

	vector<Route> routesVect;

	ifstream in("in.txt");
	assert(in.is_open());
	while (!in.eof())
	{
		string name, brand;
		int busId, routeId;
		in >> routeId >> name >> busId >> brand;
		routesVect.push_back(Route(name, brand, routeId, busId));
	}
	in.close();

	cout << "Sorted by bus # : " << endl;
	// sort busID
	sort(routesVect.begin(), routesVect.end(), [](const Route& rt1, const Route& rt2) {return rt1.getBusNumber() < rt2.getBusNumber(); });
	copy(routesVect.begin(), routesVect.end(), ostream_iterator<Route>(cout, "\n"));

	cout << endl << "Sorted by route  # : " << endl;
	sort(routesVect.begin(), routesVect.end(), [](const Route& rt1, const Route& rt2) {return rt1.getRId() < rt2.getRId(); });
	copy(routesVect.begin(), routesVect.end(), ostream_iterator<Route>(cout, "\n"));

	//(2) key == driver
	multimap<string, Route> routesMap;
	for_each(routesVect.begin(), routesVect.end(), [&routesMap](const Route& rt) {routesMap.insert(make_pair(rt.getDriver(), rt)); });
	//(3)
	cout << "Printing multimap : " << endl;
	for_each(routesMap.begin(), routesMap.end(), [](pair<string, Route> pair) {cout << pair.second; });
	// (4) b,d
	int reqRoute = 342;
	cout << endl << "Route : " << reqRoute << endl;

	for_each(routesMap.begin(), routesMap.end(), [&reqRoute](pair<string, Route> pair)
	{
		if (pair.second.getRId() == reqRoute) cout << pair.second.getBusNumber() << endl;
	});

	//d	вывести список всех водителей, работающих на одной марке автобуса;
	cout << endl << "One brand : " << endl;
	map<string, set<string>> mapDrivers;
	for_each(routesVect.begin(), routesVect.end(), [&mapDrivers](const Route& rt)
	{
		mapDrivers[rt.getDriver()].insert(rt.getBrand());
	});
	
	for_each(mapDrivers.begin(), mapDrivers.end(), [&mapDrivers] (pair<string, set<string>> pair)
	{
		if (pair.second.size() == 1) cout << pair.first << endl;
	});
	cout << endl;

	//5ac
	typedef multimap<string, Route>::iterator mapIter;
	mapIter target;
	Route toDel("Krilov", "MAZ", 101,22);
	target = find_if(routesMap.begin(), routesMap.end(), [&toDel](pair<string, Route> pair) {return  pair.second == toDel; });
	if (target != routesMap.end())
		routesMap.erase(target);

	cout << "Without deleted bus : " << endl;
	for_each(routesMap.begin(), routesMap.end(), [](pair<string, Route> pair) {cout << pair.second; });

	// change bus
	int changeFrom = 100, changeTo = 38;
	target = find_if(routesMap.begin(), routesMap.end(), [changeFrom](pair<string, Route> pair) {return changeFrom == pair.second.getBusNumber(); });
	if (target != routesMap.end())
		target->second.setBusNumber(changeTo);

	cout << "Changed bus : " << endl;
	for_each(routesMap.begin(), routesMap.end(), [](pair<string, Route> pair) {cout << pair.second; });

	//6ac a	найти маршрут с наибольшим количеством автобусов.

	map<int, int> routesBuses;
	for_each(routesVect.begin(), routesVect.end(), [&routesBuses](const Route& p) {routesBuses[p.getRId()]++; });
	map<int,int>::iterator p = max_element(routesBuses.begin(), routesBuses.end(), [](auto pair1, auto pair2) {return pair1.second < pair2.second; });
	cout << "Route with max buses : " << p->first << endl;

	//c)	найти маршрут, на котором работают автобусы одной марки

	map<int, set<string>> routesBrands;
	for_each(routesVect.begin(), routesVect.end(), [&routesBrands](const Route& p)
	{
		routesBrands[p.getRId()].insert(p.getBrand());
	});

	for_each(routesBrands.begin(), routesBrands.end(), [](pair<int, set<string>> pair)
	{
		if (pair.second.size() == 1) cout << pair.first << endl;
	});
	return 0;
}

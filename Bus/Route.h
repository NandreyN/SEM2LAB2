#pragma once
#include <string>

using namespace std;
class Route
{
public:
	Route(const string& driver, const string& brand, int route, int busNumber);
	~Route();

	int getRId() const;
	int getBusNumber() const;
	string getDriver() const;
	string getBrand() const;

private:
	int _routeID;
	string _driver;
	int _busNumber;
	string _busBrand;
};


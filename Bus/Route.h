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
	void setBusNumber(int num) { _busNumber = num; }
	string getDriver() const;
	string getBrand() const;
	bool operator==(const Route&) const;
private:
	int _routeID;
	string _driver;
	int _busNumber;
	string _busBrand;
};

inline ostream& operator<<(ostream& o ,const Route& rt)
{
	o << rt.getRId() << " " << rt.getDriver() << " " << rt.getBusNumber() << " " << rt.getBrand() << endl;
	return o;
}

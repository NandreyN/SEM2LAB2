#include "Route.h"

Route::Route(const string& driver, const string& brand, int route, int busNumber)
{
	_driver = driver;
	_busBrand = brand;
	_routeID = route;
	_busNumber = busNumber;
}

Route::~Route()
{
}

int Route::getRId() const
{
	return _routeID;
}

int Route::getBusNumber() const
{
	return _busNumber;
}

string Route::getDriver() const
{
	return _driver;
}

string Route::getBrand() const
{
	return _busBrand;
}
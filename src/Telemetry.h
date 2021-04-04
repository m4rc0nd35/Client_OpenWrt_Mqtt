#ifndef TELEMETRY_H // include guard
#define TELEMETRY_H

#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Telemetry
{
public:
	vector<string> split(string s, string delimiter);
	string serial_number();
	string exec(string command); 
	string wifi();
	string mac();
};
#endif /* TELEMETRY_H */
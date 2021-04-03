#ifndef TELEMETRY_H // include guard
#define TELEMETRY_H

#include <regex>
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
};
#endif /* TELEMETRY_H */
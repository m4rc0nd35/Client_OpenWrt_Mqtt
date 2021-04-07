#ifndef TELEMETRY_H // include guard
#define TELEMETRY_H

#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "MQTTClient.h"

using namespace std;

class Telemetry
{
public:
	vector<string> split(string s, string delimiter);
	string serial_number();
	static string exec(string command); 
	string wifi();
	string mac();
	static void callbackCmdAll(MQTT::MessageData &md);
	static void callbackCmdMac(MQTT::MessageData &md);
};
#endif /* TELEMETRY_H */
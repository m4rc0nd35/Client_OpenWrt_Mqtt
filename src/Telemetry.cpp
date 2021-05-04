#include "Telemetry.h"

vector<string> Telemetry::split(string s, string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}
string Telemetry::serial_number()
{
	return exec("cat /proc/device-tree/serial-number");
}
string Telemetry::exec(string command)
{
	char buffer[128];
	string result = "";

	FILE *pipe = popen(command.c_str(), "r");
	if (!pipe)
		return "popen failed!";

	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}

	pclose(pipe);
	return result;
}
string Telemetry::wifi()
{
	string data;
	data.append(exec("uci get wireless.default_radio0.ssid | awk '{print $1,$2}' | tr '\n' '|' | sed 's/ //g'"));
	data.append(exec("uci get wireless.default_radio0.mode | awk '{print $1,$2}' | tr '\n' '|' | sed 's/ //g'"));
	data.append(exec("uci get wireless.default_radio0.encryption | awk '{print $1,$2}' | tr '\n' '|' | sed 's/ //g'"));
	data.append(exec("iwinfo wlan0 assoclist | grep -i 'dBm / unknown' | awk '{print $1,$2}' | tr '\n' ';' | sed 's/ /#/g'"));
	return data;
}
string Telemetry::mac()
{
	return exec("ifconfig | grep -i HWaddr | awk '{if($1 == \"br-lan\") print $5}' | tr '\n' ' ' | sed 's/ //g' ");
}
void Telemetry::callbackCmdAll(MQTT::MessageData &md)
{
	MQTT::Message &message = md.message;

	char payload[255];
	string text;
	strcpy(payload, (char *)message.payload );
	
	for (int i = 0; (int)message.payloadlen > i; i++)
		text.push_back(payload[i]);
	
	exec(text);
	cout << "callbackCmdAll: "<< text << endl;
}
void Telemetry::callbackCmdMac(MQTT::MessageData &md)
{
	MQTT::Message &message = md.message;

	char payload[255];
	string text;
	strcpy(payload, (char *)message.payload );
	
	for (int i = 0; (int)message.payloadlen > i; i++)
		text.push_back(payload[i]);
	exec(text);
	cout << "callbackCmdMac: "<< text << endl;
}
#include <Telemetry.h>

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
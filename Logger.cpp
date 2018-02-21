#include "Logger.h"

void resetColor(int color, bool lineBreak) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (lineBreak)
		std::cout << std::endl;
	else
		std::cout << "";
	SetConsoleTextAttribute(hConsole, color);
}

tm getTimeStruct() {
	time_t time_raw;
	time(&time_raw);
	tm time;
	localtime_s(&time, &time_raw);
	return time;
}

std::string getTimeStamp(tm timeStruct) {
	int hrs = timeStruct.tm_hour;
	std::string hrs_str;
	if (hrs < 10)
		hrs_str = "0" + std::to_string(hrs);
	else
		hrs_str = std::to_string(hrs);

	int mins = timeStruct.tm_min;
	std::string mins_str;
	if (mins < 10)
		mins_str = "0" + std::to_string(mins);
	else
		mins_str = std::to_string(mins);

	int secs = timeStruct.tm_sec;
	std::string secs_str;
	if (secs < 10)
		secs_str = "0" + std::to_string(secs);
	else
		secs_str = std::to_string(secs);

	std::string finalTimeStamp = "[" + hrs_str + ":" + mins_str + ":" + secs_str + "]";

	return finalTimeStamp;
}
#include "Countdown.h"

Countdown::Countdown()
{
}
Countdown::Countdown(int ms)
{
	countdown_ms(ms);
}
bool Countdown::expired()
{
	struct timeval now, res;
	gettimeofday(&now, NULL);
	timersub(&end_time, &now, &res);
	//printf("left %d ms\n", (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000);
	//if (res.tv_sec > 0 || res.tv_usec > 0)
	//	printf("expired %d %d\n", res.tv_sec, res.tv_usec);
	return res.tv_sec < 0 || (res.tv_sec == 0 && res.tv_usec <= 0);
}

void Countdown::countdown_ms(int ms)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	struct timeval interval = {ms / 1000, (ms % 1000) * 1000};
	//printf("interval %d %d\n", interval.tv_sec, interval.tv_usec);
	timeradd(&now, &interval, &end_time);
}

void Countdown::countdown(int seconds)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	struct timeval interval = {seconds, 0};
	timeradd(&now, &interval, &end_time);
}

int Countdown::left_ms()
{
	struct timeval now, res;
	gettimeofday(&now, NULL);
	timersub(&end_time, &now, &res);
	// printf("left %d ms\n", (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000);
	return (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000;
}
#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

class Countdown
{
public:
	Countdown();
	Countdown(int ms);
	bool expired();
	void countdown_ms(int ms);
	void countdown(int seconds);
	int left_ms();

private:
	struct timeval end_time;
};
#endif /* COUNTDOWN_H */
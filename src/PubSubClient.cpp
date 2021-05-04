#include "PubSubClient.h"

PubSubClient::PubSubClient(){}
int PubSubClient::connect(const char *hostname, int port)
{
	int type = SOCK_STREAM;
	struct sockaddr_in address;
	int rc = -1;
	sa_family_t family = AF_INET;
	struct addrinfo *result = NULL;
	struct addrinfo hints = {0, AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP, 0, NULL, NULL, NULL};

	if ((rc = getaddrinfo(hostname, NULL, &hints, &result)) == 0)
	{
		struct addrinfo *res = result;

		/* prefer ip4 addresses */
		while (res)
		{
			if (res->ai_family == AF_INET)
			{
				result = res;
				break;
			}
			res = res->ai_next;
		}

		if (result->ai_family == AF_INET)
		{
			address.sin_port = htons(port);
			address.sin_family = family = AF_INET;
			address.sin_addr = ((struct sockaddr_in *)(result->ai_addr))->sin_addr;
		}
		else
			rc = -1;

		freeaddrinfo(result);
	}

	if (rc == 0)
	{
		mysock = socket(family, type, 0);
		if (mysock != -1)
		{
			rc = ::connect(mysock, (struct sockaddr *)&address, sizeof(address));
		}
	}

	return rc;
}
int PubSubClient::read(unsigned char *buffer, int len, int timeout_ms)
{
	struct timeval interval = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
	if (interval.tv_sec < 0 || (interval.tv_sec == 0 && interval.tv_usec <= 0))
	{
		interval.tv_sec = 0;
		interval.tv_usec = 100;
	}

	setsockopt(mysock, SOL_SOCKET, SO_RCVTIMEO, (char *)&interval, sizeof(struct timeval));

	int bytes = 0;
	int i = 0;
	const int max_tries = 10;
	while (bytes < len)
	{
		int rc = ::recv(mysock, &buffer[bytes], (size_t)(len - bytes), 0);
		if (rc == -1)
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK)
				bytes = -1;
			break;
		}
		else
			bytes += rc;
		if (++i >= max_tries)
			break;
		if (rc == 0)
			break;
	}
	return bytes;
}

int PubSubClient::write(unsigned char *buffer, int len, int timeout)
{
	struct timeval tv;

	tv.tv_sec = 0;				 /* 30 Secs Timeout */
	tv.tv_usec = timeout * 1000; // Not init'ing this can cause strange errors

	setsockopt(mysock, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(struct timeval));
	int rc = ::write(mysock, buffer, len);
	//printf("write rc %d\n", rc);
	return rc;
}

int PubSubClient::disconnect()
{
	return ::close(mysock);
}
#ifndef PUBSUBCLIENT_H // include guard
#define PUBSUBCLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

class PubSubClient
{
public:
  PubSubClient();
  int connect(const char* hostname, int port);
  int disconnect();
  int read(unsigned char* buffer, int len, int timeout_ms);
  int write(unsigned char* buffer, int len, int timeout);
private:
  int mysock;
  
};
#endif /* PUBSUBCLIENT_H */
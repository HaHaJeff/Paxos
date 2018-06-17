#include "paxos_server.h"

int main()
{
  PaxosServer server("127.0.0.1:50051");
  server.Start();
  return 0;
}

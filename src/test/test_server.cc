#include "paxos_server.h"

int main()
{
  std::shared_ptr<StateMachine> pState = std::make_shared<StateMachine>();
  PaxosServer server("127.0.0.1:50051", pState);
  server.Start();
  return 0;
}

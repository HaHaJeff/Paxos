#include "paxos_server.h"

int main(int argc, char **argv)
{
  std::shared_ptr<StateMachine> pState = std::make_shared<StateMachine>();
  PaxosServer server(argv[1], pState);
  server.Start();
  return 0;
}

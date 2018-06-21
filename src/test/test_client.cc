#include "paxos_client.h"

int main()
{
  std::shared_ptr<StateMachine> pState = std::make_shared<StateMachine>();
  PaxosClient client(pState);

  std::pair<uint32_t, std::string> p1 = std::make_pair(1, "127.0.0.1:50051");
  std::pair<uint32_t, std::string> p2 = std::make_pair(2, "127.0.0.1:50052");

  client.AddPeer(p1);
  client.AddPeer(p2);

  client.AddValue("get k");
  client.AddValue("modify k");

  while (!client.Prepare() );

  client.Accept();

  return 0;
}

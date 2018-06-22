#include <future>

#include "paxos_client.h"
#include "paxos_server.h"

void Server(std::shared_ptr<StateMachine> pState, const std::string &address) {
  PaxosServer server(address, pState);
  server.Start();
}

int main()
{
  std::shared_ptr<StateMachine> pState = std::make_shared<StateMachine>();
  PaxosClient client(pState);


  std::pair<uint32_t, std::string> p0 = std::make_pair(0, "127.0.0.1:50050");
  std::pair<uint32_t, std::string> p1 = std::make_pair(1, "127.0.0.1:50051");
  std::pair<uint32_t, std::string> p2 = std::make_pair(2, "127.0.0.1:50052");

//  std::async(std::launch::async, Server, pState, p0.second);

  client.AddPeer(p0);
  client.AddPeer(p1);
  client.AddPeer(p2);

  client.AddValue("get k");
  client.AddValue("modify k");

  uint32_t instance, peer;

  if (client.Prepare(instance)) {
    if (client.Accept(instance, peer)) {
      client.Success(instance, peer);
    }
  }

  return 0;
}

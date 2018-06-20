#include "paxos_client.h"

int main()
{
  std::shared_ptr<StateMachine> pState = std::make_shared<StateMachine>();
  PaxosClient client(grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials()), pState);
  client.Prepare();
  return 0;
}

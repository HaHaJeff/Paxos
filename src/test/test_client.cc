#include "paxos_client.h"

int main()
{
  StateMachine sm;
  PaxosClient client(grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials()), &sm);
  PrepareRequest request;
  PrepareReply reply;
  client.Prepare();
  return 0;
}

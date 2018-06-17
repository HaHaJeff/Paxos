#include "paxos_client.h"

int main()
{
  PaxosClient client(grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials()));
  PrepareRequest request;
  PrepareReply reply;
  client.SendPrepare(request, &reply);
  return 0;
}

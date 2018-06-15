#include "comdef.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

#ifndef PAXOSCLIENT_H
#define PAXOSCLIENT_H

//rpc client;
//use grpc stub;
class PaxosClient {
  public:
    PaxosClient(std::shared_ptr<Channel> channel) : stub_(NewStub(channel)) {  }

    void SendPrepare(const PrepareRequest &request, PreapreReply &reply);
    void SendAccept(const AcceptRequest &request, AcceptReply &reply);
    void SendSuccess(const SuccessRequest &request, SuccessReply &reply);

  private:
    std::unique_ptr<Stub> stub_;
};

#endif

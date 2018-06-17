#include "paxos_client.h"

PaxosClient::PaxosClient(std::shared_ptr<Channel> channel)
  : stub_(Paxos::NewStub(channel)) {  }

void PaxosClient::SendPrepare(const PrepareRequest &request, PrepareReply &reply) {
  std::cout << "rpc call OnPrepare" << std::endl;
  ClientContext context;
  stub_->OnPrepare(&context, request, &reply);
}

void PaxosClient::SendAccept(const AcceptRequest &request, AcceptReply &reply) {
  std::cout << "rpc call OnAccept" << std::endl;
  ClientContext context;
  stub_->OnAccept(&context, request, &reply);
}

void PaxosClient::SendSuccess(const SuccessRequest &request, SuccessReply &reply) {
  std::cout << "rpc call OnSuccess" << std::endl;
  ClientContext context;
  stub_->OnSuccess(&context, request, &reply);
}

void PaxosClient::Prepare() {
  PrepareRequest request;
  PrepareReply reply;

  GetPrepareRequest(request);
  SendPrepare(request, reply);
  SetPrepareReply(reply);
}

void PaxosClient::Accept() {
  AcceptRequest request;
  AcceptReply   reply;

  GetAcceptRequest(request);
  SendAccept(request, reply);
  SetAcceptReply(reply);
}

void PaxosClient::Success() {
  SuccessRequest request;
  SuccessReply   reply;

  GetSuccessRequest(request);
  SendSuccess(request, reply);
  SetSuccessReply(reply);
}

#include "paxos_client.h"

PaxosClient::PaxosClient(std::shared_ptr<StateMachine> pState)
  : pProposer_(new Proposer(pState)) {

  }

void PaxosClient::AddPeer(const std::pair<uint32_t, std::string> &peer) {

  peers_.insert(peer);

  std::shared_ptr<::grpc::Channel> channel = grpc::CreateChannel(peer.second, grpc::InsecureChannelCredentials());
  std::unique_ptr<Paxos::Stub> uStub = Paxos::NewStub(channel);
  std::shared_ptr<Paxos::Stub> stub = std::move(uStub);
  std::pair<const uint32_t, std::shared_ptr<Paxos::Stub> > p = std::make_pair(peer.first, stub);

  stub_.insert(p);
}

void PaxosClient::AddValue(const std::string &value) {
  pProposer_->AddValue(value);
}

void PaxosClient::SendPrepare(const PrepareRequest &request, PrepareReply &reply) {
  std::cout << "rpc call OnPrepare" << std::endl;

  std::for_each(stub_.begin(), stub_.end(), [&](std::pair<const uint32_t, std::shared_ptr<Paxos::Stub> > peer){
      ClientContext context;
      std::shared_ptr<Paxos::Stub> stub = peer.second;
      stub->OnPrepare(&context, request, &reply);
      SetPrepareReply(reply);
      });

}

void PaxosClient::SendAccept(const AcceptRequest &request, AcceptReply &reply) {
  std::cout << "rpc call OnAccept" << std::endl;

  std::for_each(stub_.begin(), stub_.end(), [&](std::pair<const uint32_t, std::shared_ptr<Paxos::Stub> > peer){
      ClientContext context;
      std::shared_ptr<Paxos::Stub> stub = peer.second;
      stub->OnAccept(&context, request, &reply);
      SetAcceptReply(reply);
      });
}

void PaxosClient::SendSuccess(const SuccessRequest &request, SuccessReply &reply) {
  std::cout << "rpc call OnSuccess" << std::endl;

  std::for_each(stub_.begin(), stub_.end(), [&](std::pair<const uint32_t, std::shared_ptr<Paxos::Stub> > peer){
      ClientContext context;
      std::shared_ptr<Paxos::Stub> stub = peer.second;
      stub->OnSuccess(&context, request, &reply);
      SetSuccessReply(reply);
      });
}

bool PaxosClient::Prepare() {
  PrepareRequest request;
  PrepareReply reply;

  GetPrepareRequest(request);
  SendPrepare(request, reply);

  pProposer_->Print();
  bool majority = pProposer_->Count(reply.instanceid()) > peers_.size()/2 ? true : false;

  return majority;
}

bool PaxosClient::Accept() {
  AcceptRequest request;
  AcceptReply   reply;

  GetAcceptRequest(request);
  SendAccept(request, reply);

  pProposer_->Print();
  bool majority = pProposer_->Count(reply.instanceid()) > peers_.size()/2 ? true : false;

  return majority;
}

bool PaxosClient::Success() {
  SuccessRequest request;
  SuccessReply   reply;

  GetSuccessRequest(request);
  SendSuccess(request, reply);

  return false;
}

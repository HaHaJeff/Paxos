#include "comdef.h"
#include "proposer.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

#ifndef PAXOSCLIENT_H
#define PAXOSCLIENT_H

//rpc client;
//use grpc stub;
class PaxosClient {
  public:
    PaxosClient(std::shared_ptr<StateMachine> pState);

    bool Prepare();
    bool Accept();
    bool Success();

    void AddPeer(const std::pair<uint32_t, std::string> &peer);
    void AddValue(const std::string &value);

    //Get means get a request from proposer
    //Set means set a reply from peer acceptor to proposer, update proposer state
    void GetPrepareRequest(PrepareRequest &request) {
      pProposer_->GetPrepareRequest(request);
    }
    void SetPrepareReply(const PrepareReply &reply) {
      pProposer_->SetPrepareReply(reply);
    }

    void GetSuccessRequest(SuccessRequest &request) {
      pProposer_->GetSuccessRequest(request);
    }
    void SetSuccessReply(const SuccessReply &reply) {
      pProposer_->SetSuccessReply(reply);
    }

    void GetAcceptRequest(AcceptRequest &request) {
      pProposer_->GetAcceptRequest(request);
    }
    void SetAcceptReply(const AcceptReply &reply) {
      pProposer_->SetAcceptReply(reply);
    }

    void SendPrepare(const PrepareRequest &request, PrepareReply &reply);
    void SendAccept(const AcceptRequest &request, AcceptReply &reply);
    void SendSuccess(const SuccessRequest &request, SuccessReply &reply);

  private:

    //uint32_t: NodeID, std::string: address
    std::map<uint32_t, std::string> peers_;
    // uint32_t: NodeID unique_ptr: Stub
    std::map<uint32_t, std::shared_ptr<Paxos::Stub> > stub_;
    std::unique_ptr<Proposer> pProposer_;

};

#endif

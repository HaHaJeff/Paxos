
#include "comdef.h"
#include "paxos_client.h">

#ifndef PROPOSER_H
#define PROPOSER_H


//TODO: need mutex?
//TODO: persist

class ProposerState {
  public:
    ProposerState() : maxRound_(0), nextIndex_(0), prepared_(false) {  }
    ~ProposerState() {  }

    void SetMaxRound(uint32_t round) { maxRound_ = round; }
    void IncMaxRound() { maxRound_ += 1; }
    uint32_t GetMaxRound() const { return maxRound_; }

    void SetNodeID(uint32_t nodeID) { nodeID_ = nodeID; }
    uint32_t GetNodeID() const { return nodeID_; }

    void SetNextIndex(uint32_t index) { nextIndex_ = index; }
    uint32_t GetNextIndex() const { return nextIndex_; }

    void SetFirstUnchosenIndex(uint32_t index) { firstUnchosenIndex_ = index; }
    uint32_t GetFirstUnchosenIndex() const { return firstUnchosenIndex_; }

    bool IsPrepared() { return prepared_; }
    void SetPrepared() { prepared_ = true; }
    void SetNotPrepared() { prepared_ = false; }

  private:
    uint32_t firstUnchosenIndex_;
    uint32_t maxRound_;
    uint32_t nextIndex_;
    uint32_t nodeID_;
    bool prepared_;
};

class Proposer {
  public:
    Proposer();
    ~Proposer();

    void SendPrepare(const PrepareRequest &request, PrepareReply &reply);
    void SendAccept(const AcceptRequest &request, AcceptReply &reply);
    void SendSuccess(const SuccessRequest &request, SuccessReply &reply);

  private:
    void NewPrepareRequest(PrepareRequest &request);
    void NewAcceptRequest(AcceptRequest &request);
    void NewSuccessRequest(SuccessRequest &request);

  private:
    ProposerState state_;
    std::vector<PaxosClient*> peers_;
};

#endif

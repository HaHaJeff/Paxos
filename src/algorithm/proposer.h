
#include "comdef.h"

#ifndef PROPOSER_H
#define PROPOSER_H


//TODO: need mutex?
//TODO: persist

class ProposerState {
  public:
    ProposerState(State *pState) : maxRound_(0), nextIndex_(0), prepared_(false), pState_(pState) {  }
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
    uint32_t nodeID_;        //暂时不用该属性
    bool prepared_;
    State *pState_;
};

class Proposer {
  public:
    Proposer(State *pState);
    ~Proposer();

    void SetPrepareReply(const PrepareReply &reply);
    void SetAcceptReply(const AcceptReply &reply);
    void SetSuccessReply(const SuccessReply &reply);

    void GetPrepareRequest(PrepareRequest &request);
    void GetAcceptRequest(AcceptRequest &request);
    void GetSuccessRequest(SuccessRequest &request);

  private:
    ProposerState state_;
};

#endif

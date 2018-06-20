#include "comdef.h"
#include "state.h"

#ifndef PROPOSER_H
#define PROPOSER_H


//TODO: need mutex?
//TODO: persist

class ProposerState {
  public:
    ProposerState(std::shared_ptr<StateMachine> pState) : maxRound_(0), index_(0), prepared_(false), pState_(pState) {  }
    ~ProposerState() {  }

    void SetMaxRound(uint32_t round) { maxRound_ = round; }
    void IncMaxRound() { maxRound_ += 1; }
    uint32_t GetMaxRound() const { return maxRound_; }

    void SetNodeID(uint32_t nodeID) { nodeID_ = nodeID; }
    uint32_t GetNodeID() const { return nodeID_; }

//    void SetNextIndex(uint32_t index) { nextIndex_ = index; }
//    uint32_t GetNextIndex() const { return nextIndex_; }

//    void SetFirstUnchosenIndex(uint32_t index) { firstUnchosenIndex_ = index; }
    uint32_t GetFirstUnchosenIndex() const { return pState_->GetFirstUnchosenIndex(); }

    //set highest proposal
    void SetPeerAcceptedProposal(const PrepareReply &entry);

    PrepareReply GetPeerAcceptedProposal(uint32_t instance) { return peerAcceptedProposal_[instance]; }

    bool IsPrepared() { return prepared_; }
    void SetPrepared() { prepared_ = true; }
    void SetNotPrepared() { prepared_ = false; }

    void AddToStateMachine(uint32_t index, const ProposalEntry &entry);
    void GetAcceptRequest(AcceptRequest &request, const std::string &value, uint32_t index, uint32_t firstUnchosenIndex);

    uint32_t Count(uint32_t index);

  private:
    uint32_t firstUnchosenIndex_;
    uint32_t maxRound_;
//   uint32_t nextIndex_;
    uint32_t index_;
    uint32_t nodeID_;        //暂时不用该属性
    bool prepared_;
    std::map<uint32_t, PrepareReply> peerAcceptedProposal_;
    std::map<uint32_t, uint32_t> count_;
    std::shared_ptr<StateMachine> pState_;
};

class Proposer {
  public:
    Proposer(std::shared_ptr<StateMachine> pState);
    ~Proposer();

    //仅仅只是为value分配一个可用的instance_id
    void Add(const std::string &value);

//    void Start();
//    void Stop();

    uint32_t Count(uint32_t index);
    void SetPrepareReply(const PrepareReply &reply);
    void SetAcceptReply(const AcceptReply &reply);
    void SetSuccessReply(const SuccessReply &reply);

    void GetPrepareRequest(PrepareRequest &request);
    void GetAcceptRequest(AcceptRequest &request);
    void GetSuccessRequest(SuccessRequest &request);

  private:
    ProposerState state_;
    //TODO: maybe prealloc instanceid may change, so when AddToMachine
    //is executed, we need to check instanceid whether is being chosen?
    std::map<uint32_t, std::string> toBeChosenValue_;
};

#endif

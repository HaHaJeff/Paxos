#include "comdef.h"
#include "state.h"

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

// Acceptro对于StateMachine应该是没有写权限的

class AcceptState {
  public:
    AcceptState(std::shared_ptr<StateMachine> pState);
    ~AcceptState();

    void SetLastLogIndex(uint32_t index) {
      lastLogIndex_ = index;
    }
    uint32_t GetLastLogIndex() const {
      return lastLogIndex_;
    }
    uint32_t GetFirstUnchosenIndex() const {
      return pState_->GetFirstUnchosenIndex();
    }

    void SetMinProposal(uint32_t index, uint32_t proposal);
    uint32_t GetMinProposal(uint32_t index_);

    //@return if success, return proposalID, else return -1
    uint32_t GetLogProposalID(uint32_t index);
    bool GetLogProposal(uint32_t index, ProposalEntry &proposal);
    bool GetLogValue(uint32_t index, std::string &value);
    void SetLogProposal(uint32_t index, const ProposalEntry &proposal);

    void UpdateChosenProposal(uint32_t proposal, uint32_t peerFirstUnchosenIndex);
    void AddToStateMachine(uint32_t index, const ProposalEntry &entry);

    void Print();

  private:
    void UpdateEntry(uint32_t index, const ProposalEntry &proposal);

  private:
    uint32_t lastLogIndex_;
    std::map<uint32_t, uint32_t> minProposal_;
    std::map<uint32_t, ProposalEntry> acceptedProposal_;
    std::shared_ptr<StateMachine> pState_;

    std::mutex mutex_;
};

class Acceptor {
  public:

    Acceptor(std::shared_ptr<StateMachine> pState);
    ~Acceptor();

    void RecvPrepare(const PrepareRequest &request, PrepareReply &reply);
    void RecvAccept(const AcceptRequest &request, AcceptReply &reply);
    void RecvSuccess(const SuccessRequest &request, SuccessReply &reply);

    void Print();

  private:
    AcceptState state_;
};

#endif

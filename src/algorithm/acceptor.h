#include <string>
#include <map>

#include "comdef.h"

#ifndef ACCEPTOR_H
#define ACCEPTOR_H


class AcceptState {
  public:
    AcceptState();
    ~AcceptState();

    void SetLastLogIndex(uint32_t index) {
      lastLogIndex_ = index;
    }
    uint32_t GetLastLogIndex() const {
      return lastLogIndex_;
    }
    void SetMinProposal(uint32_t proposal) {
      minProposal_ = proposal;
    }
    uint32_t GetMinProposal() const {
      return minProposal_;
    }

    bool GetLogProposal(uint32_t index, ProposalEntry &proposal);
    bool GetLogValue(uint32_t index, std::string &value);
    void SetLogProposal(uint32_t index, const ProposalEntry &proposal);

  private:
    void UpdateEntry(uint32_t index, const ProposalEntry &proposal);

  private:
    uint32_t lastLogIndex_;
    uint32_t minProposal_;
    uint32_t firstUnchosenIndex_;
    std::map<uint32_t, ProposalEntry> acceptedProposal_;


    //std::map<uint32_t, uint32_t> acceptedProposal_;
    //std::map<uint32_t, std::string> acceptedValue;

};

class Acceptor {
  public:
    Acceptor();
    ~Acceptor();

    void RecvPrepare(const PrepareRequest &request, PrepareReply &reply);
    void RecvAccept(const AcceptRequest &request, AcceptReply &reply);
    void RecvSuccess(const SuccessRequest &request, SuccessReply &reply);

  private:
    AcceptState state_;
};

#endif

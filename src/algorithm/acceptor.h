#include <string>
#include <map>

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

class AcceptState {
  public:

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


    bool IsChosen(uint32_t index) const {
      return acceptedProposal_[index] == -1;
    }

  private:
    uint32_t lastLogIndex_;
    uint32_t minProposal_;
    uint32_t firstUnchosenIndex_;
    std::map<uint32_t, uint32_t> acceptedProposal_;
    std::map<uint32_t, std::string> acceptedProposal_;

};

class Acceptor {
  public:
    Acceptor();
    ~Acceptor();

    void OnPrepare(const PrepareRequest &request, PrepareReply &reply);
    void OnAccpet(const AcceptRequest &request, AcceptReply &reply);
    void OnSuccess(const SuccessRequest &request, SuccessReply &reply);
}

#endif

#include <bitset>
#include "comdef.h"
#ifndef STATE_H
#define STATE_H

class StateMachine {
  public:
    StateMachine();
    bool AddToStateMachine(const LogEntry &entry);
    uint32_t GetFirstUnchosenIndex() const;
    std::string GetInstanceValue(uint32_t instance);

    void Print();

  private:
    bool Move();

    bool Insert(const LogEntry &entry);

    bool CanExecute() {
      return window_ == 0;
    }
    void UpdateFirstUnchosenIndex();

  private:
    static const uint32_t factor_ = 5;
    uint32_t window_;
    uint32_t firstIndexInThisWindow_;
    uint32_t firstUnchosenIndex_;
    std::bitset<factor_> chosenFlag_;
    std::map<uint32_t, ProposalEntry> chosenProposal_;

    std::mutex mutex_;
};

#endif

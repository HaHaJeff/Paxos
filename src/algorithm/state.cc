#include "state.h"


StateMachine::StateMachine() :
  window_(factor_), firstIndexInThisWindow_(0),
  firstUnchosenIndex_(0), chosenFlag_(0) {  }

bool StateMachine::AddToStateMachine(const LogEntry &entry) {
  if (window_ == 0) {
    return false;
  }
  std::lock_guard<std::mutex> lck(mtx_);
  if (window_ == 0) {
    return false;
  }
  chosenProposal_.insert(entry);
  chosenFlag_.set(entry.first % factor_);
  window_ -= 1;
  UpdateFirstUnchosenIndex();

  if (firstUnchosenIndex_ % factor_ == 0) {
    Move();
  }

  return true;
}

bool StateMachine::Move() {
  if (!CanExecute()) {
    return false;
  }
  firstIndexInThisWindow_ += factor_;
  window_ = factor_;
  chosenFlag_.reset();
  return true;
}

void StateMachine::UpdateFirstUnchosenIndex() {
  int i;
  for (i = 0; i < factor_; i++) {
    if(chosenFlag_[i] == false) {
      break;
    }
  }
  firstUnchosenIndex_ = i + firstIndexInThisWindow_;
}

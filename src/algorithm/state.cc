#include "state.h"

#include <iostream>

StateMachine::StateMachine() :
  window_(factor_), firstIndexInThisWindow_(0),
  firstUnchosenIndex_(0), chosenFlag_(0) {  }

bool StateMachine::AddToStateMachine(const LogEntry &entry) {
  //Double check
  if (window_ == 0) {
    return false;
  }
  std::lock_guard<std::mutex> lock(mutex_);
  if (window_ == 0) {
    return false;
  }
  //FIXME: bug: when insert option is error
  chosenProposal_.insert(entry);
  chosenFlag_.set(entry.first % factor_);
  window_ -= 1;
  UpdateFirstUnchosenIndex();

  if (firstUnchosenIndex_ % factor_ == 0) {
    Move();
  }

  return true;
}

uint32_t StateMachine::GetFirstUnchosenIndex() const {
  return firstUnchosenIndex_;
}

std::string StateMachine::GetInstanceValue(uint32_t instance) {
  return chosenProposal_[instance].second;
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


void StateMachine::Print() {
  std::cout << "**********StateMachine*********" << std::endl;
  std::cout << "bitset: " << chosenFlag_.to_string() << std::endl;
  std::cout << "firstUnchosenIndex: " << firstUnchosenIndex_ << std::endl;
  std::cout << "firstIndexInThisWindow: " << firstIndexInThisWindow_ << std::endl;
  std::cout << "item: " << std::endl;
  for (auto &iter: chosenProposal_) {
    std::cout << "log index: " << iter.first << "\t" <<
      "log value: " << iter.second.second << std::endl;
  }
  std::cout << "********************************" << std::endl;
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

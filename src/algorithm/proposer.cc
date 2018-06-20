#include "proposer.h"

void ProposerState::AddToStateMachine(uint32_t index, const ProposalEntry &entry) {
  LogEntry log(index, entry);
  pState_->AddToStateMachine(log);
}

void ProposerState::GetAcceptRequest(AcceptRequest &request, const std::string &value, uint32_t index, uint32_t firstUnchosenIndex) {
  request.set_instanceid(peerAcceptedProposal_[index].instanceid());
  request.set_nodeid(peerAcceptedProposal_[index].nodeid());
  request.set_proposalid(peerAcceptedProposal_[index].proposalid());
  request.set_value(peerAcceptedProposal_[index].value().empty() ? value: peerAcceptedProposal_[index].value());
  //firstunchosenindex或许已经更新过了，因为可能已经AddToStateMachine其他proposal了
  request.set_firstunchosenindex(firstUnchosenIndex);
}

//set highest proposal
void ProposerState::SetPeerAcceptedProposal(const PrepareReply &entry) {
  int instance = entry.instanceid();
  //means reject
  if (entry.proposalid() < peerAcceptedProposal_[instance].proposalid()) {
    return;
  }

  //means accept
  peerAcceptedProposal_[instance] = entry;
  count_[instance]++;
}

Proposer::Proposer(std::shared_ptr<StateMachine> pState) : state_(pState) {  }

Proposer::~Proposer() {  }

void Proposer::Add(const std::string &value) {

}

void Proposer::SetPrepareReply(const PrepareReply &reply) {
  state_.SetPeerAcceptedProposal(reply);
}

void Proposer::SetAcceptReply(const AcceptReply &reply) {

}

void Proposer::SetSuccessReply(const SuccessReply &reply) {

}

void Proposer::GetPrepareRequest(PrepareRequest &request) {
  request.set_instanceid(state_.GetFirstUnchosenIndex());
  request.set_nodeid(state_.GetNodeID());
  request.set_proposalid(state_.GetMaxRound());
  state_.IncMaxRound();
}

void Proposer::GetAcceptRequest(AcceptRequest &request) {
  std::string value = toBeChosenValue_[request.instanceid()];
  state_.GetAcceptRequest(request, value, request.instanceid(), state_.GetFirstUnchosenIndex());
}

void Proposer::GetSuccessRequest(SuccessRequest &request) {

}

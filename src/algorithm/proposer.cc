#include "proposer.h"

void ProposerState::AddToStateMachine(uint32_t index, const ProposalEntry &entry) {
  LogEntry log(index, entry);
  pState_->AddToStateMachine(log);
}

void ProposerState::GetAcceptRequest(AcceptRequest &request, uint32_t index, uint32_t firstUnchosenIndex) {
  request.set_instanceid(peerAcceptedProposal_[index].instanceid());
  request.set_nodeid(peerAcceptedProposal_[index].nodeid());
  request.set_proposalid(peerAcceptedProposal_[index].proposalid());
  request.set_value(peerAcceptedProposal_[index].value());
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

uint32_t ProposerState::Count(uint32_t index) {
  return count_[index];
}

void ProposerState::SetChosenProposal(uint32_t index, const ProposalEntry &entry) {
  AddToStateMachine(index, entry);
}

Proposer::Proposer(std::shared_ptr<StateMachine> pState) : state_(pState) {  }

Proposer::~Proposer() {  }

void Proposer::Add(const std::string &value) {
  Value v(0, value, TODO);
  toBeChosenValue_.push_back(v);
}

uint32_t Proposer::Count(uint32_t index) {
  return state_.Count(index);
}

void Proposer::SetPrepareReply(const PrepareReply &reply) {
  state_.SetPeerAcceptedProposal(reply);
}

void Proposer::SetAcceptReply(const AcceptReply &reply) {

  std::string value;
  std::for_each(toBeChosenValue_.begin(), toBeChosenValue_.end(), [reply, &value](Value &v){
      if (reply.instanceid() == v.instanceid && v.status == PENDING) {
      v.status = FINISHED;
      value = v.value;
      return;
      }
  });
  ProposalEntry entry(reply.proposalid(), value);
  state_.SetChosenProposal(reply.instanceid(), entry);
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

  state_.GetAcceptRequest(request, request.instanceid(), state_.GetFirstUnchosenIndex());

  if (request.value().empty()) {
    std::string value;
    std::for_each(toBeChosenValue_.begin(), toBeChosenValue_.end(), [request, &value](Value &v){
        if (v.status == TODO) {
        v.status = PENDING;
        v.instanceid = request.instanceid();
        value = v.value;
        return;
        }
        });
    request.set_value(value);
  }
}

void Proposer::GetSuccessRequest(SuccessRequest &request) {

}

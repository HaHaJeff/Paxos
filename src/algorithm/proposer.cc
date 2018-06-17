#include "proposer.h"

Proposer::Proposer() {  }

Proposer::~Proposer() {  }

void Proposer::SetPrepareReply(const PrepareReply &reply) {

}

void Proposer::SetAcceptReply(const AcceptReply &reply) {

}

void Proposer::SetSuccessReply(const SuccessReply &reply) {

}

void Proposer::GetPrepareRequest(PrepareRequest &request) {
  request.set_instanceid(state_.GetFirstUnchosenIndex());
  request.set_nodeid(state_.GetNodeID());
  request.set_proposalid(state_.GetMaxRound());
}

void Proposer::GetAcceptRequest(AcceptRequest &request) {
}

void Proposer::GetSuccessRequest(SuccessRequest &request) {

}

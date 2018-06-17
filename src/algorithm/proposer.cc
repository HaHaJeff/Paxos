#include "proposer.h"

Proposer::Proposer(State *pState) : state_(pState) {  }

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
  state_.IncMaxRound();
}

void Proposer::GetAcceptRequest(AcceptRequest &request) {
}

void Proposer::GetSuccessRequest(SuccessRequest &request) {

}

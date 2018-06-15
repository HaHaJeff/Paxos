#include "proposer.h"

Proposer::Proposer() {  }

Proposer::~Proposer() {  }

void Proposer::SendPrepare(const PrepareRequest &request, PrepareReply &reply) {

}

void Proposer::SendAccept(const AcceptRequest &request, AcceptReply &reply) {

}

void Proposer::SendSuccess(const SuccessRequest &request, SuccessReply &reply) {

}

void Proposer::NewPrepareRequest(PrepareRequest &request) {
  request.SetInstanceID(state_.GetFirstUnchosenIndex());
  request.SetNodeID(state_.GetNodeID());
  request.SetProposalID(state_.GetMaxRound());
}

void Proposer::NewAcceptRequest(AcceptRequest &request) {
}

void Proposer::NewSuccessRequest(SuccessRequest &request) {

}

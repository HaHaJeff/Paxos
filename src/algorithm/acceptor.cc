#include "acceptor.h"
#include <iterator>

AcceptState::AcceptState() : lastLogIndex_(0), minProposal_(0), firstUnchosenIndex_(0) {  }
AcceptState::~AcceptState() {  }

bool AcceptState::GetLogProposal(uint32_t index, ProposalEntry &proposal) {
  if(acceptedProposal_.find(index) == acceptedProposal_.end()) {
    return false;
  }
  proposal = acceptedProposal_[index];
  return true;
}
bool AcceptState::GetLogValue(uint32_t index, std::string &value) {
  if(acceptedProposal_.find(index) == acceptedProposal_.end()) {
    return false;
  }
  value = acceptedProposal_[index].second;
  return true;
}

void AcceptState::SetLogProposal(uint32_t index, const ProposalEntry &proposal) {
  UpdateEntry(index, proposal);
}

void AcceptState::UpdateEntry(uint32_t index, const ProposalEntry &proposal) {
  std::map<uint32_t, ProposalEntry>::iterator iter = acceptedProposal_.lower_bound(index);

  if(iter != acceptedProposal_.end() && !(acceptedProposal_.key_comp()(index, iter->first))) {
    iter->second = proposal;
  } else {
    acceptedProposal_.insert(iter, LogEntry(index, proposal));
  }
}

Acceptor::Acceptor() {  }

Acceptor::~Acceptor() {  }

void Acceptor::RecvPrepare(const PrepareRequest &request, PrepareReply &reply) {
  int index = request.instanceid();
  int proposal = request.proposalid();
  int minProposal = state_.GetMinProposal();

  reply.set_instanceid(index);
  reply.set_nodeid(1);

  std::string value = "";
  state_.GetLogValue(index, value);
  reply.set_value(value);

  reply.set_nomoreaccepted(false);

  //Accept
  if (proposal > state_.GetMinProposal()) {

    reply.set_proposalid(proposal);

    state_.SetMinProposal(proposal);
    state_.SetLogProposal(index, ProposalEntry(proposal, ""));
    state_.SetLastLogIndex(index);
  } else { //Reject

    reply.set_proposalid(minProposal);
  }

}

void Acceptor::RecvAccept(const AcceptRequest &request, AcceptReply &reply) {

}

void Acceptor::RecvSuccess(const SuccessRequest &request, SuccessReply &reply) {

}

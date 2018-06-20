#include "acceptor.h"
#include <iterator>

AcceptState::AcceptState(std::shared_ptr<StateMachine> pState) : lastLogIndex_(0), firstUnchosenIndex_(0), pState_(pState) {
}
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

void AcceptState::SetMinProposal(uint32_t index, uint32_t proposal) {
  std::map<uint32_t, uint32_t>::iterator iter = minProposal_.lower_bound(index);

  if (iter != minProposal_.end() && !(minProposal_.key_comp()(index, iter->first))) {
    iter->second = proposal;
  } else {
    minProposal_.insert(iter, std::make_pair(index, proposal));
  }
}

uint32_t AcceptState::GetMinProposal(uint32_t index) const {
  return 0;
}

void AcceptState::SetLogProposal(uint32_t index, const ProposalEntry &proposal) {
  UpdateEntry(index, proposal);
}

void AcceptState::UpdateChosenProposal(uint32_t proposal, uint32_t peerFirstUnchosenIndex) {
  for (int i = firstUnchosenIndex_; i < peerFirstUnchosenIndex; i++) {
    ProposalEntry entry;
    if (GetLogProposal(i, entry) && entry.first == proposal) {
      minProposal_[i] = PROPOSAL_MAX;
      AddToStateMachine(i, entry);
    }
  }
}

void AcceptState::UpdateEntry(uint32_t index, const ProposalEntry &proposal) {
  std::map<uint32_t, ProposalEntry>::iterator iter = acceptedProposal_.lower_bound(index);

  if(iter != acceptedProposal_.end() && !(acceptedProposal_.key_comp()(index, iter->first))) {
    iter->second = proposal;
  } else {
    acceptedProposal_.insert(iter, LogEntry(index, proposal));
  }
}

void AcceptState::AddToStateMachine(uint32_t index, const ProposalEntry &entry) {
  LogEntry log(index, entry);
  pState_->AddToStateMachine(log);
}

Acceptor::Acceptor(std::shared_ptr<StateMachine> pState) : state_(pState) {  }

Acceptor::~Acceptor() {  }

void Acceptor::RecvPrepare(const PrepareRequest &request, PrepareReply &reply) {
  int index = request.instanceid();
  int proposal = request.proposalid();
  int minProposal = state_.GetMinProposal(index);

  reply.set_instanceid(index);
  reply.set_nodeid(1);

  std::string value = "";
  state_.GetLogValue(index, value);
  reply.set_value(value);

  reply.set_nomoreaccepted(false);

  //Accept
  if (proposal > minProposal) {

    reply.set_proposalid(proposal);

    state_.SetMinProposal(index, proposal);

    //FIXME: the step is not need to do
    //state_.SetLogProposal(index, ProposalEntry(proposal, ""));

    //TODO: uncorrect in parallel commit
    state_.SetLastLogIndex(index);
  } else { //Reject

    reply.set_proposalid(minProposal);
  }
}

void Acceptor::RecvAccept(const AcceptRequest &request, AcceptReply &reply) {
  int index = request.instanceid();
  int proposal = request.proposalid();
  int minProposal = state_.GetMinProposal(index);
  std::string value = request.value();
  int peerFirstUnchosenIndex = request.firstunchosenindex();


  reply.set_instanceid(index);
  reply.set_nodeid(1);

  if (proposal > minProposal) {
    reply.set_proposalid(proposal);

    state_.SetMinProposal(index, proposal);
    state_.SetLogProposal(index, ProposalEntry(proposal, value));
    //TODO: uncorrect in parallel commit
    state_.SetLastLogIndex(index);

    // for every index < peerFirstUnchosenIndex, if proposal[index]
    state_.UpdateChosenProposal(proposal, peerFirstUnchosenIndex);

  } else {
    reply.set_proposalid(minProposal);
  }

}

void Acceptor::RecvSuccess(const SuccessRequest &request, SuccessReply &reply) {

}

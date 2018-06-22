#include "acceptor.h"
#include <iterator>

AcceptState::AcceptState(std::shared_ptr<StateMachine> pState) : lastLogIndex_(0), firstUnchosenIndex_(0), pState_(pState) {
}
AcceptState::~AcceptState() {  }

bool AcceptState::GetLogProposal(uint32_t index, ProposalEntry &proposal) {
  std::lock_guard<std::mutex> lock(mutex_);
  if(acceptedProposal_.find(index) == acceptedProposal_.end()) {
    return false;
  }
  proposal = acceptedProposal_[index];
  return true;
}
bool AcceptState::GetLogValue(uint32_t index, std::string &value) {
  std::lock_guard<std::mutex> lock(mutex_);
  if(acceptedProposal_.find(index) == acceptedProposal_.end()) {
    return false;
  }
  value = acceptedProposal_[index].second;
  return true;
}

void AcceptState::SetMinProposal(uint32_t index, uint32_t proposal) {
  std::lock_guard<std::mutex> lock(mutex_);
  std::map<uint32_t, uint32_t>::iterator iter = minProposal_.lower_bound(index);

  if (iter != minProposal_.end() && !(minProposal_.key_comp()(index, iter->first))) {
    minProposal_.insert(iter, std::make_pair(index, proposal));
  } else {
    iter->second = proposal;
  }
}

uint32_t AcceptState::GetMinProposal(uint32_t index) {
  std::lock_guard<std::mutex> lock(mutex_);
  std::map<uint32_t, uint32_t>::iterator iter = minProposal_.lower_bound(index);
  uint32_t minProposal = 0;
  if (iter != minProposal_.end() && !(minProposal_.key_comp()(index, iter->first))) {
    minProposal = 0;
  } else {
    minProposal = iter->second;
  }
  return minProposal;
}

void AcceptState::SetLogProposal(uint32_t index, const ProposalEntry &proposal) {
  UpdateEntry(index, proposal);
}

void AcceptState::UpdateChosenProposal(uint32_t proposal, uint32_t peerFirstUnchosenIndex) {
  std::lock_guard<std::mutex> lock(mutex_);
  for (int i = firstUnchosenIndex_; i < peerFirstUnchosenIndex; i++) {
    ProposalEntry entry;
    if (GetLogProposal(i, entry) && entry.first == proposal) {
      minProposal_[i] = PROPOSAL_MAX;
      AddToStateMachine(i, entry);
    }
  }
}

void AcceptState::UpdateEntry(uint32_t index, const ProposalEntry &proposal) {
  std::lock_guard<std::mutex> lock(mutex_);
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

void AcceptState::Print() {
  std::cout << "********AcceptState********" << std::endl;

  std::cout << "MinProposal: ";
  std::for_each(minProposal_.begin(), minProposal_.end(), [](auto &p) {
      std::cout << "instance: " << p.first << "\t" << "minProposal: " << p.second << std::endl;
      });
  std::cout << std::endl;

  std::cout << "AcceptedProposal: ";
  std::for_each(acceptedProposal_.begin(), acceptedProposal_.end(), [](auto &p) {
      std::cout << "instance: " << p.first << "\t" << "proposal id: " << p.second.first << " value: " << p.second.second << std::endl;
      });
  std::cout << std::endl;

  std::cout << "***************************" << std::endl;

  pState_->Print();
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
  if (proposal >= minProposal) {

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

  if (proposal >= minProposal) {
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

void Acceptor::Print() {
  state_.Print();
}

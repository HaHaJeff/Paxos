#include "paxos_service.h"

PaxosService::PaxosService(std::shared_ptr<StateMachine> pState) : pAcceptor_(new Acceptor(pState)) {

}

Status PaxosService::OnPrepare(ServerContext *context, const PrepareRequest *request, PrepareReply *reply) {
  std::cout << "OnPrepare: " << std::endl;
  pAcceptor_->RecvPrepare(*request, *reply);
  pAcceptor_->Print();
  return Status::OK;
}

Status PaxosService::OnAccept(ServerContext *context, const AcceptRequest *request, AcceptReply *reply) {
  std::cout << "OnAccept: " << std::endl;
  pAcceptor_->RecvAccept(*request, *reply);
  pAcceptor_->Print();
  return Status::OK;
}

Status PaxosService::OnSuccess(ServerContext *context, const SuccessRequest *request, SuccessReply *reply) {
  std::cout << "OnSuccess: " << std::endl;
  pAcceptor_->RecvSuccess(*request, *reply);
  pAcceptor_->Print();
  return Status::OK;
}


#include "paxos_service.h"

PaxosService::PaxosService(std::shared_ptr<StateMachine> pState) : pAcceptor_(new Acceptor(pState)) {

}

Status PaxosService::OnPrepare(ServerContext *context, const PrepareRequest *request, PrepareReply *reply) {
  pAcceptor_->RecvPrepare(*request, *reply);
  return Status::OK;
}

Status PaxosService::OnAccept(ServerContext *context, const AcceptRequest *request, AcceptReply *reply) {
  pAcceptor_->RecvAccept(*request, *reply);
  return Status::OK;
}

Status PaxosService::OnSuccess(ServerContext *context, const SuccessRequest *request, SuccessReply *reply) {
  pAcceptor_->RecvSuccess(*request, *reply);
  return Status::OK;
}


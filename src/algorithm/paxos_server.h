#include "comdef.h"
#include "acceptor.h"


#ifndef PAXOS_SERVER_H
#define PAXOS_SERVER_H

class PaxosServer final : public Service{
  public:
    Status OnPrepare(ServerContext *context, const PrepareRequest *request,
        PrepareReply *reply) override {
      pAcceptor_->RecvPrepare(*request, *reply);
      return Status::OK;
    }

    Status OnAccept(ServerContext *context, const AcceptRequest *request,
        AcceptReply *reply) override {
      pAcceptor_->RecvAccept(*request, *reply);
      return Status::OK;
    }

    Status OnSuccess(ServerContext *context, const SuccessRequest *request,
        SuccessReply *reply) override {
      pAcceptor_->RecvSuccess(*request, *reply);
      return Status::OK;
    }
  private:
    std::shared_ptr<Acceptor> pAcceptor_;
};

#endif

#include "comdef.h"
#include "acceptor.h"
#include <grpcpp/grpcpp.h>

#ifndef PAXOS_SERVICE_H
#define PAXOS_SERVICE_H

using grpc::Status;
using grpc::ServerContext;

class PaxosService final : public Paxos::Service {
  public:
    PaxosService();

    Status OnPrepare(ServerContext *context, const PrepareRequest *request,
        PrepareReply *reply) override;

    Status OnAccept(ServerContext *context, const AcceptRequest *request,
        AcceptReply *reply) override;

    Status OnSuccess(ServerContext *context, const SuccessRequest *request,
        SuccessReply *reply) override;
  private:
    std::unique_ptr<Acceptor> pAcceptor_;
};

#endif

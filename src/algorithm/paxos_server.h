#include "comdef.h"
#include "paxos_service.h"

#ifndef PAXOS_SERVER_H
#define PAXOS_SERVER_H

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class PaxosServer {
  public:
    PaxosServer(const std::string &address, std::shared_ptr<StateMachine> pState);
    ~PaxosServer();
    void Start();
    void Stop();
  private:
    PaxosService service_;
    bool started_;
    std::string address_;
    std::unique_ptr<Server> server_;
};

#endif

#include "paxos_server.h"

PaxosServer::PaxosServer(const std::string &address, std::shared_ptr<StateMachine> pState) :
  service_(pState), started_(false), address_(address) {  }

PaxosServer::~PaxosServer() {
  if(started_) {
    Stop();
  }
}

void PaxosServer::Start() {
  if (started_) {
    return;
  }

  ServerBuilder builder;
  builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
  builder.RegisterService(&service_);
  server_ = builder.BuildAndStart();
  std::cout << "Server listening on " << address_ << std::endl;
  server_->Wait();

}

void PaxosServer::Stop() {

}

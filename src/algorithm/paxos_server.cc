#include "paxos_server.h"

PaxosServer::PaxosServer(const std::string &address) : started_(false), address_(address) {  }

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
  std::cout << "Server listening on " << address_ << std::endl;
  server_->Wait();

}

void PaxosServer::Stop() {

}

#ifndef COMMDEF_H
#define COMMDEF_H


#include "rpc.pb.h"
#include "rpc.grpc.pb.h"

typedef std::pair<uint32_t, std::string> ProposalEntry ;
typedef std::pair<uint32_t, ProposalEntry> LogEntry;

#endif

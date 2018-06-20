#ifndef COMMDEF_H
#define COMMDEF_H

#include <map>
#include <string>
#include <memory>
#include <functional>
#include <grpcpp/grpcpp.h>
#include <limits>

#include "rpc.pb.h"
#include "rpc.grpc.pb.h"

#define PROPOSAL_MAX (std::numeric_limits<uint32_t>::max())

typedef std::pair<uint32_t, std::string> ProposalEntry;
typedef std::pair<uint32_t, ProposalEntry> LogEntry;

#endif

CXX = g++
CXXFLAGS += -g -std=c++11 -I../algorithm
LDFLAGS += -L /usr/local/lib `pkg-config --libs protobuf grpc++ grpc`

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

OBJ_DIR = ../objs

PROTO_PATH = ../../proto

vpath %.proto $(PROTO_PATH)

PROTO_OUT = ./

all: test_acceptor test_proposer test_state

main: main.o rpc.pb.o rpc.grpc.pb.o
	@echo $^ "====>" $@
	$(CXX) $^ $(LDFLAGS) -o $@

test_acceptor: test_acceptor.o $(OBJ_DIR)/acceptor.o $(OBJ_DIR)/rpc.pb.o $(OBJ_DIR)/rpc.grpc.pb.o
	@echo $^ "====>" $@
	$(CXX) $^ $(LDFLAGS) -o $@

test_proposer: test_proposer.o $(OBJ_DIR)/proposer.o $(OBJ_DIR)/rpc.pb.o $(OBJ_DIR)/rpc.grpc.pb.o
	@echo $^ "====>" $@
	$(CXX) $^ $(LDFLAGS) -o $@

test_state: test_state.o $(OBJ_DIR)/state.o $(OBJ_DIR)/rpc.pb.o $(OBJ_DIR)/rpc.grpc.pb.o
	@echo $^ "====>" $@
	$(CXX) $^ $(LDFLAGS) -o $@
: 
#demo_server: demo.pb.o demo.grpc.pb.o demo_server.o
#	@echo $^ "====>" $@
#	$(CXX) $^ $(LDFLAGS) -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTO_PATH) --grpc_out=$(PROTO_OUT) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTO_PATH) --cpp_out=$(PROTO_OUT) $<

clean:
	@rm -rf *.pb.cc *.pb.h *.o test_acceptor test_proposer test_state


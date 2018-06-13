CXX = g++
CXXFLAGS += -g -std=c++11
LDFLAGS += -L /usr/local/lib `pkg-config --libs protobuf grpc++ grpc`

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTO_PATH = ../../proto

PROTO_OUT = ./

all: main

main: main.o rpc.pb.o rpc.grpc.pb.o
	@echo $^ "====>" $@
	$(CXX) $^ $(LDFLAGS) -o $@

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
	@rm -rf *.pb.cc *.pb.h *.o main


CXX = g++
CXXFLAGS += -g -std=c++14
LDFLAGS += -L /usr/local/lib `pkg-config --libs protobuf grpc++ grpc`


PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

SRCS=${wildcard *.cc}
OBJS=$(patsubst %.cc, %.o, $(SRCS))

PROTO_PATH = ../../proto

PROTO_OUT = .

all: $(OBJS) move 

$(OBJ): %.o: %.cc
	@echo $< "====>" $@
	$(CXX) $< $(LDFLAGS) -o $@

move:
	@mv *.o ../objs

#.PRECIOUS: %.grpc.pb.cc
#	%.grpc.pb.cc: %.proto
#	$(PROTOC) -I $(PROTO_PATH) --grpc_out=$(PROTO_OUT) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

#.PRECIOUS: %.pb.cc
#	%.pb.cc: %.proto
#	$(PROTOC) -I $(PROTO_PATH) --cpp_out=$(PROTO_OUT) $<

clean:
	@rm -rf *.pb.cc *.pb.h *.o

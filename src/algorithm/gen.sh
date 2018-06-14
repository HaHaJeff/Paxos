#!/bin/bash
protoc -I ../../proto/ --grpc_out=./ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` rpc.proto
protoc -I ../../proto/ --cpp_out=./ rpc.proto

#!/bin/sh

SRC_DIR=./
DST_DIR=./
protoc -I=$SRC_DIR  --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto
echo protoc -I=$SRC_DIR  --cpp_out=$DST_DIR ${SRC_DIR}addressbook.proto

protoc -I=$SRC_DIR  --cpp_out=$DST_DIR $SRC_DIR/info.proto
echo protoc -I=$SRC_DIR  --cpp_out=$DST_DIR ${SRC_DIR}info.proto

protoc -I=$SRC_DIR  --cpp_out=$DST_DIR $SRC_DIR/loop_message.proto
echo protoc -I=$SRC_DIR  --cpp_out=$DST_DIR $SRC_DIR/loop_message.proto

# read and write
#写操作
g++ addressbook.pb.cc writer.cpp -o writer -lprotobuf -lpthread
echo g++ addressbook.pb.cc writer.cpp -o writer -lprotobuf -lpthread

#读操作
g++ addressbook.pb.cc reader.cpp -o reader -lprotobuf -lpthread
echo g++ addressbook.pb.cc reader.cpp -o reader -lprotobuf -lpthread

#序列化
g++ info.pb.cc protobuf_serialize.cpp -o serialize -lprotobuf -lpthread
echo g++ info.pb.cc protobuf_serialize.cpp -o serialize -lprotobuf -lpthread

#message嵌套
g++ loop_message.cpp loop_message.pb.cc -o loop_message -lprotobuf -lpthread
echo g++ loop_message.cpp loop_message.fb.h -o loop_message -lprotobuf -lpthread

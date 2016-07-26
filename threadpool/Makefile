#--------------------------------------------------------------------
ifeq ($(GCOV_ON),1)
GCOV= -ftest-coverage -fprofile-arcs -lgcov
endif

CC = gcc
CXX = g++
AR = ar cru
CFLAGS = -Wall -D_REENTRANT -D_GNU_SOURCE -g -fPIC $(GCOV)
SOFLAGS = -shared

INC = inc
SYSINC = /home/w/include
SRC = src
LIB = lib
BIN = bin
TEST = test
TESTR = testr

INCFLAGS = -I$(INC) -I$(SYSINC)

CFLAGS += $(INCFLAGS)

LDFLAGS = -L/home/w/lib64/ -lpthread -lgtest_main -lgtest $(GCOV)

LIBTHREADPOOL = libthreadpool
LIBTHREADPOOL_A = $(LIB)/$(LIBTHREADPOOL).a
LIBTHREADPOOL_SO = $(LIB)/$(LIBTHREADPOOL).so
TESTEXE = $(BIN)/threadpool_test

#--------------------------------------------------------------------

LIBOBJS =  			        \
	$(SRC)/TP_ThreadPool.o          \
	$(SRC)/TP_Time.o                \
	$(SRC)/TP_Threads.o             \
	$(SRC)/TP_Lock.o                \
	$(SRC)/TP_Worker.o              \
	$(SRC)/TP_Task.o                \
	$(SRC)/TP_Executor.o

TESTOBJS =                               \
        $(TEST)/TP_TaskTest.o            \
        $(TEST)/TP_WorkerTest.o          \
        $(TEST)/TP_ExecutorTest.o	 \
	$(TEST)/TP_ThreadPoolTest.o

TARGET =                                \
	$(LIBTHREADPOOL_A)              \
	$(LIBTHREADPOOL_SO)             \
	$(TESTEXE)

#--------------------------------------------------------------------
.PHONY: all clean $(TARGET) $(LIBTHREADPOOL_SO) $(LIBTHREADPOOL_A) install $(TESTEXE) $(TESTR)

all: $(TARGET) $(TESTEXE) $(TESTR) 

$(LIBTHREADPOOL_SO): $(LIBOBJS)
	$(CXX) $(SOFLAGS) $^ -o $@

$(LIBTHREADPOOL_A): $(LIBOBJS)
	$(AR) $@ $^

$(TESTEXE): $(TESTOBJS) $(LIBOBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(TESTR):
	exec $(TESTEXE)  --gtest_output=xml:test-output/threadpool_test.xml


install:
	cp -rf $(LIB)/* /home/w/lib64/
	mkdir -p /home/w/include/threadpool/
	cp -rf $(INC)/* /home/w/include/threadpool/

clean:
	@rm -rf  $(LIBOBJS) $(TESTOBJS) $(TARGET) test-output/*

#--------------------------------------------------------------------

# make rule

%.o : %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@
	
%.o : %.cc
	$(CXX) $(CFLAGS) -c $^ -o $@	

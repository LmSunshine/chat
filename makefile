ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
DATA_POOL=$(ROOT_PATH)/data_pool
LIB=$(ROOT_PATH)/lib
CONF=$(ROOT_PATH)/conf
PLUGIN=$(ROOT_PATH)/plugin
CHAT_WINDOW=$(ROOT_PATH)/chat_window


SERVER_BIN=udp_server
CLIENT_BIN=udp_client

INCLUDE=-I$(COMM) -I$(DATA_POOL) -I$(LIB)/include -I$(CHAT_WINDOW)
LIB_JSON=-L$(LIB)/lib 
CC=g++
FLAGS=#-D_DEBUG__
LDFLAGS=-ljsoncpp -lpthread #-static 

SER_SRC=$(shell ls -R $(SERVER) | grep -E '*\.cpp')
SER_SRC+=$(shell ls -R $(COMM) |grep -E '*\.cpp')
SER_SRC+=$(shell ls -R $(DATA_POOL) |grep -E '*\.cpp')
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls -R $(CLIENT) | grep -E '*\.cpp')
CLI_SRC+=$(shell ls -R $(COMM) | grep -E '*\.cpp')
CLI_SRC+=$(shell ls -R $(CHAT_WINDOW) | grep -E '*\.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SER_OBJ)
	@$(CC) -o $@ $^ $(LIB_JSON) $(LDFLAGS)
	@echo "Linking [ $^ ] to [ $@ ] ...done."
$(CLIENT_BIN):$(CLI_OBJ) 
	@$(CC) -o $@ $^ $(LIB_JSON) $(LDFLAGS) -lncurses# -static 
	@echo "Linking [ $^ ] to [ $@ ] ...done."

%.o:$(COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
#@echo "Compling [ $< ] to [ $@ ] ...done."
	@echo "Compling [ $(shell basename $<) ] to [ $@ ] ...done."
%.o:$(SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
#@echo "Compling [ $< ] to [ $@ ] ...done."
	@echo "Compling [ $(shell basename $<) ] to [ $@ ] ...done."
%.o:$(CHAT_WINDOW)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
#@echo "Compling [ $< ] to [ $@ ] ...done."
	@echo "Compling [ $(shell basename $<) ] to [ $@ ] ...done."
%.o:$(DATA_POOL)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(LDFLAGS)
#@echo "Compling [ $< ] to [ $@ ] ...done."
	@echo "Compling [ $(shell basename $<) ] to [ $@ ] ...done."
%.o:$(CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
#@echo "Compling [ $< ] to [ $@ ] ...done."
	@echo "Compling [ $(shell basename $<) ] to [ $@ ] ...done."

.PHONY:	clean
clean:
	@rm -f *.o $(SERVER_BIN) $(CLIENT_BIN)
	@echo "clean... done."
.PHONY:debug
debug:
	@echo $(SER_SRC)
	@echo $(SER_OBJ)
	@echo $(CLI_SRC)
	@echo $(CLI_OBJ)

	


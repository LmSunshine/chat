ROOT_PATH=$(shell pwd)
INCLUDE=-I$(ROOT_PATH)/lib/include
LIB=-L$(ROOT_PATH)/lib

udp_data:udp_data.o my_json.o
	g++ -o $@ $^ $(LIB) -ljsoncpp

%.o:%.cpp
	g++ -c $< $(INCLUDE) -D_DEBUG_ 

.PHONY:clean
clean:
	rm -f udp_data *.o


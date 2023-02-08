all:
	g++ -o reader ./src/CAN_reader.cpp
	g++ -o send ./src/CAN_send.cpp

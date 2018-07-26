all:
	g++ -I. main.cpp -o main -std=c++11 -O2 -lpthread -ldl
	g++ -I. get_thread_name.cpp -o gtn -std=c++11 -O2 -lpthread -ldl


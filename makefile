CC = gcc
CXX = g++
CXX-FLAG = -g --std=c++17

test:
	$(CXX) testcc.cc $(CXX-FLAG)
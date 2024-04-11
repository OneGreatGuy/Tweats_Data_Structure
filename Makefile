CC=g++
C_FLAGS=-g -std=c++17 -Wall -Wextra

all: run_app

run_app: 
	$(CC) $(C_FLAGS) main.cpp minHeapify.cpp hash.cpp bst.cpp -o run_app
	
run_small: run_app
	./run_app datasets/test.csv

run_big: run_app
	./run_app datasets/tweets-data_smol.csv
	
clean:
	rm run_app



all:
	g++ -std=c++0x *.cpp -o process
run:
	./process
clean:
	rm process
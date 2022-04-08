run : simu
	./simu

simu: simu.cpp
	g++ -Wall -o simu simu.cpp -lm

clean:
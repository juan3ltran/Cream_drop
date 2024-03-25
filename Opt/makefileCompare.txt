compare:
	g++ -c mainCompare.cpp utils.cpp
	g++ mainCompare.o utils.o -o main.x
	./main.x 
	#python3 graficadores/punto1.py

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -f *.o *.x *.dat 
	rm -rf data/*.dat
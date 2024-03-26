run:
	g++ -c main.cpp utils.cpp
	g++ main.o utils.o -o main.x
	./main.x > data.dat

plot: data.dat
	python3 plot.py

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -f *.o *.x *.dat 
	rm -rf data/*.dat
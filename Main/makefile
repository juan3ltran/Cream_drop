# Definir el compilador
CC=g++

# Opciones de compilación por defecto
CFLAGS = -O3 -fsanitize=address -fsanitize=undefined -fsanitize=leak
GPROFFLAGS = -Wall -pg -g
CATCHFLAGS = -l Catch2Main -l Catch2
MEMCHECKFLAGS = --tool=memcheck --leak-check=yes
CACHEGRINDFLAGS =  --tool=cachegrind
# Nombre del archivo de salida
TARGET=plot

# Archivos objeto
OBJ=utils.o

# Compilar y ejecutar el target por defecto
all: $(TARGET) 

# Compila los archivos fuente en objetos
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el programa principal
run: $(TARGET)
	./$(TARGET)

# Nuevo objetivo para punto2
punto1.x: punto1.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto1.x
	./punto1.x ./inputs/input.txt

punto2.x: punto2.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto2.x
	./punto2.x > data/punto2.dat

punto4.x: punto4.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto4.x
	./punto4.x > data/punto4.dat

# Graficar los resultados
plot: punto1.x punto2.x punto4.x
	python3 graficadores/graficador_1.py data/punto1.dat
	python3 graficadores/graficador_2.py data/punto2.dat
	python3 graficadores/graficador_4.py data/punto4.dat

cachegrind:
	$(CC) -g -c -O3 punto1.cpp utils.cpp
	$(CC) -g -O3 punto1.o utils.o -o punto1.x 
	valgrind $(CACHEGRINDFLAGS) ./punto1.x ./inputs/input.txt
	cg_annotate --auto=yes cachegrind.out.* > cachegrind-report.txt
	rm *.o *.x cachegrind.out.*

memcheck: 
	$(CC) -g -c -O3 punto1.cpp utils.cpp
	$(CC) -g -O3 punto1.o utils.o -o punto1.x 
	valgrind $(MEMCHECKFLAGS) ./punto1.x ./inputs/input.txt
	rm *.o *.x

gprof: 
	$(CC) $(GPROFFLAGS) -c punto1.cpp utils.cpp
	$(CC) $(GPROFFLAGS) punto1.o utils.o -o gprof_report.x
	./gprof_report.x ./inputs/input-profiling.txt
	gprof gprof_report.x gmon.out > gprof-report.txt
	rm gmon.out *.o *.x

test: test.cpp utils.cpp
	$(CC) -c  $(CATCHFLAGS)
	$(CC) test.o $(OBJ) -o test.x $(CATCHFLAGS) 
	./test.x
	rm *.o 
.PHONY: clean
clean:
	rm -f *.o *.x *.dat *.out *.txt
	rm -f data/*.dat
	rm -f graficas/*.pdf
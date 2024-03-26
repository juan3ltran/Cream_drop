# Definir el compilador
CC=g++

# Opciones de compilación por defecto
CFLAGS = -O3 -fsanitize=address -fsanitize=undefined -fsanitize=leak
GPROFFLAGS= -Wall -pg -g

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
	./punto1.x ./inputs/input1.txt

punto2.x: punto2.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto2.x
	./punto2.x > data/punto2.dat

# punto4.x: punto4.o $(OBJ)
# 	$(CC) $(CFLAGS) $^ -o $>
# 	./punto4.x > data/punto4.dat

# Graficar los resultados
plot: punto1.x punto2.x
	python3 graficadores/graficador_1.py data/punto1.dat
	python3 graficadores/graficador_2.py data/punto2.dat

gprof: 
	$(CC) $(GPROFFLAGS) -c punto1.cpp utils.cpp
	$(CC) $(GPROFFLAGS) punto1.o utils.o -o gprof_report.x
	./gprof_report.x ./inputs/input-profiling.txt
	gprof gprof_report.x gmon.out > gprof-report.txt
	rm gmon.out *.o *.x

.PHONY: clean
clean:
	rm -f *.o *.x *.dat *.out *.txt
	rm -f data/*.dat
	rm -f graficas/*.pdf

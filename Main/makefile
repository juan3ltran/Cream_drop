# Definir el compilador
CC=g++

# Opciones de compilación por defecto
CFLAGS = -O3 -fsanitize=address -fsanitize=undefined -fsanitize=leak
GPROFFLAGS = -Wall -pg -g
CATCHFLAGS = -l Catch2Main -l Catch2
MEMCHECKFLAGS = --tool=memcheck --leak-check=yes
CACHEGRINDFLAGS =  --tool=cachegrind
# Nombre del archivo de salida
TARGET=main.x

# Archivos objeto
OBJ=utils.o

# Compilar y ejecutar el target por defecto
all: $(TARGET) 

# Compila los archivos fuente en objetos
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el programa principal
main.x: main.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o main.x
	./main.x<./inputs/input.txt
# Nuevo objetivo para punto2
punto1.x: punto1.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto1.x
	./punto1.x<./inputs/input_punto1.txt>data/punto1.dat

punto2.x: punto2.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto2.x
	./punto2.x > data/punto2.dat

punto3.x: punto3.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto3.x
	./punto3.x > data/punto3.dat

punto4.x: punto4.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o punto4.x
	./punto4.x > data/punto4.dat

t_computo.x:
	@echo "\n Esto puede tardar aproximadamente 30 minutos \n"
	$(CC) -g -c t_computo.cpp utils.cpp
	$(CC) -g t_computo.o utils.o -o t_computo.x 
	./t_computo.x no3
	
	$(CC) -g -c -O3 t_computo.cpp utils.cpp
	$(CC) -g -O3 t_computo.o utils.o -o t_computo.x 
	./t_computo.x o3

# Graficar los resultados
plot: punto1.x punto2.x punto3.x punto4.x t_computo.x
	python3 graficadores/graficador_1.py data/punto1.dat
	python3 graficadores/graficador_2.py data/punto2.dat
	python3 graficadores/graficador_3.py data/punto3.dat
	python3 graficadores/graficador_4.py data/punto4.dat
	python3 graficadores/graficador_tcomp.py
	rm -r *.o 

cachegrind:
	$(CC) -g -c -O3 main.cpp utils.cpp
	$(CC) -g -O3 main.o utils.o -o main.x 
	valgrind $(CACHEGRINDFLAGS) ./main.x<./inputs/input.txt>temp.dat
	cg_annotate --auto=yes cachegrind.out.* > cachegrind-report.txt
	rm *.o *.x cachegrind.out.* temp.dat

memcheck: 
	$(CC) -g -c -O3 main.cpp utils.cpp
	$(CC) -g -O3 main.o utils.o -o main.x 
	valgrind $(MEMCHECKFLAGS) ./main.x<./inputs/input.txt>temp.dat
	rm *.o *.x temp.dat

gprof: 
	$(CC) $(GPROFFLAGS) -c main.cpp utils.cpp
	$(CC) $(GPROFFLAGS) main.o utils.o -o gprof_report.x
	./gprof_report.x <./inputs/input-profiling.txt>temp.dat
	gprof gprof_report.x gmon.out > gprof-report.txt
	rm gmon.out *.o *.x temp.dat

test: test.cpp utils.cpp
	$(CC) -c  $(CATCHFLAGS) $^
	$(CC) test.o $(OBJ) -o test.x $(CATCHFLAGS) 
	./test.x
	rm *.o 
.PHONY: clean
clean:
	rm -f *.o *.x *.out
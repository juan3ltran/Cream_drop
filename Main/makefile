# Definir el compilador
CC=g++

# Opciones de compilación por defecto
CFLAGS=-fsanitize=address -fsanitize=undefined -fsanitize=leak

# Nombre del archivo de salida
TARGET=main.x

# Archivos objeto
OBJ=main.o utils.o

# Compilar y ejecutar el target por defecto
all: $(TARGET) run plot

# Enlaza los objetos para crear el ejecutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Compila los ejecutables
%.x: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Compila los archivos fuente en objetos
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el programa principal
run: $(TARGET)
	./$(TARGET)

# Graficar los resultados
plot:
	python3 graficadores/graficador.py data/punto1.dat

.PHONY: clean
clean:
	rm -f *.o *.x *.dat 
	rm -rf data/*.dat
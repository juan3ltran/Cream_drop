# Definir el compilador
CC=g++

# Opciones de compilación por defecto
CFLAGS=

# Sanitizers
SANITIZE_FLAGS=-fsanitize=address -fsanitize=undefined -fsanitize=leak

# Nombre del archivo de salida por defecto
TARGET=walk.x

# Ruta del archivo de datos de salida por defecto
DATAPATH=datos_prueba/comparacion_entropias.dat

# Compilar y ejecutar el target por defecto
all: CFLAGS += $(SANITIZE_FLAGS)
all: $(TARGET) run plot

# Enlaza los objetos para crear el ejecutable
$(TARGET): walk.o entropia_h.o
	$(CC) $(CFLAGS) $^ -o $@

# Compila los archivos fuente en objetos
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el programa principal
run:
	./$(TARGET) > $(DATAPATH)

# Graficar los resultados
plot:
	python3 graficador.py $(DATAPATH)

# Compilar y ejecutar tests o pruebas
test: CFLAGS += $(SANITIZE_FLAGS)
test: test.x
	./test.x

prueba: CFLAGS += $(SANITIZE_FLAGS)
prueba: prueba.x
	./prueba.x

.PHONY: clean
clean:
	rm -f *.o *~ *.x *.out

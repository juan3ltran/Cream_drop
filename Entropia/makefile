# Definir el compilador
CC=g++

# Opciones de compilación, por ejemplo, para incluir símbolos de depuración se puede añadir -g
CFLAGS=

# Nombre del archivo de salida
TARGET=walk.x

# Ruta del archivo de datos de salida
DATAPATH=datos_prueba/caminador.dat

all: $(TARGET) run plot

$(TARGET): walk.cpp
	$(CC) $(CFLAGS) walk.cpp -o $(TARGET)

run:
	./$(TARGET) > $(DATAPATH)

plot:
	python3 graficador.py $(DATAPATH)



.PHONY: clean
clean:
	rm -f *.o *~ *.x *.out 
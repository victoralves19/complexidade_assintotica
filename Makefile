CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11
TARGET = main

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	python3 graficos.py

clean:
	rm -f $(TARGET) tempos_execucao.csv grafico_busca.png grafico_ordenacao.png
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS  = -static

FONTES = matriz.cpp lu.cpp ldp.cpp entrada_saida.cpp

all: foguete teste

foguete: main.cpp $(FONTES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

teste: teste_gabarito.cpp $(FONTES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

run-teste: teste
	./teste

verificar: foguete
	@ldd foguete 2>&1 | grep -q "not a dynamic executable" && echo "OK: executável estático" || echo "ATENÇÃO: executável dinâmico"

clean:
	rm -f foguete teste

.PHONY: all run-teste verificar clean

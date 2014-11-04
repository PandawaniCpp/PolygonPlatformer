# Makefile gry #TITLE
# 	data: 04.11
# 
# Każdy nowy plik z rozszerzeniem .cpp trzeba dołączyć do zmiennej OBJECTS z rozszerzeniem .o

OBJECTS=Source.o

CXX=g++ -std=c++11
CFLAGS=-Wall -pedantic
LFLAGS=-lsfml-system -lsfml-graphics -lsfml-window -lBox2D
EXEC=Project.o

# Finalny projekt wykonywalny
$(EXEC): $(OBJECTS)
	$(CXX) -o $(EXEC) $(OBJECTS) $(LFLAGS) 

%.o: %.c
	$(CXX) -c -o $@ $< $(CFLAGS)

# Traktuje ponizsze wyrazy jako instrukcje, nie nazwy plikow
.PHONY: clean del

# Czysci wszystkie pliki posrednie
clean:
	rm -rf $(OBJECTS)

# Usuwa wykonywalny plik projektu
del:
	rm -rf $(EXEC)
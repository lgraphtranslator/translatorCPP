RESULT = lib/
BIN = bin/
TARGET = $(BIN)libtranslator.so
SRC = src/
TEST = test/

all:$(TARGET)

$(TARGET):$(BIN)Scanner.o $(BIN)Ident.o $(BIN)TableIdent.o $(BIN)Token.o $(BIN)Interpretator.o $(BIN)Parser.o $(BIN)Poliz.o $(BIN)Executer.o $(BIN)Variable.o 
	g++ -shared -o $(TARGET) $(BIN)Scanner.o $(BIN)Ident.o $(BIN)TableIdent.o $(BIN)Token.o $(BIN)Interpretator.o $(BIN)Parser.o $(BIN)Poliz.o $(BIN)Executer.o $(BIN)Variable.o

$(BIN)Scanner.o:
	g++ -fPIC -c -o $(BIN)Scanner.o $(SRC)Scanner.cpp
$(BIN)Ident.o:
	g++ -fPIC -c -o $(BIN)Ident.o $(SRC)Ident.cpp
$(BIN)TableIdent.o:
	g++ -fPIC -c -o $(BIN)TableIdent.o $(SRC)TableIdent.cpp
$(BIN)Token.o:
	g++ -fPIC -c -o $(BIN)Token.o $(SRC)Token.cpp
$(BIN)Interpretator.o:
	g++ -fPIC -c -o $(BIN)Interpretator.o $(SRC)Interpretator.cpp
$(BIN)Parser.o:
	g++ -fPIC -c -o $(BIN)Parser.o $(SRC)Parser.cpp
$(BIN)Poliz.o:
	g++ -fPIC -c -o $(BIN)Poliz.o $(SRC)Poliz.cpp
$(BIN)Executer.o:
	g++ -fPIC -c -o $(BIN)Executer.o $(SRC)Executer.cpp
$(BIN)Variable.o:
	g++ -fPIC -c -o $(BIN)Variable.o $(SRC)Variable.cpp



install:
	install $(TARGET) $(RESULT)
bin:
	mkdir bin

clean:
	rm -rf $(BIN)*.o
	



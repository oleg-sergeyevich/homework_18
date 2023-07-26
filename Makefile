SRC = main.cpp 
TARGET = homework 
LIB = MyLibrary
U = User
M = Message
PREFIX = /usr/local/bin

privet:	$(SRC) lib
		g++ -o $(TARGET) $(SRC) -L. -l$(LIB)

lib:	$(U).cpp $(U).h $(M).cpp $(M).h
		g++ -o $(U).o $(U).cpp -c
		g++ -o $(M).o $(M).cpp -c
		ar rc lib$(LIB).a $(U).o $(M).o

clean:	
		rm -rf *.o *.a 

install:
		install $(TARGET) $(PREFIX)

uninstall:
		rm -rf $(PREFIX)/$(TARGET)
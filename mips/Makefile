mips: main.o mips.o mips.h
	g++ -o mips -g main.o mips.o
main.o: main.cpp mips.h
	g++ -c -g main.cpp
mips.o: mips.cpp mips.h
	g++ -c -g mips.cpp

clean:
	rm *.o
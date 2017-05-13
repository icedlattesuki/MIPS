mips: main.o mips.o mips.h
	clang++ -o mips -g main.o mips.o
main.o: main.cpp mips.h
	clang++ -c -g main.cpp
mips.o: mips.cpp mips.h
	clang++ -c -g mips.cpp

clean:
	rm *.o
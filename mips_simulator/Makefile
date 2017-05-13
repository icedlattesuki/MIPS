cpu: main.o cpu.o mips.o
	clang++ -o cpu -g main.o cpu.o mips.o
main.o: main.cc cpu.h mips.h
	clang++ -g -c main.cc
cpu.o: cpu.cc cpu.h mips.h
	clang++ -g -c cpu.cc
mips.o: mips.cc mips.h
	clang++ -g -c mips.cc

clean:
	rm *.o
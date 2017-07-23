a: main.o mips_invert.o
	g++ -o a main.o mips_invert.o -g
main.o: main.cc mips_invert.h
	g++ -c main.cc -g
mips_invert.o: mips_invert.cc mips_invert.h
	g++ -c mips_invert.cc -g
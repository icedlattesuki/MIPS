a: main.o mips_invert.o
	clang++ -o a main.o mips_invert.o -g
main.o: main.cc mips_invert.h
	clang++ -c main.cc -g
mips_invert.o: mips_invert.cc mips_invert.h
	clang++ -c mips_invert.cc -g
cpu: main.o cpu.o mips.o mips_invert.o mips.h mips_invert.h cpu.h
	clang++ -o cpu -g main.o cpu.o mips.o mips_invert.o
main.o: main.cc cpu.h mips.h
	clang++ -g -c main.cc
cpu.o: cpu.cc cpu.h mips.h
	clang++ -g -c cpu.cc
mips.o: mips.cc mips.h
	clang++ -g -c mips.cc
mips_invert.o: mips_invert.h mips_invert.cc
	clang++ -g -c mips_invert.cc

clean:
	rm *.o
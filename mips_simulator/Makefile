cpu: main.o cpu.o mips.o mips_invert.o mips.h mips_invert.h cpu.h
	g++ -o cpu -g main.o cpu.o mips.o mips_invert.o
main.o: main.cc cpu.h mips.h
	g++ -g -c main.cc
cpu.o: cpu.cc cpu.h mips.h
	g++ -g -c cpu.cc
mips.o: mips.cc mips.h
	g++ -g -c mips.cc
mips_invert.o: mips_invert.h mips_invert.cc
	g++ -g -c mips_invert.cc

clean:
	rm *.o
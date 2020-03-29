cc = g++
prom = sudoku_solve
deps = sudoku.h
obj = main.o neighbor.o sudoku_basic.o
 
$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

main.o: main.cc $(deps)
	$(cc) -c main.cc

neighbor.o: neighbor.cc $(deps)
	$(cc) -c neighbor.cc

sudoku_basic.o: sudoku_basic.cc $(deps)
	$(cc) -c sudoku_basic.cc

.PHONY:clean
clean:
	rm *.o $(prom)

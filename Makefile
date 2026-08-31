sudoku: sudoku.c
	gcc sudoku.c -o sudoku

run: sudoku
	./sudoku

clean:
	rm -f sudoku

.PHONY: clean run

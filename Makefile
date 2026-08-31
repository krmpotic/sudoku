sudoku: sudoku.c
	gcc sudoku.c -o sudoku

run: sudoku
	./sudoku

clean:
	rm -f sudoku
	rm -f tests/*.out

fmt: sudoku.c
	clang-format -i sudoku.c

test: sudoku
	cat tests/0.in | ./sudoku > tests/0.out
	diff tests/0.out tests/0.exp || echo FAIL

.PHONY: clean run test fmt

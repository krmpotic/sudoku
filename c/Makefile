sudoku: sudoku.c
	gcc -Wall -Wextra -g -O0 sudoku.c -o sudoku

clean:
	rm -f sudoku

fmt: sudoku.c
	clang-format -i sudoku.c

test: sudoku
	@cat ../tests/0.in | ./c/sudoku > ../tests/0.c.out
	@diff ../tests/0.c.out ../tests/0.exp && echo 'PASSED #0' || echo 'FAILED #0'

.PHONY: clean fmt test

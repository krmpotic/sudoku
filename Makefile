sudoku:
	$(MAKE) -C ./c/ sudoku
	mv ./c/sudoku sudoku

clean:
	rm -f sudoku

.PHONY: clean

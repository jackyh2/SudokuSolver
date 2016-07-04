# SudokuSolver
Implements Dancing Links algorithm to solve Sudoku.

If 'n' is the dimension of a single box, the exact cover matrix has
Rows = n^2 symbols into (n^2 * n^2) boxes
	 = n^6
Columns/constraints
	 = n^2 symbols in n^2 rows
	 + n^2 symbols in n^2 columns
	 + n^2 symbols in n^2 boxes
	 + n^2 * n^2 boxes to fill
	 = 4n^4
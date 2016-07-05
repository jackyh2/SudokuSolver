#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>

#include <cmath>
#include "exactcover.h"

#define COND 4

Matrix_ExactCover m_create(std::vector<int> input, int size) {
	int row = pow(size, 6);
	int col = pow(size, 4)*COND;
	int m[row][col];
	std::vector<int>::iterator v = input.begin();
	for (int p = row; p < row; ++p) {
		for (int q = col; q < col; ++q) {
			m[p][q] = *v++;
		}
	}
	(void)m;//compile
	return 0;
}

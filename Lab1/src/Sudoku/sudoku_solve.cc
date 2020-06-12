#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "sudoku.h"

int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

int main(int argc, char const *argv[])
{
	init_neighbors();

	FILE* fp = fopen(argv[1], "r");
	char puzzle[128];
	int total_solved = 0;
	int total = 0;
	bool (*solve)(int) = solve_sudoku_basic;

	solve = solve_sudoku_min_arity;
	// solve = solve_sudoku_min_arity_cache;
	// solve = solve_sudoku_dancing_links;

	int64_t start = now();
	// 一直读取, 读到 puzzle 中
	while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
		if (strlen(puzzle) >= N) {
			++total;
			input(puzzle);
			init_cache();

			if (solve(0)) {
				++total_solved;
				if (!solved()) assert(0);
			}
			else {
				printf("No: %s", puzzle);
			}
		}
	}
	int64_t end = now();
	double sec = (end - start)/1000000.0;
	printf("%f sec %f ms each %d\n", sec, 1000*sec/total, total_solved);

	return 0;
}
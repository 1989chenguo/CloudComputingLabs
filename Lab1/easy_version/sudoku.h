#ifndef SUDOKU_H
#define SUDOKU_H

const bool DEBUG_MODE = false;//�Ƿ�����м�����������Ϣ�� 
enum { ROW=9, COL=9, N = 81, NEIGHBOR = 20 };//����Ϊ���� ���� ������ һ��������Χ20�����ڵķ����С��С�����
const int NUM = 9;//������1~9


extern int neighbors[N][NEIGHBOR];//neighbors[i][j]��ʾ��i������ĵ�j���ھӵ��±�

const int MaxNumPuzzle = 1e6;
extern char puzzle[MaxNumPuzzle][128];
extern char solution[MaxNumPuzzle][N+1];

extern int board[MaxNumPuzzle][N];
extern int spaces[MaxNumPuzzle][N];
/********************************/


void init_neighbors();
int input(const char in[N],int board[N],int spaces[N]);
void init_cache();

bool available(int guess, int cell,int board[N]);

bool solve_sudoku_basic(int which_space, int board[N],int spaces[N]);
bool solve_sudoku_min_arity(int which_space);
bool solve_sudoku_min_arity_cache(int which_space);
bool solve_sudoku_dancing_links(int unused);
bool solved(int board[N]);
#endif

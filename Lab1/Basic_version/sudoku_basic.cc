#include <assert.h>
#include <stdio.h>

#include <algorithm>

#include "sudoku.h"

//int board[N];//һά����ֵΪ���������
//int spaces[N];//����Ŀո�ֵΪ�������е��±�
//int nspaces;// ����������Ŀո�����
//int (*chess)[COL] = (int (*)[COL])board;//��Ψ���̵Ķ�ά���� 

static int find_spaces(int board[N],int spaces[N])//������пո��¼�ո�һά���� 
{
  int nspaces = 0;
  for (int cell = 0; cell < N; ++cell) {
    if (board[cell] == 0)
      spaces[nspaces++] = cell;
  }
  return nspaces;
}

int input(const char in[N],int board[N],int spaces[N])//����������ַ���תΪһά��ֵ����
{
  for (int cell = 0; cell < N; ++cell) {
    board[cell] = in[cell] - '0';
    assert(0 <= board[cell] && board[cell] <= NUM);
  }
  return find_spaces(board,spaces);
}

bool available(int guess, int cell, int board[N])
{
  for (int i = 0; i < NEIGHBOR; ++i) {
    int neighbor = neighbors[cell][i];
    if (board[neighbor] == guess) {
      return false;
    }
  }
  return true;
}

bool solve_sudoku_basic(int which_space,int nspaces,int board[N],int spaces[N])//�ݹ���� 
{
  if (which_space >= nspaces) {
    return true;
  }
  int cell = spaces[which_space];

  for (int guess = 1; guess <= NUM; ++guess) {
    if (available(guess, cell,board)) {
      assert(board[cell] == 0);
      board[cell] = guess;
      if (solve_sudoku_basic(which_space+1,nspaces,board,spaces)) {
		return true;
      }

      assert(board[cell] == guess);
      board[cell] = 0;
    }
  }
  return false;
}

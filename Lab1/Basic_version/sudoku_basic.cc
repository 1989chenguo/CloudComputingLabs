#include <assert.h>
#include <stdio.h>

#include <algorithm>

#include "sudoku.h"

//int board[N];//一维棋盘值为所填的数字
//int spaces[N];//待填的空格值为在棋盘中的下标
//int nspaces;// 棋盘上最初的空格总数
//int (*chess)[COL] = (int (*)[COL])board;//二唯棋盘的二维数组 

static int find_spaces(int board[N],int spaces[N])//标记所有空格记录空格一维坐标 
{
  int nspaces = 0;
  for (int cell = 0; cell < N; ++cell) {
    if (board[cell] == 0)
      spaces[nspaces++] = cell;
  }
  return nspaces;
}

int input(const char in[N],int board[N],int spaces[N])//根据输入的字符串转为一维数值棋盘
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

bool solve_sudoku_basic(int which_space,int nspaces,int board[N],int spaces[N])//递归填充 
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

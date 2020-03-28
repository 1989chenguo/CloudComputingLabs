#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "sudoku.h"

char puzzle[MaxNumPuzzle][128];
char solution[MaxNumPuzzle][N+1];
int board[MaxNumPuzzle][N];
int spaces[MaxNumPuzzle][N];

int total=0;//数独问题的总数量
int total_solved = 0;//已经解决数独的数目
bool (*solve)(int, int, int*, int*) = solve_sudoku_basic;//采用最基本的basic方法解决问题 
int numOfWorkerThread=2;//，线程的数目，默认双线程
pthread_t* WorkThreads;
long int threadID;

int nextPuzzleWillSolve=0;
pthread_mutex_t WorkThreadMutex=PTHREAD_MUTEX_INITIALIZER;

const char outputFileName[10]="outfile"; 
int64_t now() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void read_data() { //读文件数据 

	char *file_name=(char*)malloc(256*sizeof(char));
	FILE *fp;
	while(fgets(file_name, 256, stdin)) {

		if(file_name[0]=='\n') {
			
			printf("please wait...\n");
			break;
		}

		if(file_name[strlen(file_name)-1]=='\n')  file_name[strlen(file_name)-1]='\0';

		fp = fopen(file_name, "r");

		if(fp==NULL) {
			printf("%s does not exist.please try again\n",file_name);
			continue;
		}
		while(fgets(puzzle[total],1024,fp)) {
			if(strlen(puzzle[total])>=N) {
				++total;
			}
		}
	}

}
int recvOnePuzzle(){
	int currentPuzzleID=0;
	pthread_mutex_lock(&WorkThreadMutex);
	while(nextPuzzleWillSolve>=total) 
	{  
		pthread_mutex_unlock(&WorkThreadMutex);
		return -1;
	}
	currentPuzzleID=nextPuzzleWillSolve;
	nextPuzzleWillSolve++;
	pthread_mutex_unlock(&WorkThreadMutex);
	return currentPuzzleID;
}
void* Thread_solve(void* CurThread) {
	long int my_CurThread = (long int) CurThread;
	
	int currentPuzzleID=0;
	int *PuzzleHaveSolved=(int*)malloc(total*sizeof(int));//当前教程解决的数独id集 
	long int CurThreadHaveSolvedNum=0;//当前线程解决的数独数目 
	
	while(true){
		currentPuzzleID = recvOnePuzzle();
		if(currentPuzzleID==-1)
			break;
		
		PuzzleHaveSolved[CurThreadHaveSolvedNum]=currentPuzzleID;
		CurThreadHaveSolvedNum++;
		
		
		int nspaces = input(puzzle[currentPuzzleID],board[currentPuzzleID],spaces[currentPuzzleID]);
		
		if(solve(0,nspaces,board[currentPuzzleID],spaces[currentPuzzleID])) {
			
			++total_solved;
			
			if (!solved(board[currentPuzzleID]));
		
		} else {
			printf("currentPuzzleID:%d;NoSolution: %s", currentPuzzleID,puzzle[currentPuzzleID]);
		}
		
		for(int j=0; j<N; ++j) {
			solution[currentPuzzleID][j]=board[currentPuzzleID][j]+'0';
		}
		solution[currentPuzzleID][N]='\0';
		if(DEBUG_MODE){
		printf("The No.%d puzzle's solution:%s\n",currentPuzzleID,solution[currentPuzzleID]);
	}
	}
	if(DEBUG_MODE){
	 printf("threadID No.%d have solved:",my_CurThread);
	 for(int i=0;i<CurThreadHaveSolvedNum;++i){
		 if(i>0) printf(",");
		 printf("%d",PuzzleHaveSolved[i]);
	 }
	 printf("CurThreadHaveSolvedNum: %d\n",CurThreadHaveSolvedNum);
   }
	return NULL;
}
void outputToFile() {
	FILE *fp = fopen(outputFileName,"w");
	for(int i=0; i<total; ++i) {
		fprintf(fp,"%s\n",solution[i]);
	}
	printf("okay,all the solution has been output to 'outfile'\n");
}
int main(int argc, char* argv[]) {

     
	if(argc>=2)
    numOfWorkerThread=atoi(argv[1]);//输入工作线程数 

	init_neighbors();
	read_data(); 

	int64_t start = now();//开始计时
	WorkThreads = (pthread_t *)malloc(numOfWorkerThread*sizeof(pthread_t));

	for(threadID=0;threadID<numOfWorkerThread; ++threadID) {
		if(pthread_create(&WorkThreads[threadID],NULL,Thread_solve,(void*)threadID)!=0){
			 perror("pthread_create failed");
			 exit(1);
		}
	}
	
	for(threadID=0;threadID<numOfWorkerThread; ++threadID) {
		pthread_join(WorkThreads[threadID],NULL);
	}
	int64_t end = now();
	double sec = (end-start)/1000000.0;
	printf("%f sec %f ms each %d\n", sec, 1000*sec/total, total_solved);
	free(WorkThreads);
	outputToFile();
}


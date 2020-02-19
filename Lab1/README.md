# Lab 1: “Super-fast” Sudoku Solving

https://github.com/1989chenguo/CloudComputingLabs/tree/master/Lab1

## 1. Overview

Implement a Sudoku solving program, using multiple threads or multiple processes, running on a single machine. Try to **utilize all your CPU cores** and make your program **run as fast as possible**! 

### Goals

* Practice basic parallel programming skills, such as using multiple threads/processes;
* Get familiar with Unix OS environment development (eg., file I/O, get timestamp);
* Get familiar with source code version control tools (git), and learn to collaborate with others using github;
* Practice how to do performance test and write a high-quality performance test report.

## 2. Background

### 2.1 Introduction to Sudoku

Sudoku (originally called Number Place) is a logic-based combinatorial number-placement puzzle. 

You are given a 9×9 board of 81 squares logically separated into 9 columsn, 9 rows, and 9 3×3 subsquares. The goal is, given a board with some initial numbers filled in (we call it a **Sudoku puzzle**), fill in the rest of the board so that every column, row, and subsquare have all the digits from 1 to 9 and each digit appears only once (we call it a **Sudoku solution**).


 <u>An example Sudoku puzzle:</u>

<img src="src/Sudoku_puzzle.png" alt="Sudoku" title="Sudoku puzzle" style="zoom:67%;" />

 <u>An example Sudoku solution to above puzzle:</u>

<img src="src/Sudoku_answer.png" alt="Sudoku" title="Sudoku answer" style="zoom:67%;" />

### 2.2 Some useful resources

If you have no idea about what algorithms can be used to solve Sudoku puzzles, we suggest you read [this](https://rafal.io/posts/solving-sudoku-with-dancing-links.html). To simplify your work, we have provided an simple [implementation](src/Sudoku/) of 4 Sudoku solving algorithms (some are slow, some are fast), but without using multiple threads/processes. The two files *test1* and *test1000* contain many puzzles for you to test. 

Of course, you are always encouraged (not mandatory) to implement those algorithms by yourselves and even your own algorithms (if you have time).

## 3. Your Lab Task

### 3.1 Write a program 

Implement a program which satisfies the following requirements:

#### 3.1.1 Program input and output

##### **3.1.1.1 Input** 

1. Your program should have no arguments during start. For example, if your program is called *sudoku_solve*,  just typing `./sudoku_solve` and your program will run correctly.
2. But after start, your program should be able to read multiple strings from ***stdin***, where each string is separated by a line-break. Each string is a **name of a file**, which contains one or more Sudoku puzzles that your program is going to solve. 
3. In the input file, **each line** is a Sudoku puzzle that needs to be solved. Each line contains 81 decimal digits. The 1st-9th digits are the 1st row of the 9×9 grid, and the 10th-18th digits are the 2nd row of the 9×9 grid, and so on. Digit 0 means this digit is unknown and your program needs to figure it out according to the Sudoku rules described above.

<u>Example input to your program</u> may be like this (start your program and read 3 input file names from stdin)

<img src="src/ExampleInput.png" alt="ExampleInput" style="zoom:50%;" />

<u>Example input file format</u>, 

```
./test1 is an input file that contains one Sudoku puzzle problem that need to be solved:
310000085000903000905000307804000106000401000690000073030502010000804000020706090

The first Sudoku puzzle problem (first line) actually looks like this when being placed on the 9×9 grid:
---------------------
3 1 0 | 0 0 0 | 0 8 5
0 0 0 | 9 0 3 | 0 0 0
9 0 5 | 0 0 0 | 3 0 7
---------------------
8 0 4 | 0 0 0 | 1 0 6 
0 0 0 | 4 0 1 | 0 0 0 
6 9 0 | 0 0 0 | 0 7 3
---------------------
0 3 0 | 5 0 2 | 0 1 0
0 0 0 | 8 0 4 | 0 0 0
0 2 0 | 7 0 6 | 0 9 0
---------------------
```
##### 3.1.1.2 Output

1. You should calculate the solutions of all the Sudoku puzzles in all the input files, and output these solutions into ***stdout***.
2. The solutions should be outputed **in the same sequence** as the puzzles are inputted in. For example, if  there are two input files and the first input file contains 2 puzzles, then, the 1st output solution should be of the 1st puzzle in the first input file, and the 2nd output solution should be of the 2nd puzzle in the first input file, and the 3rd output solution should be of the 1st puzzle in the second input file, and so on.

<u>Example output</u>:

```
Assuming your program has been inputted with two file names from stdin: 
./test1
./test2

./test1 has the following content:
310000085000903000905000307804000106000401000690000073030502010000804000020706090

./test2 has the following content:
000000010400000000020000000000050407008000300001090000300400200050100000000806000
000000013000030080070000000000206000030000900000010000600500204000400700100000000

Then your program should output the following results to stdout:
312647985786953241945128367854379126273461859691285473437592618569814732128736594
693784512487512936125963874932651487568247391741398625319475268856129743274836159
869725413512934687374168529798246135231857946456319872683571294925483761147692358

Where the 1st line in the output is the solution to puzzle
310000085000903000905000307804000106000401000690000073030502010000804000020706090
and the 2nd line in the output is the solution to puzzle
000000010400000000020000000000050407008000300001090000300400200050100000000806000
and the 3rd line in the output is the solution to puzzle
000000013000030080070000000000206000030000900000010000600500204000400700100000000
```
#### 3.1.3 Implementation requirements 

##### 3.1.3.1 Basic version

Your program should be able to: 

1. Accept **one** input file name, and the size of the input file is smaller than 100MB. 
2. Successfully solve the puzzles in the input file, and output the results in the format described before.
3. Use multiple threads/processes to make use of most of your machine's CPU cores.

\[Tips\]: 1) Use event queue to dispatch tasks and merge results to/from worker threads. 2) Dynamically detect how many CPU cores are there on your machine, in order to decide how many threads/processes your program uses. 3) Be careful about the contention among multiple threads/processes

##### 3.1.3.2 Advanced version

Your program should be able to: 

1. Complete all the requirements in the basic version.
2. Accept **any number of** input file names, and the size of input file can be **any large** (as long as it can be stored on your disk)
3. When the program is solving puzzles in the previously input file(s), the program can **meanwhile accept more input file names from *stdin***.

\[Tips\]: 1) Use a dedicated thread to accept input; 2) To avoid consuming all the memory, read different parts of the file into memory and solve them one by one; 3) You are encouraged to try more optimizations such as cache coherency processing.

### 3.2. Finish a performance test report

Please test your code first, and commit a test report along with your lab code into your group’s course github repo. 

The test report should describe your test inputs, and the performance result under various testing conditions. Specifically, in your test report, you should at least contain the following two things:

1. Compare the performance of your “super-fast” Sudoku solving program with a simple single-thread version, using the same input and under the same environment.
2. Change the input (e.g., change file size) and environment (e.g., using machines with different CPUs and hard drives), and draw several curves of your program’s performance under various conditions.

## 4. Lab submission

Please submit your lab program and performance test report following the guidance in the [Overall Lab Instructions](../README.md)

## 5. Grading standards

1. You can get 38 points if you can: 1) finish all the requirements of the basic version, and 2) your performance test report has finished the two requirements described before. If you missed some parts, you will get part of the points depending how much you finished
2. You can get 40 points (full score) if you can: 1) finish all the requirements of the advanced version, and 2) your performance test report has finished the two requirements described before. If you missed some parts, you will get part of the points depending how much you finished.


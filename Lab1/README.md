==================================================

This is the instruction for Lab 1 

==================================================

Lab 1: “Super-fast” word-count program
1.	Overview
Implementing a word-count program, using multiple threads or multiple processes, running on a single machine.
2.	Program input
Input 1: The name of a file from stdin. 
[Note on input 1] The file may be very large, and contain any number of English words. Each word only contains the letters in English alphabet, and each word is separated with a line break symbol ‘\n’. 
Example file format:
Hello
To
All
The
Students
Hello
To
The
Teacher
3.	Program output
Output 1: The number of times that each word appears in the file. 
[Note on output 1] Should list all the words that have ever appeared in the file, and count how many times that each word has appeared.
Example output (matching the input example above):
	Hello 2
	To 2
	All 1
	The 2
	Students 1
	Teacher 1
4.	Implementation requirements 
4.1	Basic version
Use at least two threads/processes to concurrently count words in the input file, and correctly merge the results after all the threads/processes finished. Try your best to optimize your program’s performance!
4.2	Advanced version
Besides the “basic” functions: When the program is counting the words in the previously input file(s), the program can continuously receive more input file names from stdin. Try your best to optimize your program’s performance!
5.	Test report
Please test your code first, and commit a test report along with your lab code into your group’s course github repo. 
The test report should contain several sample test inputs, and the performance result under various testing conditions. Specifically, in your test report, you should at least contain the following two things:
1)	Compare the performance of your “super-fast” word-count program with a simple single-thread version, using the same input and under the same environment.
2)	Change the input (e.g., change file size, word pattern) and environment (e.g., using machines with different CPUs and hard drives), and draw several curves of your program’s performance under various conditions.

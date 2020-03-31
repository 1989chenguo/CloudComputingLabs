Lab1 test report
=====
# 1.实验概述
## 1.1输入
&emsp;&emsp;程序在控制台接收输入的测试文件，测试文件在当前版本的代码的目录下，包括test1,test10…test1000，,文件中包含一个到多个的数独题，并且这些数独按照一定的格式存储。
## 1.2输出
&emsp;&emsp;程序将测试文件的数独的解按照与输入相应的顺序写到输出文件outfile中。
## 1.3 Sudoku算法
   &emsp;&emsp;实验提供了四个算法：BASIC,DANCE,MINA 和 MINAC。本实验选择使用BASIC算法。
## 1.4实验环境
   &emsp;&emsp;本次实验有3个不同的实验环境，分别是：<br>


- yudan：Linux内核版本为4.15.0-72-generic；1GB内存；CPU型号为Intel®Core™i5-7200U CPU@2.50GHz，共一个物理CPU，每个物理CPU有4个物理核心；不使用超线程技术。<br>

- tjc：<br>


- 服务器：<br>
在测试时会说明不同的测试环境<br>
## 1.5 代码版本
&emsp;&emsp;本次实验中使用了三份代码：<br>

- easy_version，静态分配各个线程任务后各自执行等<br>

- Basic_version，使用任务队列分配任务等<br>

- Advanced_version，在Basic_version版本基础上，使用一个专门的线程接受输入，并且可以接受任何数量的输入文件等。
# 2.性能测试
   &emsp;&emsp;本次实验的性能分析将比较:<br>

- 	实验中实现的不同版本的代码在相同的测试环境、不同的输入文件以及同样使用单线程进行求解的性能差别；<br>

- 	实验中实现的某一版本的代码在相同的测试环境下、相同的文件输入以及不同的线程数量的性能差别；<br>


- 实验中实现的某一代码在不同的测试环境下、相同的文件输入以及相同的线程数量的性能差别。
## 2.1不同版本的代码

- 代码版本：Advanced_version，Basic_version以及easy_version

- 输入：从test1到test1000，使用单线程求解<br>


- 测试环境：服务器<br>
  &emsp;&emsp;这三个版本的代码实现了相同的功能，但是在时间上的开销是不同的，随着问题规模的不断增大，不同版本的代码时间上的开销的差距会更加明显的显现。本次实验对这些代码进行时间开销上的对比，分别按照输入文件test1,test10,test20,test30,test50,test100,test200,test500,test100对代码版本Advanced_version，Basic_version以及easy_version进行测试。<br>
&emsp;&emsp;从下图中可以看出当输入文件的数独数量不断增加，Advanced_version，Basic_version以及easy_version的时间开销差距越来越明显。在test1000时easy_version比Basic_version多花了将近14秒的时间，这是因为basic比easy版本实现代码更多，并且随着输入文件数独问题数量的增多，额外的开销的影响就体现出来了，所以最终会造成下图这种情况。<br>

![](https://github.com/sunminyu/CloudComputingLabs/blob/master/Lab1/src/images/input.png)

## 2.2不同线程数


- 代码版本为Basic_version


- 输入：test100


- 测试环境：yudan<br>
    
 &emsp;&emsp;针对Basic_version版本的代码在不同的线程数的使用情况下，测试其时间性能，线程的数量为1,2,4,8,……1024，使用某个数量的线程对所提供的输入文件test100中的数独题进行求解，并且将结果写入输出文件outfile中，测量整个过程的时间开销。<br>
![](https://github.com/sunminyu/CloudComputingLabs/blob/master/Lab1/src/images/time.png)
 
## 2.3不同硬件环境
   

- 实验使用Basic_version版本的代码在两个不同的硬件环境下

- 针对输入文件test100进行求解测试

- sudoku_solve线程数量从1开始增加

- 测试环境: tjc、yudan<br>
 如下图所示为在不同硬件环境下的测试结果:<br>
![image](https://github.com/sunminyu/CloudComputingLabs/blob/master/Lab1/src/images/hardware.png)

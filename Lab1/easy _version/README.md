## 注意事项

1.make后执行sudoku_solve（可输入第二个参数，代表线程数。不输入则默认为双线程），开始输入测试文件

2.可输入多个测试文件，以**回车键分隔**

3.**连续键入两个回车键**代表输入结束

4.输入结束后开始求解数独

5.求解完成后会将所有数独的解输出至文件`outfile`中（也可输出至标准输出，在`main.cc`中取消注释输出语句即可）

![image-20200326194127177](http://q7oeubsc9.bkt.clouddn.com/image-20200326194127177.png)

6.本文件夹内使用的方式为solve_sudoku_basic，为多线程分配任务的方式为动态

7.可求解的puzzle个数为`1e6+5`，若想求解更多，在`sudoku.h`中修改`num_of_puzzle`即可

## 文件截图

`test1`文件：

![image-20200326104745363](http://q7oeubsc9.bkt.clouddn.com/image-20200326104745363.png)

`test4`文件：

![image-20200326104721426](http://q7oeubsc9.bkt.clouddn.com/image-20200326104721426.png)

`outfile`文件（部分）：

![image-20200326104545055](http://q7oeubsc9.bkt.clouddn.com/image-20200326104545055.png)

即test1文件中一个puzzle的解对应于`outfile`文件中的第1行；
test4文件中四个puzzle的解对应于`outfile`文件中的第2\~5行；
test40文件中四十个puzzle的解对应于`outfile`文件中的第6\~45行；
依次类推。
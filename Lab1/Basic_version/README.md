# Cloud Computing: Overall Lab Instruction

<!--**This is the repo containing all the lab materials for undergraduate course CS06142 "Cloud Computing Techniques" at Hunan University**--> 

## 1. Overview

There are **4 labs in total** in this course. All the materials of each lab are under folders Lab1-4 in this repo. Please clone the lab git repo onto your local computer,

`git clone https://github.com/1989chenguo/CloudComputingLabs.git`

and always track our latest lab materials using the following commands (should first enter the folder you have cloned from our lab repo)

`git pull`

You can find this overall lab instruction in `README.md` in the root folder.

Please **carefully read the overall lab instruction before you do anything**. 

Also, please **carefully read each lab's instruction** ([Lab1](Lab1/README.md), [Lab2](Lab2/README.md), [Lab3](Lab3/README.md), [Lab4](Lab4/README.md)) to get each lab's task, background, requirements, etc.

## 2. Group collaboration

Each student should register your own github account. Group members should use **git and github** to collaborate. 

All the labs are done in the unit of group, i.e., a group only needs to submit one piece of code for each lab. However, each group member should make enough contribution to the lab. Teaching assistants will check the **git commit history** to evaluate each one’s contribution.

## 3. Code submission

Each group should create a code repo for our course (create your own group's repo, do not push onto my course lab repo!). The group leader should send an email to TA telling us your group's lab git repo address. For example, https://github.com/group1/CloudComputingLabs.git`

**All the lab code should be submitted through pushing to your group's github code repo.** Teaching assistants will checkout your commit, and read and test your codes from the above repo address you provided us. The code of different lab should be in different folders, named Lab1/Lab2/Lab3/Lab4, respectively (following the same structure of this repo). Please note that your lab folder name should be exactly same as above (be careful about the first capital letter and no space before the number), otherwise your code may fail in our TAs' automatic testing scripts. All lab codes should be in the same course git repo of your group.

Please write a README.md to each lab code folder, briefly introducing how to run your lab code (including how to set the environment, provide the input, and explain the output, etc.). Keep the README short and clear! Also, your code should be well commented so that other people can understand without asking you. 

All of our labs focus very much on the performance. So please **DO submit a performance test report** along with each of your lab code. Unlike your other courses, we do NOT require you to submit any lab report to explain your code structure or share your understandings or experiences during lab conduction.  

## 4. Environment requirement

### 4.1 OS requirement

All the labs should be tested and runnable on UNIX-like operating systems, such as Linux distributions (e.g., Ubuntu, CentOS) and MacOS. We highly recommend you to use Linux distributions such as Ubuntu.
If you only have windows PC or laptops, install a UNIX VM and do experiments on the VM.

### 4.2 Programming language

Any programming languages are permitted in all labs, such as C/C++, Java, Go, Python, Perl. But for performance consideration, we highly recommend you to use C/C++ or Go !!!

### 4.3 Try to only use standard API

To make your program portable, try your best to only use standard & widely available functions and normal libraries (such as `glibc`, `C++ STLs` and some typical math libraries). All the labs should only use standard system API defined by POSIX specification or Linux man page specification. We prefer to use standard POSIX API, so your code can be easily runnable on various kind of UNIX-like systems (instead of only on Linux). 

## 5. Grading

Grading details are specified in each lab's instruction document, please carefully read them [Lab1](Lab1/README.md), [Lab2](Lab2/README.md), [Lab3](Lab3/README.md), [Lab4](Lab4/README.md).

Besides, we have the following 3 overall grading requirements applicable to all the 4 labs:

1. **DO NOT copy** others' code (either from the Internet or from your classmates), otherwise your group (every member and the leader) will got **zero point** in the lab. However, we encourage to communicate with other group and learn from each other. But do remember to write the code yourself and not copy.
2. **DO NOT miss the deadline**, otherwise your group (every member and the leader) points will be reduced accordingly.
3. Typically, your group (every member and the leader) will get same points in each lab, unless we find severely **unfair contribution** in the git commit history.  In the overall grading, the leader will get some more points as bonus.
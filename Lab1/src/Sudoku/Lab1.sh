#!/bin/bash
#~/test_data/advanced_test  (include test1 test1000)
if [ $# != 2 ] ; then 
echo "参数数量不对" 
echo "参数1:包含测试文件组的文件 例如 \"test_group\"  (其中可能包含 ./test1 ./test1000) " 
echo "参数2:包含测试文件组的文件 例如 \"answer_group\"  (其中可能包含 ./answer1 ./answer1000) " 
echo "完整命令列如 : $0 test_group" 
exit 1; 
fi 

test_data_txt=$1
answer_date_txt=$2
GROUP_NAME="group1"
Current_Folder=$(cd `dirname $0`; pwd)
Record_Time="${test_data_txt}_Folder/Record_Time.csv"
Error_Teams="${test_data_txt}_Folder/Error_Teams.csv"

if [ -e ${test_data_txt}_Folder ];then
    echo "${test_data_txt}_Folder 无需创建，已存在"
else
    mkdir ${test_data_txt}_Folder
	echo "创建${test_data_txt}_Folder"
fi

touch ${Record_Time}

echo "Team_Name,Use_Time(ms),Creat_Time,Modify_Time" > ${Record_Time}

#$1 team_name $2 Result_name $3 ${Answer_Line} $4 diff_line
Cul_Run_Time(){
    # stat $2
	
	INODE=$(ls -i $2 |awk '{print $1}')
	FILENAME=$2

	string=$(pwd)  
	array=(${string//\// })  
	root_Directory=${array[0]};

	DISK=$(df -h |grep ${root_Directory} |awk '{print $1}')

	# 文件系统非ext4则退出
	[[ "`df -T | grep ${DISK} |awk '{print $2}'`" != "ext4" ]] && { echo ${DISK} is not mount on type ext4! Only ext4 file system support!;exit 2; }

	Create_Time_t=$(sudo debugfs -R "stat <${INODE}>" ${DISK} | grep "crtime:" | awk '{printf $7}')
	
	Access_Time_t=$(stat $2 | grep "Access: 2" | awk '{printf $3}')
	Modify_Time_t=$(stat $2 | grep Modify | awk '{printf $3}') 
    # echo "Access_Time_t:$Access_Time_t   Modify_Time_t:$Modify_Time_t"
	echo "Create_Time_t:$Create_Time_t   Modify_Time_t:$Modify_Time_t"
	# Access_Time=$(date -d ${Access_Time_t} +%s%N)
	Create_Time_t=$(date -d ${Create_Time_t} +%s%N)
	Modify_Time=$(date -d ${Modify_Time_t} +%s%N)
	# echo "$1 A is $Access_Time M is $Modify_Time"
	# Use_Time=`echo $Modify_Time $Access_Time | awk '{ print ($1 - $2) / 1000000}'`
	echo "$1 Cr is $Create_Time_t M is $Modify_Time"
	Use_Time=`echo $Modify_Time $Create_Time_t | awk '{ print ($1 - $2) / 1000000}'`
	# Check_Answer $1 $2 $3
	echo -e "\033[32m $1 Use_Time: $Use_Time ms \033[0m"

	Team_Answer=$(cat $2 | wc -l)
	if [[ ${Team_Answer} -ge $3 ]];then
		echo -e "\033[32m Up to standard Team_Answer:${Team_Answer} Answer_Line:$3 \033[0m"
	else
		echo -e "\033[31m Not up to standard Team_Answer:${Team_Answer} Answer_Line:$3 \033[0m"
		echo "$1 Not up to standard   Team_Answer:${Team_Answer} Answer_Line:$3"  >> ${Error_Teams}
	fi

	right_rate=$(echo "scale=2;1 - $4 / $3" | bc)
	# echo "$1,${right_rate},$Use_Time,${Team_Answer},$3,,$Access_Time_t,$Modify_Time_t"
	# echo "$1,${right_rate},$Use_Time,${Team_Answer},$3,,$Access_Time_t,$Modify_Time_t" >> ${Record_Time}
}

Basic_Test(){
	# $1 team_name $2 test_data_file_name $3 answer_date_file_name
	test_data=$(cat $2) # ./test1 kml
	Answer_Line=0
	Exe_Prog=""
	cd ${Current_Folder}
    Result="${test_data_txt}_Folder/Basic_Result"
	Answer="${test_data_txt}_Folder/Basic_Answer"

	if [[ -e sudoku_solve ]];then
		echo "找到执行文件sudoku_solve"
		Exe_Prog='sudoku_solve'
	elif [[ -e sudoku ]];then
		echo "找到执行文件sudoku"
		Exe_Prog='sudoku'
	else
		echo "未找到命名为sudoku或sudoku_solve的执行文件"
		echo "进行编译"
		make
		if [[ -e sudoku_solve ]];then
			echo "找到执行文件sudoku_solve"
			Exe_Prog='sudoku_solve'
		elif [[ -e sudoku ]];then
			echo "找到执行文件sudoku"
			Exe_Prog='sudoku'
		else
			echo "编译后仍未找到相应执行文件"
			exit 1; 
		fi
	fi

	if [[ -e ./${Answer} ]];then
		rm ./${Answer}
		touch ./${Answer}
	else
		touch ./${Answer}
	fi
	sudo chmod 777 ./${Answer}
	screen -S $1 -X quit
	screen -dmS $1

	if [[ -e ./${Result} ]];then
		rm ./${Result}
		touch ./${Result}
	else
		touch ./${Result}
	fi

	screen -S $1 -X stuff "stdbuf -oL ./${Exe_Prog} > ./${Result}^M"
	while read -r test_data
	do
		Answer_Line=`expr ${Answer_Line} + $(cat ${test_data} | wc -l)`
		screen -S $1 -X stuff "${test_data}^M"
	done < $2
	
	while read -r answer_data
	do
		cat ${Current_Folder}/${answer_data} >> ${Current_Folder}/${Answer}
	done < $3

	sleep 30
	screen -S $1 -X stuff "^C^M"
	screen -S $1 -X quit

	diff_line=$(diff -ab ./${Result} ./${Answer} | wc -l)
    echo -e "\033[32m 错误个数:$diff_line / ${Answer_Line} \033[0m"
	Cul_Run_Time $1 ${Current_Folder}/${Result} ${Answer_Line} ${diff_line}
}

Advanced_Test(){
	# $1 team_name $2 test_data_file_name
	test_data=$(cat $2) # ./test10000
	Answer_Line=0
	Exe_Prog=""
	cd ${Current_Folder}
    Result="${test_data_txt}_Folder/Advanced_Result"
	Answer="${test_data_txt}_Folder/Advanced_Answer"
	
	if [[ -e sudoku_solve ]];then
		echo "找到执行文件sudoku_solve"
		Exe_Prog='sudoku_solve'
	elif [[ -e sudoku ]];then
		echo "找到执行文件sudoku"
		Exe_Prog='sudoku'
	else
		echo "未找到命名为sudoku或sudoku_solve的执行文件"
		echo "进行编译"
		make
		if [[ -e sudoku_solve ]];then
			echo "找到执行文件sudoku_solve"
			Exe_Prog='sudoku_solve'
		elif [[ -e sudoku ]];then
			echo "找到执行文件sudoku"
			Exe_Prog='sudoku'
		else
			echo "编译后仍未找到相应执行文件"
			exit 1; 
		fi
	fi

	if [[ -e ./${Answer} ]];then
		rm ./${Answer}
		touch ./${Answer}
	else
		touch ./${Answer}
	fi
	sudo chmod 777 ./${Answer}
	screen -S $1 -X quit
	screen -dmS $1

	if [[ -e ./${Result} ]];then
		rm ./${Result}
		touch ./${Result}
	else
		touch ./${Result}
	fi

	screen -S $1 -X stuff "stdbuf -oL ./${Exe_Prog} > ./${Result}^M"
	while read -r test_data
	do
		Answer_Line=`expr ${Answer_Line} + $(cat ${test_data} | wc -l)`
		screen -S $1 -X stuff "${test_data}^M"
	done < $2
	
	while read -r answer_data
	do
		cat ${Current_Folder}/${answer_data} >> ${Current_Folder}/${Answer}
	done < $3

	sleep 30
	screen -S $1 -X stuff "^C^M"
	screen -S $1 -X quit

	diff_line=$(diff -ab ./${Result} ./${Answer} | wc -l)
    echo -e "\033[32m 错误个数:$diff_line / ${Answer_Line} \033[0m"
	Cul_Run_Time $1 ${Current_Folder}/${Result} ${Answer_Line} ${diff_line}
}


if [ -e ${test_data_txt} ];then
    Running_Version=$(cat ${test_data_txt} | wc -l)
    echo "测试样例：$Running_Version 个"
    cat ${test_data_txt}
    if [[ $Running_Version == 1 ]];then
        echo -e "\033[32m --------------${GROUP_NAME} is running Basic_Test-------------- \033[0m"
        Basic_Test ${GROUP_NAME} ${test_data_txt} ${answer_date_txt}
	elif [[ $Running_Version == 0 ]];then
		echo "请检查输入格式，确保文件末尾有一个换行,参照实验指导书"
    else
        echo -e "\033[32m --------------${GROUP_NAME} is running Advanced_Test--------------\033[0m"
        Advanced_Test ${GROUP_NAME} ${test_data_txt} ${answer_date_txt}
    fi
else
    echo "文件$1不存在"
    exit 1; 
fi


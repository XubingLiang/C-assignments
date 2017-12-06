#usr/bin/sh


for file in *.cp
do
	out=`echo $file|cut -d. -f1`
	result=`echo $out|sed s/test/my_result/g`
	compare=`echo $out|sed s/test/result/g`
	echo "testing $out"
	`g++ -std=c++14 -Wall -Werror -O2 -o $out $file`
	`./$out > $result`
	if diff -q $result $compare".txt"
	then
		echo "test passed, you are awesome!"
	else
		echo "test failed, faito!"
	fi
done

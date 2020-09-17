#!/bin/bash -eux
mkdir "result_dir"
cd "result_dir"
base_movie=../movie/sample0914_1.mp4
i=1
while read line
do 
	result_movie="result"${i}".mp4"
	result_sh="result"${i}".sh"
	echo "ffmpeg -i $base_movie -ss $line -t 10 $result_movie" >> $result_sh
	i=`expr $i + 1`
done < ../time.txt

num=$i
i=1
while [ "$i" -lt "$num" ]
do 
	result_movie="result"${i}".mp4"
	result_sh="result"${i}".sh"
	echo ""
	echo "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
	echo "|                                                                 |"
	cat $result_sh
	echo "|                                                                 |"
	echo "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
	echo ""
	bash $result_sh
	wait
	i=`expr $i + 1`
done
rm result?.sh
cd ../
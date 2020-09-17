#!/bin/bash

#編集前動画のパス
base_movie=./movie/sample0914_1.mp4

#===============================================
#===============find_edit_point=================
#===============================================

#出力先
result_txt=result.txt
ffmpeg -i $base_movie -af silencedetect=noise=-15dB:d=0.4 -f null - 2> $result_txt

#===============================================
#==============pick_only_seconds================
#===============================================


#コンパイル
gcc src/text_change.c gnl/get_next_line_utils.c gnl/get_next_line.c libft/libft.a
#実行 (引数は初めに実行したffmpegの出力結果が記載されているファイル)
./a.out $result_txt

rm ./a.out $result_txt

#===============================================
#==============make_ffmpeg_file=================
#===============================================

mkdir "result_movies"
cd "result_movies"
base_movie=".$base_movie"
i=1
while read line
do 
	result_movie="result"${i}".mp4"
	result_sh="result"${i}".sh"
	echo "ffmpeg -i $base_movie -ss $line -t 10 $result_movie" >> $result_sh
	i=`expr $i + 1`
done < ../time.txt

rm ../time.txt

#===============================================
#============ movie edit(pick 10s) =============
#===============================================

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

ffmpeg -f concat -safe 0 -i <(for f in ./*.mp4; do echo "file '$PWD/$f'"; done) -codec copy result.mp4

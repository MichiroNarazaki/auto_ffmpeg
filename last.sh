#編集前動画
base_movie=sample0914_1.mp4
#出力先
result_movie=result.mp4
#開始時刻[s]
start=$(cat result.txt)
#10秒間
ffmpeg -ss $start -i $base_movie -t 10 $result_movie

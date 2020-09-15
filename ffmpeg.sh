#編集前動画
$base_movie=sample0914_1.mp4
#出力先
$result_txt=result.txt
ffmpeg -i $base_movie -af silencedetect=noise=-15dB:d=0.4 -f null - 2> $result_txt
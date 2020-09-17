#!/bin/bash

#コンパイル
gcc text_change.c gnl/get_next_line_utils.c gnl/get_next_line.c libft/libft.a
#実行 (引数は初めに実行したffmpegの出力結果が記載されているファイル)
./a.out result.txt
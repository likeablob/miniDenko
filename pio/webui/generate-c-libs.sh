#! /bin/bash

# TODO: Rewrite in Node
FILES=$(find dist/*gz)
MOVE_TO=../src/webui/

for file in $FILES; do
  echo $file
  header=${file}.h
  xxd -i $file | sed -e 's/\[] =/\[] PROGMEM =/' > $header
  mv $header $MOVE_TO
done

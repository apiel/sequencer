#!/bin/sh

echo "Convert: $1";

./char2mozzi.py ./$1.raw $1.h $1 16384
node js/tableConverterBlank.js $1.h ../tables/$1.h
rm $1.h
rm $1.raw

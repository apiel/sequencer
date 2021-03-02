Save by exporting with the format set to "Other uncompressed formats",
"Header: RAW(headerless)" and "Encoding: Signed 8 bit PCM".

```sh
./char2mozzi.py ./guitar3.raw guitar3.h guitar3 16384
node js/tableConverterBlank.js guitar3.h ../tables/guitar3.h
rm guitar3.h
rm guitar3.raw
```

finally regenerate Tables.h with `node js/genTables.h.js`


or for all the previous step just run bash

./convert.sh guitar3

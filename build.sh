gcc main.c parserf.c lexerf.c codegeneratorf.c ./hashmap/hashmapoperators.c  -c
gcc main.o lexerf.o parserf.o codegeneratorf.o hashmapoperators.o -o demo 
./demo test.did
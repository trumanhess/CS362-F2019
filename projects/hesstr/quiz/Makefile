all: testme.c
	gcc -o testme -g testme.c -Wall -fpic -coverage -lm -std=c99
	-./testme &> testmeProgramTrash.out
	gcov -fb testme.c &> testmeResults.out
	cat testme.c.gcov >> testmeResults.out
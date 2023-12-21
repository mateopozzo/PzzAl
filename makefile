objects = matriz/matriz.o pzzal.o

pzzal : $(objects)
	cc -o pzzal $(objects)

pzzal.o : pzzal.c matriz/matriz.h
	cc -c pzzal.c

matriz/matriz.o : matriz/matriz.c matriz/matriz.h
	cc -c matriz/matriz.c

clean :
	rm pzzal $(objects)

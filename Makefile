out = output/
src = source/

main: bst.o VectorMaker.o main.o
	g++ ${out}bst.o ${out}VectorMaker.o ${out}main.o -o ${out}main

main.o:
	g++ -c ${src}main.cpp -o ${out}main.o

bst.o:
	g++ -c ${src}bst.cpp -o ${out}bst.o

VectorMaker.o:
	g++ -c ${src}VectorMaker.cpp -o ${out}VectorMaker.o

run:
	.\${out}main.exe

clean:
	del output\*.o
	del output\*.exe
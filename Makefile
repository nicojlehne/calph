all:
	gcc -Os -s -fno-ident -fno-asynchronous-unwind-tables -o ./calph/calph ./calph/calph.c

exe:
	x86_64-w64-mingw32-gcc -Os -s -fno-ident -fno-asynchronous-unwind-tables -o ./calph/calph.exe ./calph/calph.c 

clean:
	rm -f ./calph/calph
	rm -f ./calph/calph.exe

run:
	./calph/calph

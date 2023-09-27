all:
	gcc -Os -s -fno-ident -fno-asynchronous-unwind-tables -o ./calph/calph ./calph/calph.c

clean:
	rm -f ./calph/calph

run:
	./calph/calph

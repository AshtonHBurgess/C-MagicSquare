ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	OUT_FILE=a
else
	OUT_FILE=a.out
endif

a.out:
	gcc -o ${OUT_FILE} src/main.c  src/magicSquare.c

clean:
	rm main

test: a.out
	bash test.sh
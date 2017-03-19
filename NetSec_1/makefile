all:
	gcc unshadow.c -o unshadow
	gcc guessword.c -o guessword -lcrypt
runall:
	./unshadow /tmp/passwd /tmp/shadow
	./guessword -i passwordfile.txt -d dictionary.txt -o all
all:
	gcc createsBinaryFilesList.c -o createsBinaryFilesList
	gcc scanner.c -o scanner -lcrypto -lssl
	gcc virus.c -o virus

runall:
	./createsBinaryFilesList
	./scanner
	# ./virus

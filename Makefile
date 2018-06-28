default: main.c
	g++ -o ./bin/main.exe main.c
run:
	./bin/main.exe
clean:
	rm -rf ./bin/main.exe
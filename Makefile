default: src/main.c src/safeitoa.c
	g++ -o bin/main.exe src/main.c src/safeitoa.c
run:
	bin/main.exe
clean:
	rm -rf bin/main.exe
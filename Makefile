default: src/main.c src/safeitoa.c
	gcc -o bin/main.exe src/main.c src/safeitoa.c -O3
run:
	bin/main.exe
clean:
	rm -rf bin/main.exe
make test:
	gcc -o bin/main.exe src/main.c src/safeitoa.c -O3 
	bin/main.exe
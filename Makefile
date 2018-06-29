default: src/main.c src/safeitoa.c
	gcc -o bin/paginacao src/main.c src/safeitoa.c -O3
run:
	bin/main
clean:
	rm -rf bin/paginacao
make test:
	gcc -o bin/paginacao src/main.c src/safeitoa.c -O3 
	bin/paginacao
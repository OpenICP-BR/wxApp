.PHONY: all run

all: bin/OpenICP-BR

bin/OpenICP-BR: src/*
	-mkdir bin
	cd src && go build -i -o ../bin/OpenICP-BR

run: bin/OpenICP-BR
	./bin/OpenICP-BR
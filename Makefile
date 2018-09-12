ANSI_RED="\033[0;31m"
ANSI_GREEN="\033[0;32m"
ANSI_BLUE="\033[0;34m"
ANSI_RESET="\033[0m"

ifneq ("$(wildcard /usr/local/opt/coreutils/libexec/gnubin/echo)","")
	ECHO="/usr/local/opt/coreutils/libexec/gnubin/echo"
else
	ECHO="/bin/echo"
endif
ifeq ($(NO_CACHE), "true")
	GOFLAGS=-v
else
	GOFLAGS=-v -i
endif

.PHONY: all run

all: bin/OpenICP-BR

bin/OpenICP-BR: src/*
	-mkdir bin
	@$(ECHO) -e $(ANSI_GREEN)"["$@"] Fixing imports..."$(ANSI_RESET)
	cd src && goimports -w .
	@$(ECHO) -e $(ANSI_GREEN)"["$@"] Formatting code..."$(ANSI_RESET)
	cd src && go fmt
	@$(ECHO) -e $(ANSI_GREEN)"["$@"] Compiling code..."$(ANSI_RESET)
	cd src && go build $(GOFLAGS) -o ../$@
	@$(ECHO) -e $(ANSI_BLUE)"["$@"] Finished target $@"$(ANSI_RESET)

run: bin/OpenICP-BR
	./bin/OpenICP-BR

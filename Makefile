MAKEARGS = --no-print-directory

all: compile interpret
compile:
	cd compiler && make $(MAKEARGS) all
interpret:
	cd interpreter && make $(MAKEARGS) interpret
clean:
	cd compiler && make $(MAKEARGS) clean
	cd interpreter && make $(MAKEARGS) clean

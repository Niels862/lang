all: compile interpret
compile:
	cd compiler && make all
interpret:
	cd interpreter && make interpret
clean:
	cd compiler && make clean
	cd interpreter && make clean

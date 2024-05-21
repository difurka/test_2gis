STD=--std=c++20
WFLAGS=-Wall -Wextra -Werror
words:
	g++ $(STD) $(WFLAGS) start.cpp -o start
	./start -f CharlesDickens-OliverTwist_68.txt -v mother -m words


checksum:
	g++ $(STD) $(WFLAGS) start.cpp -o start
	./start -f file_checksum.txt -m checksum

help:
	g++ $(STD) $(WFLAGS) start.cpp -o start
	./start -h

incorrect_command:
	g++ $(STD) $(WFLAGS) start.cpp -o start
	./start -f CharlesDickens-OliverTwist_68.txt -v mother -m words -y iii


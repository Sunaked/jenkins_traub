all: build
	(cd build && cmake .. && make && echo "\n\n" && ./jenkins_traub)

clean:
	rm -rf build

.PHONY: all clean

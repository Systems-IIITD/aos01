SRC=$(wildcard *.c)
DST=$(patsubst %.c,%,$(SRC))

default: $(DST)

%: %.c
	gcc -o $@ $^

clean:
	rm -rf $(DST)

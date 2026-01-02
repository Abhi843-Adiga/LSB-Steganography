var:=$(patsubst %.c,%.o,$(wildcard *.c))
steg.exe:$(var)
	gcc -o $@ $^
clean:
	rm *.o *.exe
CFLAGS = -std=c99 -Wall

test: ../src/ex_string.o test_ex_string.o test_main.o
	$(CC) $^ -g -o $@ -lcunit

%.o: %.c
	$(CC) $< -g -c -o $@ $(CFLAGS)

clean:
	rm -f test *.o

.PHONY: clean

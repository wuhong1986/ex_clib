CFLAGS =  -Wall

test:../src/ex_file.o ../src/ex_string.o test_ex_file.o test_ex_string.o test_main.o
	$(CC) $^ -g -o $@ -lcunit

%.o: %.c
	$(CC) $< -g -c -I../include -o $@ $(CFLAGS)

clean:
	rm -f test *.o

.PHONY: clean

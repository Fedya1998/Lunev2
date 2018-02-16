FILES:=stack.o structure.o iter.o test.o
all: stack_test

stack_test: $(FILES)
	g++ -o $@ $^

-include *.d

%.o: %.c
	g++ -MD -o $@ -g $<

clean:
	rm -rf stack_test *.o *.d *.gcov *.gcno *.gcda


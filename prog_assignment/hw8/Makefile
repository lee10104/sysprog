targets := $(patsubst %.c,%,$(wildcard *.c))

help:
	@echo "make <command> where <command> is one of"
	@echo ""
	@echo " help        This help screen."
	@echo " run         Run your solution."
	@echo " clean       Remove binaries and test files."

lib%.so: %.c
	$(CC) -shared -fPIC -o $@ $< -ldl

%: %.c
	$(CC) -o $@ $<

clean:
	rm -f *.so *.o $(targets)

run: test libintercept.so
	@echo "*** Without library interpositioning ***"
	@echo
	@./test
	@echo
	@echo
	@echo "*** With library interpositioning ***"
	@echo
	@LD_PRELOAD=./libintercept.so ./test
	@echo


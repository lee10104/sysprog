targets := $(patsubst %.c,%,$(wildcard *.c))

help:
	@echo "make <command> where <command> is one of"
	@echo ""
	@echo " help        This help screen."
	@echo " compile     Compile your solution."
	@echo " test        Test your solution."
	@echo " submit      Create a submission file."
	@echo " clean       Remove binaries and test files."

%: %.c
	$(CC) -o $@ $<

compile: $(targets)

test: compile
	@./manifest .
	@md5sum -c manifest.txt
	@echo ""
	@echo "Test passed."

submit: clean
	@tar cvzf hw9.submission.tgz Makefile manifest.c STUDENT.ID
	@echo ""
	@echo "Submission file prepared (hw9.submission.tgz); email to TA manually."

clean:
	@rm -f $(targets) manifest.txt hw9.submission.tgz



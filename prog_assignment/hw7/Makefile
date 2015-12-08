help:
	@echo "make <command> where <command> is one of"
	@echo ""
	@echo "  help                This help screen."
	@echo "  copy                Compile the copy.c program."
	@echo "  test                Test your solution."
	@echo "  test_files          Generate test files for the copy test."
	@echo "  clean               Remove the copy binary and test files."
	@echo ""

copy: copy.c
	@gcc -O2 -o $@ $<

test_files:
	@echo "Creating test files in temp/..."
	@mkdir -p temp
	@openssl rand     1000 > temp/dst.1.dat
	@openssl rand   100000 > temp/dst.2.dat
	@openssl rand 10000000 > temp/dst.3.dat
	@md5sum temp/dst.1.dat > temp/dst.1.md5
	@md5sum temp/dst.2.dat > temp/dst.2.md5
	@md5sum temp/dst.3.dat > temp/dst.3.md5
	@mv temp/dst.1.dat temp/src.1.dat
	@mv temp/dst.2.dat temp/src.2.dat
	@mv temp/dst.3.dat temp/src.3.dat
	@echo "Done."

test: copy
	@if [ ! -f temp/src.1.dat ]; then echo "Test files not found. Run '$$ make test_files' first."; false; fi;
	@echo "Testing buffer copy..."
	@rm -f temp/dst.*.dat
	./copy temp/src.1.dat temp/dst.1.dat 1
	@if (md5sum -c temp/dst.1.md5 2>&1) > /dev/null; then echo "  Passed."; else echo "  *** Failed."; false; fi
	./copy temp/src.2.dat temp/dst.2.dat 1
	@if (md5sum -c temp/dst.2.md5 2>&1) > /dev/null; then echo "  Passed."; else echo "  *** Failed."; false; fi
	./copy temp/src.3.dat temp/dst.3.dat 1
	@if (md5sum -c temp/dst.3.md5 2>&1) > /dev/null; then echo "  Passed."; else echo "  *** Failed."; false; fi
	@echo ""
	@echo "Testing mmap copy..."
	@rm -f temp/dst.*.dat
	./copy temp/src.1.dat temp/dst.1.dat 1
	@if (md5sum -c temp/dst.1.md5 2>&1) > /dev/null; then echo "  Passed."; else echo "  *** Failed."; false; fi
	./copy temp/src.2.dat temp/dst.2.dat 1
	@if (md5sum -c temp/dst.2.md5 2>&1) > /dev/null; then echo "  Passed."; else echo "  *** Failed."; false; fi
	./copy temp/src.3.dat temp/dst.3.dat 1
	@if (md5sum -c temp/dst.3.md5 2>&1) > /dev/null; then echo "  Passed."; else echo "  *** Failed."; false; fi
	@echo ""
	@echo "All passed."

clean:
	@rm -rf copy temp

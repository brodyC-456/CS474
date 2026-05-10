.PHONY: clean pristine test


testfs: testfs.c libvvsfs.a
	gcc -DCTEST_ENABLE -o $@ $^

libvvsfs.a: image.o block.o
	ar rcs $@ $^

image.o: image.c
	gcc -Wall -Wextra -c $<

block.o: block.c
	gcc -Wall -Wextra -c $<

clean:
	rm -f *.o

pristine:
	rm -f *.o *.a testfs

test: testfs
	./testfs




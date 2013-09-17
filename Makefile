CFLAGS=-g -O3 -std=c99 -Wall -Werror -Iinclude -DNDEBUG $(OPTFLAGS)
LIBS=$(OPTLIBS)
PREFIX?=/usr/local

# SOURCES=$(filter-out src/reg/parser.c, $(wildcard src/**/*.c src/*.c))
SOURCES=$(wildcard src/**/*.c src/*.c)

OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libreg.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: parser $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -std=c99 -Wall -Iinclude -Werror $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
				ar rcs $@ $(OBJECTS)
				ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
				$(CC) -shared -o $@ $(OBJECTS)

build:
				@mkdir -p build

src/reg/parser.c: src/reg/parser.leg peg
	./deps/peg/leg -o src/reg/parser.c src/reg/parser.leg

parser: src/reg/parser.c

peg: deps/peg/Makefile
	$(MAKE) -C deps/peg

# The Unit Tests
.PHONY: tests
$(TESTS): tests/%: tests/%.c
				$(CC) $(CFLAGS) $< -o $@ $(TARGET)
tests: $(TESTS)
				sh ./tests/runtests.sh

valgrind:
				VALGRIND="valgrind" $(MAKE)

# The Cleaner
clean:
				rm -rf build $(OBJECTS) $(TESTS)
				rm -f tests/tests.log
				rm -rf `find . -name "*.dSYM" -print`
				rm -rf `find . -name "*.o" -print`
				rm -rf `find . -name "*.leg.c" -print`
				$(MAKE) -C deps/peg clean

# The Install
install: all
				install -d $(DESTDIR)/$(PREFIX)/lib/
				install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
				@echo Files with potentially dangerous functions.
				@egrep $(BADFUNCS) $(SOURCES) || true

# libreg [![Build Status](https://travis-ci.org/txus/libreg.png)](https://travis-ci.org/txus/libreg)

Simple regular expressions library implemented as non-deterministic
finite-state automata. No fancy features, *very* basic.

Design inspired by [Understanding Computation][book], an amazing book by Tom Stuart.

## Usage

```c
#include <reg/reg.h>

unsigned int matched = 0;

Reg *regex = Reg_compile("ab|c");

matched = Reg_match(regex, "ac"); // matched! 1
matched = Reg_match(regex, "abc"); // not matched! 0

Reg_destroy(regex);
```

### Installing it as a submodule

    $ cd <your_project>
    $ mkdir -p deps
    $ git submodule add git://github.com/txus/libreg deps/libreg

In your Makefile, add this to your `CFLAGS`:

    CFLAGS=<whatever> -Ideps/libreg/include

And this to your LDFLAGS:

    LDFLAGS=<whatever> deps/libreg/build/libreg.a

Create a `libreg` target in your Makefile:

```make
libreg:
  $(MAKE) -C deps/libreg
```

And finally add it as a dependency of your main target:

```make
all: libreg <your> <other> <targets>
```

Done! :)

## Development

To build libreg and run its test suite:

    $ git clone git://github.com/txus/libreg
    $ cd libreg
    $ make

If you want to run with Valgrind to ensure there are no memory leaks:

    $ make valgrind

Tested in Mac OSX 10.8 and Linux.

## Dependencies

We build the parser using a vendored version of Ian Piumarta's peg/leg library:

  http://piumarta.com/software/peg/

## Who's this

This was made by [Josep M. Bach (Txus)](http://txustice.me) under the MIT
license. I'm [@txustice][twitter] on twitter (where you should probably follow
me!).

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

[twitter]: https://twitter.com/txustice
[book]: http://computationbook.com/
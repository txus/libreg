# libreg [![Build Status](https://travis-ci.org/txus/libreg.png)](https://travis-ci.org/txus/libreg)

Regular expressions library implemented as non-deterministic finite-state
automata.

Design inspired by "Understanding Computation", an amazing book by Tom Stuart.

## Using

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

### Interface

...

## Development

To build libreg and run its test suite:

    $ git clone git://github.com/txus/libreg
    $ cd libreg
    $ make

If you want to run with Valgrind to ensure there are no memory leaks:

    $ make valgrind

Tested in Mac OSX 10.8 and Linux.

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
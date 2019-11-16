# Debugging Python with `gdb`

You would need a Python interpreter compiled with debug symbols.
Some Linux distributions offer debug packages, but if not, you can
download CPython's source code, and compile it by yourself.

Personally I use the following configure line, to get more information
out of the interpreter.

`./configure --prefix=/your/final/install/path  --enable-shared CFLAGS="-O0 -fno-inline -fno-omit-frame-pointer -g" LDFLAGS="-O0" CPPFLAGS="-O0" OPT="-O0 -g"`

## Start debugging

You can start `gdb` using this `hack.py` file, running:

`gdb --args python hack.py`

Inside that, you can set a breakpoint into the `main()` function,
try typing:

`b main`

And now you can run the script:

`r`

Once there, you can list the close lines to that one, with:

`l`

Of course there are many other aspects of debugging, but this is
just for the first step.

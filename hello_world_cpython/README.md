# Write your first CPython module

The idea of this example, is to get started writing Python modules
using CPython.

Once everything is in place, we would like to achieve the following
module interaction (`main.py`):

```
import simple
print(simple.hello())
```

To be able to use that snippet, first we need to compile the code (`simple.c`):

```
#include <Python.h>

static PyObject* simple_hello(PyObject* self, PyObject* args){
    char *msg = "Hello Python Pizza Hamburg 2019!";
    return Py_BuildValue("s", msg);
}

static PyMethodDef simple_funcs[] = {
    {"hello", (PyCFunction)simple_hello, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef simplemodule = {
    PyModuleDef_HEAD_INIT,
    "simple",
    NULL,
    -1,
    simple_funcs
};

PyMODINIT_FUNC PyInit_simple(void){
    return PyModule_Create(&simplemodule);
}
```

First, we have a function called `simple_hello`.
This function will be in charge of just return a value based on a `char*`
message.

Secondly, you see that we are defining all the functions for the module `simple`,
this is done by creating the `simple_funcs[]` with entries per function,
the first line of the body is the one regarding our function `simple_hello`.

Third, you see the definition of the module `simplemodule`, including the
module definition, the name, and the list of functions inside of it.

Last, the initialization of the method, via executing `PyModule_Create`
referencing our `simplemodule` structure.


To build that code, I wrote a `Makefile` that you can use,
but the main idea is just to execute:

```
python setup.py install --user
```

This will place the `simple` module in the user space, or in the active
Python enviroment.

This weird `setup.py` file contains the instructions to build a Python
module, and the content is pretty straightforward: You define a `name`,
a `version`, the `ext_modules` and its dependencies, in this case our `simple.c`
file:

```
from distutils.core import setup, Extension

setup(name='simple', version='1.0',
      ext_modules=[Extension('simple', ['simple.c'])])
```

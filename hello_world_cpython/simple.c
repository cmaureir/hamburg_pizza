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

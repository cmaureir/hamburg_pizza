# CPython

For this example I used the master branch
on the commit `befa032d8869e0fab4732d910f3887642879d644`.
If you are not using that, maybe the patch will work without any problem,
but if you want to be sure, just checkout that specific state.

To apply the patch, just execute:

```
git apply list_ask_play.patch
```

This patch will add the functions `ask` and `play` to any `list` object.

## Extending the list

For this process, I copied the base idea of the function `list_append`
and started include questions that were accepted on the `ask` method.

The documentation was a really important factor too,
for this you need just to modify `Objects/clinic/listobject.c.h`
to include the `__doc__` entry for your function, for example:

```
PyDoc_STRVAR(list_ask__doc__,
"ask($self, object, /)\n"
"--\n"
"\n"
"Ask the list a question.");
```

To add new methods to objects, one need to include them into `Objects/listobject.c`
particularly the `list_methods[]` method definition:

```
LIST_CLEAR_METHODDEF
LIST_COPY_METHODDEF
LIST_APPEND_METHODDEF
LIST_ASK_METHODDEF <--- new line
```

That macro, inside `Objects/clinic/listobject.c.h` expands into:

```
#define LIST_ASK_METHODDEF    \
    {"ask", (PyCFunction)list_ask, METH_O, list_ask__doc__},
```

Finally,
our new function `list_ask` is nothing else that a function that compares
the argument to a certain string, and execute something if there is a match:

```
static PyObject *
list_ask(PyListObject *self, PyObject *object)
/*[clinic end generated code: output=7c096003a29c0eae input=43a3fe48a7066e91]*/
{
    PyObject* str = PyUnicode_AsUTF8String(object);
    const char *bytes = PyBytes_AsString(str);

    if (!strcmp(bytes, "how are you?"))
    {
        slow_print("Good, time to time broken, since I'm the master branch.");
    }
    ...
```

The `slow_print` is just a function that combines `printf` with `usleep`
to make the effect of someone writing:

```
static void slow_print(char *in)
{
    char *i;
    for (i = in; *i != '\0'; i++) {
        printf("%c", *i);
        fflush(stdout);
        if (*i == ',')
            usleep(400000);
        else
            usleep(90000);
    }
    printf("\n");
}
```

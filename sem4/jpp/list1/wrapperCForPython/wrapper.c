#include "wrapper.h"

#include <Python.h>
#include <stdlib.h>

void initPython() {
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('../libraryPython/')");
}

unsigned long factorial(unsigned long n) {
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    unsigned long result;

    initPython();
    pName = PyUnicode_FromString("math_lib");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "factorial");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            PyTuple_SetItem(pArgs, 0, PyLong_FromUnsignedLong(n));
            pValue = PyObject_CallObject(pFunc, pArgs);
            result = PyLong_AsUnsignedLong(pValue);
            Py_DECREF(pArgs);
            Py_XDECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    return result;
}

unsigned long factorialRecursive(unsigned long n) {
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    unsigned long result;

    initPython();
    pName = PyUnicode_FromString("math_lib");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "factorial_recursive");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            PyTuple_SetItem(pArgs, 0, PyLong_FromUnsignedLong(n));
            pValue = PyObject_CallObject(pFunc, pArgs);
            result = PyLong_AsUnsignedLong(pValue);
            Py_DECREF(pArgs);
            Py_XDECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    return result;
}

unsigned int gcd(unsigned int a, unsigned int b) {
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    unsigned int result;

    initPython();
    pName = PyUnicode_FromString("math_lib");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "gcd");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            PyTuple_SetItem(pArgs, 0, PyLong_FromUnsignedLong(a));
            PyTuple_SetItem(pArgs, 1, PyLong_FromUnsignedLong(b));
            pValue = PyObject_CallObject(pFunc, pArgs);
            result = PyLong_AsUnsignedLong(pValue);
            Py_DECREF(pArgs);
            Py_XDECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    return result;
}

unsigned int gcdRecursive(unsigned int a, unsigned int b) {
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    unsigned int result;

    initPython();
    pName = PyUnicode_FromString("math_lib");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "gcd_recursive");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            PyTuple_SetItem(pArgs, 0, PyLong_FromUnsignedLong(a));
            PyTuple_SetItem(pArgs, 1, PyLong_FromUnsignedLong(b));
            pValue = PyObject_CallObject(pFunc, pArgs);
            result = PyLong_AsUnsignedLong(pValue);
            Py_DECREF(pArgs);
            Py_XDECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    return result;
}

int gcdI(int a, int b) {
    if (b == 0) {
        return a;
    }

    int r;
    while (a % b > 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return b;
}

DiophantineEquationSolution diophantine(int a, int b, int c) {
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    DiophantineEquationSolution solution = {0, 0};

    initPython();
    pName = PyUnicode_FromString("math_lib");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "diophantine");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);
            PyTuple_SetItem(pArgs, 0, PyLong_FromLong(a));
            PyTuple_SetItem(pArgs, 1, PyLong_FromLong(b));
            PyTuple_SetItem(pArgs, 2, PyLong_FromLong(c));

            pValue = PyObject_CallObject(pFunc, pArgs);
            PyObject *pX = PyObject_GetAttrString(pValue, "x");
            PyObject *pY = PyObject_GetAttrString(pValue, "y");
            solution.x = PyLong_AsLong(pX);
            solution.y = PyLong_AsLong(pY);

            Py_DECREF(pX);
            Py_DECREF(pY);
            Py_DECREF(pArgs);
            Py_DECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    return solution;
}

DiophantineEquationSolution diophantineRecursive(int a, int b, int c) {
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    DiophantineEquationSolution solution = {0, 0};

    initPython();
    pName = PyUnicode_FromString("math_lib");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "diophantine_recursive");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);
            PyTuple_SetItem(pArgs, 0, PyLong_FromLong(a));
            PyTuple_SetItem(pArgs, 1, PyLong_FromLong(b));
            PyTuple_SetItem(pArgs, 2, PyLong_FromLong(c));

            pValue = PyObject_CallObject(pFunc, pArgs);
            PyObject *pX = PyObject_GetAttrString(pValue, "x");
            PyObject *pY = PyObject_GetAttrString(pValue, "y");
            solution.x = PyLong_AsLong(pX);
            solution.y = PyLong_AsLong(pY);

            Py_DECREF(pX);
            Py_DECREF(pY);
            Py_DECREF(pArgs);
            Py_XDECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    return solution;
}

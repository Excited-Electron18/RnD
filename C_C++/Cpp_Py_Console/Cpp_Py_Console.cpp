// Cpp_Py_Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

int main(int argc, char* argv[])
{
    PyObject* pName, * pModule, * pFunc;
    PyObject* pArgs, * pValue;
    int i;

    if (argc < 3) {
        fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
        return 1;
    }

    unsigned char File_Name[10];
    unsigned char Fun_Name[10];
    int arg1[2];


    Py_Initialize();
    printf("Enter the Python File Name\r\n");
    scanf_s("%s",File_Name,(unsigned)size_t(File_Name));
    pName = PyUnicode_DecodeFSDefault((char *)File_Name);
    /* Error checking of pName left out */

    printf("Enter the Python Function Name to Call\r\n");
    scanf_s("%s",Fun_Name, (unsigned)size_t(Fun_Name));

    printf("Enter the Arguments 1 for Function\r\n");
    scanf_s("%d", &arg1[0]);
    printf("Enter the Arguments 2 for Function\r\n");
    scanf_s("%d",&arg1[1]);

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, (char *)Fun_Name);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            for (i = 0; i < 2; ++i) {
                pValue = PyLong_FromLong(arg1[i]);
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr, "Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", Fun_Name);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", File_Name);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
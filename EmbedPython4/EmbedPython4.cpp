#include <Python.h>
#include <iostream>
using namespace std;

int
main(int argc, char* argv[])
{
    PyObject* pName, * pModule, * pFunc;
    PyObject* pArgs, * pValue;
    int i;

    if (argc < 3) {
        fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
        return 1;
    }

    Py_Initialize();


    pName = PyUnicode_FromString(argv[1]);
    /* Error checking of pName left out */
    //cout << pName;

    pModule = PyImport_Import(pName);
    
    Py_DECREF(pName);
       
   
    
    pFunc = PyObject_GetAttrString(pModule, argv[2]);
    /* pFunc is a new reference */

    if (PyCallable_Check(pFunc))
    {
        // Prepare the argument list for the call
        if (argc > 3)
        {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; i++)
            {
                pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue)
                {
                    PyErr_Print();
                    return 1;
                }
                PyTuple_SetItem(pArgs, i, pValue);
            }

            pValue = PyObject_CallObject(pFunc, pArgs);

            if (pArgs != NULL)
            {
                Py_DECREF(pArgs);
            }
        }
        else
        {
            pValue = PyObject_CallObject(pFunc, NULL);
        }

        if (pValue != NULL)
        {
            printf("Return of call : %d\n", PyLong_AsLong(pValue));
            Py_DECREF(pValue);
        }
        else
        {
            PyErr_Print();
        }

        // some code omitted...
    }
    Py_Finalize();
    return 0;
}


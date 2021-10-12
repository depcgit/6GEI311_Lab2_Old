#include <Python.h>
#include <string>
#include <iostream>
#include "MediaPlayer.h"

static PyObject* random(PyObject* self, PyObject* args)
{
	srand(time(NULL));
	int random = rand() % 10;
	PyObject* python_val = Py_BuildValue("i", random);
	return python_val;
}

static PyObject* Start(PyObject* self, PyObject* args)
{
	wstring path_input = L"C:/Users/Raphaelle/Documents/UniDocs/Automne 2021/Architecture_logiciels/6GEI311_lab1/Example.avi";
	LPCWSTR path = path_input.c_str();
	MediaPlayer* mediaPlayer = MediaPlayer::getInstance();
	mediaPlayer->Start(path);
	mediaPlayer->Run();
	return Py_BuildValue("i", 0);
}

static PyObject* PlayPause(PyObject* self, PyObject* args)
{
	std::cout << "Play ou paaaause" << endl;
	return Py_BuildValue("i", 0);
}

static PyObject* Quit(PyObject* self, PyObject* args)
{
	std::cout << "Quit" << endl;
	return Py_BuildValue("i", 0);
}

static PyObject* Replay(PyObject* self, PyObject* args)
{
	std::cout << "Replay" << endl;
	return Py_BuildValue("i", 0);
}

static PyObject* Accelerate(PyObject* self, PyObject* args)
{
	std::cout << "Accelerate" << endl;
	return Py_BuildValue("i", 0);
}
/*static PyObject* random(PyObject* self, PyObject* args)
{
	srand(time(NULL));
	int random = rand() % 10;
	PyObject* python_val = Py_BuildValue("i", random);
	return python_val;
}*/

static PyMethodDef methods[] = {
	{"random", (PyCFunction)random, METH_NOARGS,
	"stuff"},
	{"PlayPause", (PyCFunction)PlayPause, METH_NOARGS,
	"stuff"},
	{"Replay", (PyCFunction)Replay, METH_NOARGS,
	"stuff"},
	{"Accelerate", (PyCFunction)Accelerate, METH_NOARGS,
	"stuff"},
	{"Quit", (PyCFunction)Quit, METH_NOARGS,
	"stuff"},
	{"Start", (PyCFunction)Start, METH_NOARGS,
	"stuff"},
	{NULL, NULL, 0, NULL}
};


static PyModuleDef Lab2 =
{
	PyModuleDef_HEAD_INIT,
	"math_demo",
	"NULL",
	0,
	methods
};

PyMODINIT_FUNC PyInit_Lab2(void)
{
	//Py_Initialize();
	return PyModule_Create(&Lab2);
}

//sys.path.append("C:\\Users\\depchouina\\Desktop\\6GEI311_Lab2\\C++\\test2\\x64\\Release")



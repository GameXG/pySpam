#include<Python.h>  
//自定义异常  
static PyObject* SpamError;
//模块的功能函数  
static PyObject* spam_system(PyObject* self, PyObject* args)
{
	const char* command;
	int sts;
	if (!PyArg_ParseTuple(args, "s", &command))
		return NULL;
	sts = system(command);
	if (sts < 0) {
		PyErr_SetString(SpamError, "System command failed");
		return NULL;
	}
	return PyLong_FromLong(sts);
}
//方法表  
static PyMethodDef SpamMethods[] = {
	{ "system", spam_system, METH_VARARGS,
	"Execute a shell command." },
	{ NULL, NULL, 0, NULL }
};
//模块的结构体定义 v3.4  
/*
static struct PyModuleDef spammodule = {
PyModuleDef_HEAD_INIT,
"spam",
spam_doc,
-1,
SpamMethods
};*/
//模块初始化函数  
//PyMODINIT_FUNC PyInit_spam(void) // v3.4  
PyMODINIT_FUNC initspam(void)
{
	PyObject* m;
	//m = PyModule_Create(&spammodule); // v3.4  
	m = Py_InitModule("spam", SpamMethods);
	if (m == NULL)
		return;
	SpamError = PyErr_NewException("spam.error", NULL, NULL);
	Py_INCREF(SpamError);
	PyModule_AddObject(m, "error", SpamError);
}


// [例]编写、编译、通过Python调用扩展模块例子
// http://www.incoding.org/admin/archives/776.html


// 编写Python扩展（Extending Python with C or C++）
// http://blog.csdn.net/xiarendeniao/article/details/9374931
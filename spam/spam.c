#include<Python.h>  
//�Զ����쳣  
static PyObject* SpamError;
//ģ��Ĺ��ܺ���  
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
//������  
static PyMethodDef SpamMethods[] = {
	{ "system", spam_system, METH_VARARGS,
	"Execute a shell command." },
	{ NULL, NULL, 0, NULL }
};
//ģ��Ľṹ�嶨�� v3.4  
/*
static struct PyModuleDef spammodule = {
PyModuleDef_HEAD_INIT,
"spam",
spam_doc,
-1,
SpamMethods
};*/
//ģ���ʼ������  
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


// [��]��д�����롢ͨ��Python������չģ������
// http://www.incoding.org/admin/archives/776.html


// ��дPython��չ��Extending Python with C or C++��
// http://blog.csdn.net/xiarendeniao/article/details/9374931
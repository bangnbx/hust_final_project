#!/usr/bin/python2
import ctypes

#  encryptPy = ctypes.CDLL('/home/bangcht/projects/server/test/test.so')
#  encryptPy.encrypt.argtypes = (ctypes.c_int,ctypes.c_char_p)
#  encryptPy.encrypt.restype = None
#  hello = "hello there"
#  encryptPy.encrypt(len(hello),hello)

fingerPy = ctypes.CDLL('/usr/lib/libfprint.so.0')
fingerPy.fpi_compare_data_bang.argtypes = (ctypes.c_char_p, ctypes.c_char_p)
fingerPy.fpi_compare_data_bang.restype = ctypes.c_int

a = fingerPy.fpi_compare_data_bang('a', 'b')
print a

rm Project3
rm -f *.o
qmake Project3.pro -r -spec linux-g++
/usr/bin/make
sudo ./Project3

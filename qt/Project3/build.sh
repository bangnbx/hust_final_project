rm Project3
rm -f *.o
qmake Project3.pro -r -spec linux-g++
make
sudo ./Project3

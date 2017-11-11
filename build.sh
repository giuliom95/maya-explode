SRC="node"
STD="-std=c++11"

g++ $STD -c -I/usr/autodesk/maya2017/include -fPIC src/$SRC.cpp
g++ $STD -shared -o $SRC.so $SRC.o -L/usr/autodesk/maya2017/lib -lOpenMaya
rm *.o
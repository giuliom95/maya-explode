SRC="node"
OUT="explode"
STD="c++11"

g++ -std=$STD -c -I/usr/autodesk/maya2017/include -fPIC src/$SRC.cpp
g++ -std=$STD -shared -o $OUT.so *.o -L/usr/autodesk/maya2017/lib -lOpenMaya
rm *.o
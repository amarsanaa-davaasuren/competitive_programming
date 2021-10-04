g++ -O2 -std=c++14 -I . -Wall "-Wl,--stack=1073741824" mrsn.cpp -o mrsn.exe
cmd /c '.\mrsn.exe < .\in.txt > .\out.txt'

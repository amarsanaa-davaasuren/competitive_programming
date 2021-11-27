rm bit.exe
g++ -O2 -std=c++17 -Wall "-Wl,--stack=1073741824" bit.cpp -o bit.exe
cmd /c '.\bit.exe < .\in.txt > .\out.txt'


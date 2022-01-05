rm swag.exe
g++ -O2 -std=c++17 -Wall "-Wl,--stack=1073741824" swag.cpp -o swag.exe
cmd /c '.\swag.exe < .\in.txt > .\out.txt'

rm SWAG.exe
g++ -O2 -std=c++17 -Wall "-Wl,--stack=1073741824" SWAG.cpp -o main.exe
cmd /c '.\SWAG.exe < .\in.txt > .\out.txt'

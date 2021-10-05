g++ -O2 -std=c++17 -Wall "-Wl,--stack=1073741824" main.cpp -o main.exe
cmd /c '.\main.exe < .\in.txt > .\out.txt'

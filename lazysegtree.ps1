rm lazy_segtree.exe
g++ -O2 -std=c++17 -Wall "-Wl,--stack=1073741824" lazy_segtree.cpp -o lazy_segtree.exe
cmd /c '.\lazy_segtree.exe < .\in.txt > .\out.txt'
#Set-Alias a .\a

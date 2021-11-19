rm prime_sieve.exe
g++ -O2 -std=c++17 -Wall "-Wl,--stack=1073741824" prime_sieve.cpp -o prime_sieve.exe
cmd /c '.\prime_sieve.exe < .\in.txt > .\out.txt'
#Set-Alias a .\a

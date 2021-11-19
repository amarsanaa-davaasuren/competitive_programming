<<<<<<< HEAD
=======
rm main.exe
>>>>>>> c21eaddef4e82fb7953da281c7be3efeb5130ddb
g++ -O2 -std=c++17 -Wall "-Wl,--stack=1073741824" main.cpp -o main.exe
cmd /c '.\main.exe < .\in.txt > .\out.txt'
#Set-Alias a .\a

# Stage 1: Install OpenSSL and some basic tools

***WARNING:*** These instructions are not working :(

1. Download and install MSYS2.
2. Open MSYS MinGW as Administrator.
2. Run ```pacman -S  make perl nasm vmake mingw-w64-x86_64-gcc ```.
3. Run ```wget https://www.openssl.org/source/openssl-1.1.0h.tar.gz```.
4. Extract and enter the openssl directory.
5. Run ```export PATH="/c/msys64/mingw64/bin:$PATH"```.
6. Run ```mkdir /usr/local/openssl-1.1```.
6. Run ```./Configure --prefix=/usr/local/openssl-1.1 no-idea no-mdc2 no-rc5 shared mingw64```.
7. Run ```make depend && make```.
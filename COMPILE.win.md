# Stage 1: Install OpenSSL and some basic tools


1. Download and install MSYS2.
2. Open MSYS MinGW as Administrator.
3. Run: ```pacman -S  make perl cmake git mingw-w64-i686-gcc mingw32/mingw-w64-i686-wxWidgets```.
4. Clone repository: ```git clone github.com/gjvnq/OpenICP-BR```.
5. Enter: ```cd OpenICP-BR```.
6. Run: ```export PATH="/c/msys64/mingw32/bin:$PATH"```.
7. Configure: ```cmake -G "MSYS Makefiles"```
8. Compile OpenSSL

  1. Enter: ```cd openssl-1.1.0h```
  2. Configure: ```./Configure mingw --prefix="`pwd`/dist" --openssldir="`pwd`/dist" no-dso```.
  3. Compile: ```make depend && make```.
  4. "Install": ```make install```.

9. Configure: ```cmake -G "MSYS Makefiles"```
10. Compile: ```make openicp```.
11. 
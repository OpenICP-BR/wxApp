# Stage 1: Install basic tools

1. Download and install MSYS2.
2. Open MSYS MinGW as Administrator.
3. Run: ```pacman -S unzip make perl cmake git mingw-w64-i686-gcc mingw-w64-i686-glib2 mingw-w64-i686-glibmm```.
4. Clone repository: ```git clone github.com/gjvnq/OpenICP-BR```.
5. Run: ```export PATH="/c/msys64/mingw32/bin:$PATH"```.

# Stage 2: Compile OpenSSL

1. Enter: ```cd OpenICP-BR/openssl-1.1.0h```
2. Run: ```mkdir dist```.
3. Configure: ```./Configure mingw shared no-asm -fleading-underscore -fPIC --prefix="`pwd`/dist" --openssldir="`pwd`/dist"```.
4. Compile: ```make CC=/c/msys64/mingw32/bin/gcc.exe -j4 all```.
5. "Install": ```make install```.
6. Hack: ```objcopy --remove-leading-char dist/lib/libcrypto.a dist/lib/libcrypto_no_leading_char.a```.

# Stage 3: Compile OpenICP-BR

1. Enter: ```cd OpenICP-BR```.
2. Set compiler: ```export CCX=/c/msys64/mingw32/bin/gcc.exe```.
3. Configure: ```cmake -G "MSYS Makefiles" .```
4. Compile: ```make openicp```.
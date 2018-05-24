# Stage 1: Install basic tools

1. Download and install MSYS2.
2. Open MSYS MinGW as Administrator.
3. Run: ```pacman -S unzip make perl cmake git mingw-w64-i686-gcc```.
4. Clone repository: ```git clone github.com/gjvnq/OpenICP-BR```.
5. Run: ```export PATH="/c/msys64/mingw32/bin:$PATH"```.

# Stage 2: Compile OpenSSL

1. Enter: ```cd OpenICP-BR/openssl-1.1.0h```
2. Run: ```mkdir dist```.
3. Configure: ```./Configure mingw shared no-asm -fPIC --prefix="`pwd`/dist" --openssldir="`pwd`/dist"```.
4. Compile: ```make CC=/c/msys64/mingw32/bin/gcc.exe -j4 all```.
5. "Install": ```make install```.
6. Hack: ```objcopy --remove-leading-char dist/lib/libcrypto.a dist/lib/libcrypto_no_leading_char.a```.

# Stage 3: Install wxWidgets 3.0.4

1. Download: ```wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.4/wxWidgets-3.0.4.zip```
2. Create directory:```mkdir wxWidgets-3.0.4```.
3. Extract it: ```cd wxWidgets-3.0.4 && unzip ../wxWidgets-3.0.4.zip```.
4. Configure: ```./configure --enable-unicode --enable-xrc```.
5. Compile: ```make```.
6. Install: ```make install_sw```.

# Stage 4: Compile OpenICP-BR

1. Enter: ```cd OpenICP-BR```.
2. Configure: ```cmake -G "MSYS Makefiles"```
3. Compile: ```make openicp```.
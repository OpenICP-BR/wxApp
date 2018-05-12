NOTE: Tested on Arch Linux.

  1. Clone repository: ```git clone github.com/gjvnq/OpenICP-BR```.
  2. Enter directory: ```cd OpenICP-BR```.
  3. Compile OpenSSL.
    1. Enter directory: ```cd openssl-1.1.0h```.
    2. Make directory: ```mkdir dist```.
    3. Configure: ```./Configure linux-x86_64 --prefix="`pwd`/dist" --openssldir="`pwd`/dist" no-shared```.
    5. Compile: ```make```. (SUGESTION: use ```-j4```to speed things up if you have multiple processors)
    6. "Install" it: ```make install```. (NOTE: this WON'T actually install it to your system, it will just copy the final files to the ``dist``` folder we have just created)
    7. Go back to our previous folder: ```cd ..```.
  4. Compile wxWidgets: (not verified)
    1. Enter directory: ```cd wxWidgets-3.0.4```.
    2. Make directory: ```mkdir -p dist/build```.
    3. Enter directory: ```cd dist/build```
    4. Configure: ```../../configure --prefix="`pwd`/../" --enable-clipboard --enable-controls --enable-dataviewctrl --enable-display --enable-dnd --enable-graphics_ctx --enable-std_string --enable-svg --enable-unicode --enable-webkit --with-expat --with-libjpeg --with-libpng --with-libtiff --with-opengl --with-osx_cocoa --with-zlib --disable-precomp-headers --enable-monolithic --disable-mediactrl --with-macosx-version-min=10.7 --enable-stl --disable-shared",```.
    5. Compile: ```make```. (SUGESTION: use ```-j4```to speed things up if you have multiple processors)
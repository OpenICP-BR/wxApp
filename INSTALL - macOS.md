  1. Clone repository: ```git clone github.com/gjvnq/OpenICP-BR```.
  2. Enter directory: ```cd OpenICP-BR```.
  3. Compile OpenSSL.
    1. Enter directory: ```cd openssl-1.1.0h```.
    2. Make directories: ```mkdir dist```.
    3. Configure: ```./Configure darwin64-x86_64-cc --prefix=`pwd`/dist --openssldir=`pwd`/dist```.
    4. Compile: ```make depend```.
    5. Compile more stuff: ```make```. (SUGESTION: use ```-j4```to speed things up if you have multiple processors)
    6. "Install" it: ```make install```. (NOTE: this WON'T actually install it to your system, it will just copy the final files to the ``dist``` folder we have just created)
  4. Compile wxWidgets:
    1. Enter directory: ```cd wxWidgets-3.0.4```.
    2.  
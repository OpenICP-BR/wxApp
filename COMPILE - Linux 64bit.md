NOTE: Tested on Arch Linux.

  1. Clone repository: ```git clone github.com/gjvnq/OpenICP-BR```.
  2. Enter directory: ```cd OpenICP-BR```.
  3. Compile OpenSSL.
    1. Enter directory: ```cd openssl-1.1.0h```.
    2. Make directory: ```mkdir dist```.
    3. Configure: ```./Configure linux-x86_64 --prefix="`pwd`/dist" --openssldir="`pwd`/dist" no-dso```.
    5. Compile: ```make```. (SUGESTION: use ```-j4```to speed things up if you have multiple processors)
    6. "Install" it: ```make install```. (NOTE: this WON'T actually install it to your system, it will just copy the final files to the ``dist``` folder we have just created)
    7. Go back to our previous folder: ```cd ..```.
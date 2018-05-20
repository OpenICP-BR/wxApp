  1. Install wxWidgets: `brew install wxmac`
  2. Clone repository: `git clone github.com/gjvnq/OpenICP-BR`.
  3. Enter directory: `cd OpenICP-BR`.
  4. Compile OpenSSL.
    1. Enter directory: `cd openssl-1.1.0h`.
    2. Make directory: `mkdir dist`.
    3. Configure: ``./Configure darwin64-x86_64-cc --prefix="`pwd`/dist" --openssldir="`pwd`/dist"``.
    4. Compile: `make depend`.
    5. Compile more stuff: `make`. (SUGESTION: use `-j4` to speed things up if you have multiple processors)
    6. "Install" it: `make install`. (NOTE: this WON'T actually install it to your system, it will just copy the final files to the `dist` folder we have just created)
    7. Go back to our previous folder: `cd ..`.
  5. Configure: `cmake .`
  6. Compile: `make openicp`. (SUGESTION: use `-j4` to speed things up if you have multiple processors)
  7. (OPTIONAL) Run with: `make run`
  8. (OPTIONAL) Generate the DMG file with: `make dmg`

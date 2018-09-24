NOTE: Tested on Ubuntu 18.04.

  1. Install dependencies: `apt-get install wx-common wx3.0-headers wx3.0-i18n git cmake build-essential golang`.
  2. Clone repository: `git clone github.com/gjvnq/OpenICP-BR`.
  3. Enter directory: `cd OpenICP-BR`.
  4. Download and compile libICP: `tools/libICP.sh`.
  5. Configure: `WX_CONFIG=/usr/bin/wx-config-gtk3 cmake .`.
  6. Compile and run: `make run`.
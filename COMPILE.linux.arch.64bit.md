NOTE: Tested on Arch Linux.

  1. Install wxWidgets: `pacman -S extra/wxgtk3`.
  2. Clone repository: `git clone github.com/gjvnq/OpenICP-BR`.
  3. Enter directory: `cd OpenICP-BR`.
  4. Download and compile libICP: `tools/libICP.sh`.
  5. Configure: `WX_CONFIG=/usr/bin/wx-config-gtk3 cmake .`.
  6. Compile and run: `make run`.
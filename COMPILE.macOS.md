  1. Install wxWidgets: `brew install wxmac`
  2. Clone repository: `git clone github.com/gjvnq/OpenICP-BR`.
  3. Enter directory: `cd OpenICP-BR`.
  4. Download and compile libICP: `tools/libICP.sh`.
  5. Configure: `cmake .`
  6. Compile: `make openicp`. (SUGESTION: use `-j4` to speed things up if you have multiple processors)
  7. (OPTIONAL) Run with: `make run`
  8. (OPTIONAL) Generate the DMG file with: `make dmg`

1. Download and install WinBuilds from http://win-builds.org/doku.php/download_and_installation_from_windows
	1. Install for Native Windows.
	2. Set the architecture to i686.
	3. Install to C:\WinBuild-i686
	4. Make sure the following packages will be installed: binutils, winpthreads, make, mingw-w64, gcc, gcc-g++. (In doubt, install all packages)
2. Install git.
	1. Use: checkout as-is, commit unix-style line endings.
	2. Use: minTTY.
	3. Enable symbolic links.
3. Open git bash.
	1. Run: export PATH="/c/WinBuild-i686/bin":$PATH


----------------

1. Download and install WinRAR from: https://www.win-rar.com
2. Install git.
	1. Use: checkout as-is, commit unix-style line endings.
	2. Use: minTTY.
3. Donwload and install Mingw-w64 from: http://mingw-w64.org/doku.php/download/mingw-builds
	1. Install it to: C:\mingw32
4. Install git.
	1. Use: checkout as-is, commit unix-style line endings.
	2. Use: minTTY.
	3. Enable symbolic links.
5. Open git bash.
	1. Run: export PATH=/c/mingw32/i686-w64-mingw32/bin/:/c/mingw32/bin:$PATH

-------

1. Install git.
	1. Use: checkout as-is, commit unix-style line endings.
	2. Use: minTTY.
	3. Enable symbolic links.
2. Install mingw from http://www.mingw.org/wiki/Getting_Started
	1. Install it to C:\MinGW
	2. Mark the following for installation: mingw-developer-toolkit, mingw32-base, mingw32-gcc-g++, msys-base, mingw32-pthreads-w32.
	3.
3. Install CMake from: https://cmake.org/download/
	1. Install it to: C:\CMake
4. Open git bash.
	1. Run: cp /c/MinGW/bin/mingw32-make.exe /c/MinGW/mingw32/bin/make.exe
	2. Run: echo "export PATH=/c/Go/bin:/c/MinGW/bin/:/c/MinGW/mingw32/bin/:/c/CMake/bin:\$PATH" >> ~/.bashrc
	2. Run: echo "export GOPATH=/c/goroot/" >> ~/.bashrc
	3. Run: source ~/.bashrc
5. Download TDM-GCC from http://tdm-gcc.tdragon.net
	1. Install to C:\TDM-GCC-32
6. Download and compile wxWidgets 3.0.4 "Windows Installer" (under source code). Direct link: https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.4/wxMSW-3.0.4-Setup.exe
	1. Compile wxWidgets
		1. On git bash, run: cd /c/wxWidgets-3.0.4/build/msw/
		2. Run: mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 BUILD=release clean
		3. Run: mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 BUILD=release CC="/c/TDM-GCC-32/bin/gcc.exe"
	2. Compile and test an example
		1. Run: cd c/wxWidgets-3.0.4/samples/controls
		2. Run: mingw32-make -f makefile.gcc LIBDIRNAME="/c/wxWidgets-3.0.4/lib/gcc_dll/" BUILD=release
		3. Run: cp /c/wxWidgets-3.0.4/lib/gcc_dll/*.dll gcc_mswu/
		4. Run: gcc_mswu/controls.exe
7. Download and install Golang from: https://golang.org
8. Make go root and clone the repository.
	1. Run: mkdir -pv /c/goroot/src/github.com/OpenICP-BR
	2. Run: cd /c/goroot/src/OpenICP-BR
	3. Run: git clone https://github.com/OpenICP-BR/wxApp
9. Compile OpenICP-BR
	1. Run: cd /c/goroot/src/github.com/OpenICP-BR/wxApp
	2. Set the correct branch: git checkout golang-libICP
	3. Download and compile libICP: ./tools/libICP.sh
	4. Configure: cmake . -G "Unix Makefiles"
	5. Compile: make
	6. Run: make run

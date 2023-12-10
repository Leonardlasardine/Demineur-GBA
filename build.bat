set PATH=D:\HAM\gcc-arm\bin;D:\HAM\tools\win32;%PATH%
set HAMDIR=D:\HAM
cd "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur"
del libham.h
echo #>libham.h
"D:\Program Files (x86)\Windows Resource Kits\Tools\timeit" -a make
make fixheader
make runvba
echo #define HAM_WITH_LIBHAM>libham.h

::make gdb
::make emu

set PATH=D:\HAM\gcc-arm\bin;D:\HAM\tools\win32;%PATH%
set HAMDIR=D:\HAM
set PROGDIR="D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur"

cd "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur\headers"
del libham.h
echo #>libham.h

cd "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur"
"D:\Program Files (x86)\Windows Resource Kits\Tools\timeit" -a make

cd "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur\headers"
echo #define HAM_WITH_LIBHAM>libham.h

cd "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur"
make fixheader

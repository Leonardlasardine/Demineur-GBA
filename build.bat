set HAMDIR=D:\HAM
cd "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur"

"D:\Program Files (x86)\Windows Resource Kits\Tools\timeit" -a make
make fixheader
make runvba

::make gdb
::make emu

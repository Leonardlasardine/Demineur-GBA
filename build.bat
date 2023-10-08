set HAMDIR=D:\HAM
cd "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur"

"D:\Program Files (x86)\Windows Resource Kits\Tools\timeit" make
cd "D:\Program Files\vgba"
vgba "D:\Documents and Settings\Administrator\My Documents\Gameboy\HAM\Demineur\Demineur\Demineur.gba"

:: Multithreaded-Debug-DLL (/MDd), Multithreaded-DLL (/MD), Multithreaded-Debug (/MTd), Multithreaded (/MT)
cl /c ../lodepng.cpp /MDd
lib lodepng.obj /OUT:lodepngd.lib
cl /c ../lodepng.cpp /MD
lib lodepng.obj /OUT:lodepng.lib
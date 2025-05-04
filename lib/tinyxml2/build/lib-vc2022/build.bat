:: Multithreaded-Debug-DLL (/MDd), Multithreaded-DLL (/MD), Multithreaded-Debug (/MTd), Multithreaded (/MT)
cl /c ../../tinyxml2.cpp /MDd
lib tinyxml2.obj /OUT:tinyxml2d.lib
cl /c ../../tinyxml2.cpp /MD
lib tinyxml2.obj /OUT:tinyxml2.lib
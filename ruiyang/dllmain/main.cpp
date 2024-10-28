#include "WishSoftware.h"
#include <windows.h>
//#pragma comment(linker, "/subsystem:windows /entry:main")

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WishSoftware wish_software;
	//wish_software.write_productXML();
	//wish_software.read_productXML();
	wish_software.show_window();
	return 0;
}
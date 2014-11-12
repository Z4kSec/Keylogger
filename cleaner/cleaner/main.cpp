#include <Windows.h>
#include "Cleaner.h"

int main()
{
	Cleaner clean;

	clean.reloadExplorer();
	clean.showSources();
	clean.removeOfStartingProcess();
	clean.removeFiles();
	return (0);
}
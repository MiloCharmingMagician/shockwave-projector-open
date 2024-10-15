#include "stdafx.h"
#include "util.h"

// Globals

unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x99, 0x89, 0xcf, 0xab, 0x12};
unsigned char iv[16] = {0x0f, 0x47, 0x0e, 0x7f, 0x75, 0x9c, 0x47, 0x0f, 0x42, 0xc6, 0xd3, 0x9c, 0xbc, 0x8e, 0x23, 0x25};

// Functions

unsigned long getFileSize(const char* filename)
{
	unsigned long size = 0;
	std::fstream file;

	file.open(filename, std::ios::in | std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size = file.tellg();
		file.close();
	}
	else
	{
		OutputDebugString(_T("couldn't load file"));
	}

	return size;
}

char* readFileData(const char* filename, unsigned long offset)
{
	std::fstream file;
	char* data;
	unsigned long size = getFileSize(filename);

	file.open(filename, std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		file.seekg(offset, std::ios::beg);
		data = new char[size];
		file.read(data, size);
		file.close();
		return data;
	}
	else
	{
		OutputDebugString(_T("couldn't load file"));
		return 0;
	}
}

unsigned long romReadBootSize()
{
	std::fstream file;

#ifndef SYS_ROM
	char filename[MAX_PATH];
	DWORD ex = GetModuleFileNameA(NULL, filename, MAX_PATH);
    if (!ex) {
		return 0;
	}
#else
	const char* filename = "rom.bin";
#endif

	unsigned long data = 0;

	file.open(filename, std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		file.seekg(-4, std::ios::end);
		file.read(reinterpret_cast<char*>(&data), sizeof(data));
		file.close();
	    return data;
	}
	else
	{
		OutputDebugString(_T("couldn't load rom boot size"));
		return 0;
	}
}

char* romReadFile(long offset, unsigned long size)
{
	std::fstream file;
	char* data;

#ifndef SYS_ROM
	char filename[MAX_PATH];
	DWORD ex = GetModuleFileNameA(NULL, filename, MAX_PATH);
    if (!ex) {
		return 0;
	}
#else
	const char* filename = "rom.bin";
#endif

	file.open(filename, std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		file.seekg(offset - 4, std::ios::end);
		data = new char[size];
		file.read(data, size);
		file.close();
		return data;
	}
	else
	{
		OutputDebugString(_T("couldn't load rom data"));
		return 0;
	}
}
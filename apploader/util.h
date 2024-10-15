#ifndef UTIL_H_
#define UTIL_H_

#include <fstream>
#include <iostream>
#include <windows.h>

// Defines
#define FLASH_OCX_SIZE 1417216
//#define SYS_ROM
#define AUTH_CODE

// Globals
extern unsigned char key[16];
extern unsigned char iv[16];

// Functions
extern unsigned long getFileSize(const char* filename);
extern char* readFileData(const char* filename, unsigned long offset);
unsigned long romReadBootSize();
extern char* romReadFile(long offset, unsigned long size);

#endif // UTIL_H_

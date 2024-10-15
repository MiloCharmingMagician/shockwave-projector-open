#include <fstream>
#include <iostream>
#include <string>

#include "AES_128_CBC.h"

//#define BUILD_ROM
#define AUTH_CODE

char* readFileData(const char* filename);
unsigned long getFileSize(const char* filename);

int main(int argc, char** argv) {
	std::fstream file;
	char* ldrFilename;
    char* sysFilename;
    char* bootFilename;
    char* output;

	std::cout << "Shockwave Compiler Version 1.0.0" << "\n";
    std::cout << "Copyright (C) Garrett S. 2023-2024. All rights reserved" << "\n\n";

#ifdef _DEBUG
	if (argc < 4) {
		// print usage here and return, since that's what you need.
		std::cout << "makeimage [LDRFILE] [SYSFILE] [BOOTFILE] [OUTPUT]" << std::endl;
	}
	else {
		ldrFilename = argv[1];
		sysFilename = argv[2];
        bootFilename = argv[3];
        output = argv[4];
	}
#else
    ldrFilename = "apploader.exe";
    sysFilename = "flash.ocx";
    bootFilename = "boot.swf";
    output = "player.exe";
#endif

    unsigned long ldrSize = getFileSize(ldrFilename);
	char* ldrFile = readFileData(ldrFilename);

    unsigned long sysSize = getFileSize(sysFilename);
	char* sysFile = readFileData(sysFilename);

    unsigned long bootSize = getFileSize(bootFilename);
	char* bootFile = readFileData(bootFilename);

    // Key
    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x99, 0x89, 0xcf, 0xab, 0x12};

    // IV
    unsigned char iv[16] = {0x0f, 0x47, 0x0e, 0x7f, 0x75, 0x9c, 0x47, 0x0f, 0x42, 0xc6, 0xd3, 0x9c, 0xbc, 0x8e, 0x23, 0x25};

	unsigned char* sysData = (unsigned char*)sysFile;
    unsigned char* bootData = (unsigned char*)bootFile;

#ifdef AUTH_CODE
	// encrypt flash ocx
	AES_CTX ctx1;
	AES_EncryptInit(&ctx1, key, iv);
    for (unsigned int offset = 0; offset < sysSize; offset += 16) {
        AES_Encrypt(&ctx1, sysData + offset, sysData + offset);
    }

	// encrypt boot swf
	AES_CTX ctx2;
	AES_EncryptInit(&ctx2, key, iv);
	for (unsigned int offset = 0; offset < bootSize; offset += 16) {
        AES_Encrypt(&ctx2, bootData + offset, bootData + offset);
    }
#endif

	// write rom image
#ifdef BUILD_ROM
	file.open("rom.bin", std::ios::out | std::ios::binary);
	if (file.is_open()) {
		// Userdata
        file.write((char*)bootData, bootSize);
		file.write((char*)sysData, sysSize);
		// Header
		file.write(reinterpret_cast<const char*>(&bootSize), sizeof(bootSize));
		file.close();
	}
#endif

	// write projector file
	file.open(output, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		// Application
        file.write(ldrFile, ldrSize);
		// Userdata
        file.write((char*)bootData, bootSize);
		file.write((char*)sysData, sysSize);
		// Header
		file.write(reinterpret_cast<const char*>(&bootSize), sizeof(bootSize));
		file.close();
	}

#ifdef _DEBUG
    system("pause");
#endif

    return 0;
}

char* readFileData(const char* filename)
{
	std::fstream file;
    char* data;
    unsigned long size = getFileSize(filename);
    
    file.open(filename, std::ios::in | std::ios::binary);
    if (file.is_open()) {
		data = new char[size];
		file.read(data, size);
		file.close();
		return data;
	}
	else 
	{
	    return 0;
	}
}

unsigned long getFileSize(const char* filename) {
	unsigned long size = 0;
	std::fstream file;

	file.open(filename, std::ios::in | std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size = file.tellg();
	}
	else {
		std::cout << "Error - " << filename << "\n";
	}

	return size;
}

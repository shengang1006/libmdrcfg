#pragma once

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

/*
 *	读取ini类型文件，读取字符串
 */
char* GetIniSectionItem(const char* filename,const char* sect,const char* key,char * out);

/*
 *	读取ini类型文件，读取整形
 */
bool GetIniSectionItemInt(const char* filename,const char* sect,const char* key,int * out);

/*
[section]
{
	
}
*/
char** GetIniItemTable(const char* filename, const char* sect, int&count);


int APHash(char * key);

int ELFHash(char * key);

int BKDRHash(char * key);

int DJBHash(char * key);

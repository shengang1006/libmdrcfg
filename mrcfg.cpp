#include "mrcfg.h"
#define  max_line_length 512

char * trim(char * dst, const char * src, int slen = -1){

	if(!src || !dst){
		return NULL;
	}

	int len = (slen == -1) ? strlen(src):slen;

	if(!len){
		return NULL;
	}

	const char * left = src;
	const char * right = src + len - 1;

	while((*left == ' ' || *left == 0x9) && left++);
	while((*right == ' '|| *right == 0x9 || *right == '\r' || *right == '\n') && right--);

	strncpy(dst, left, right - left + 1);

	dst[right - left + 1] = 0;

	return dst;

}

bool begin(const char * src, char ch){

	if(!src){
		return false;
	}
	while((*src == ' '|| *src == 0x9)&& src++);

	return *src==ch;
}


/*
 *	读取ini类型文件，读取字符串
 */
char* GetIniSectionItem(const char* filename,const char* sect,const char* key,char * out)  
{  

	char temp[max_line_length] = {0};
	char linebuf[max_line_length] = {0};

	bool skip = false;

	char section[64] = {0};
	sprintf(section,"[%s]",sect);  

	FILE *f = fopen(filename,"r"); 
	if(!f)  {  
		return NULL;  
	}  

	while(skip || fgets(linebuf, sizeof(linebuf), f))
	{
		//compare the section

		if(begin(linebuf,'#') ||  //it is comment
			begin(linebuf,';') ||  //it is comment
			!begin(linebuf,'[') ||   //not begin with '['
			!strstr(linebuf, section)){ // not has the section
				skip = false;
				continue;
		}

		//get key
		while(fgets(linebuf, sizeof(linebuf), f)){

			//it is a session, break;
			if (begin(linebuf,'[')){
				skip = true;
				break;
			}

			//it is comment
			if(begin(linebuf,'#') || 
				begin(linebuf,';')) {
					continue;
			}

			//it it a item
			char * pos = strchr(linebuf, '=');
			if (!pos){
				continue;
			}

			//copy the key
			trim(temp, linebuf, pos - linebuf);

			//compare the key,then get value
			if (!strcmp(temp, key)){	
				fclose(f);
				return trim(out, pos+1);
			}
		}
	}

	fclose(f);

	return NULL;  
}  

/*
 *	读取ini类型文件，读取整形
 */
bool GetIniSectionItemInt(const char* filename,const char* sect,const char* key,int * out)
{ 
	char result[64] = {0};
	if(GetIniSectionItem(filename, sect, key, result)){
		*out = atoi(result);
		return true;
	}
	return false;
}


char** GetIniItemTable(const char* filename, const char* sect, int&count, int maxcount /* = 1024*/)
{
	count = 0;
	char section[64] = {0};
	sprintf(section,"[%s]",sect);  

	FILE *f = fopen(filename,"r"); 
	if(!f)  {  
		return NULL;  
	}

	bool find = false;
	char linebuf[max_line_length] = {0};


	//compare the section
	while(fgets(linebuf, sizeof(linebuf), f))
	{
		//get section
		if(begin(linebuf,'[') &&   //not begin with '['
		   strstr(linebuf, section)){ // not has the section
			find = true;
			break;
		}
	}

	if(!find){return NULL;}

	int max = maxcount;
	char ** items = (char**)malloc(max * sizeof(char*));
	memset(items, 0 , max);

	//get {
	while(fgets(linebuf, sizeof(linebuf), f)){
		
		//it is comment
		if(begin(linebuf,'#') || 
		   begin(linebuf,';') ||
		   begin(linebuf,'\n') ||
		   begin(linebuf,'\r')) {
			continue;
		}

		//next section
		if(begin(linebuf, '[')){
			break;
		}

		//too much
		if(count >= max){
			break;
		}
		
		char *item = (char*)malloc(max_line_length);
		trim(item, linebuf);
		items[count++] = item;

	}
	fclose(f);
	return items;
}


int APHash(char * key)
{
    unsigned int hash = 0;
    for (int i= 0; *key; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*key++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*key++) ^ (hash >> 5)));
        }
    }
    return (hash & 0x7FFFFFFF);
}

int ELFHash(char * key)
{
	unsigned long h=0,g;
	while(*key){
		h = (h<<4)+*key++;
		g=h & 0xf0000000L;
		if(g)h ^= (g >> 24);
		h &= ~g;
	}
	return (h & 0x7FFFFFFF);
}

int BKDRHash( char   * key)
{
     unsigned  int  seed  =   131 ;  //  31 131 1313 13131 131313 etc..
     unsigned  int  hash  =   0 ;
     while  ( * key)
     {
         hash  =  hash  *  seed  +  ( * key ++ );
     }
     return  (hash  &   0x7FFFFFFF );
}

int DJBHash(char *key)
{
    unsigned int hash = 5381;
    while (*key)
    {
        hash += (hash << 5) + (*key++);
    }
 
    return (hash & 0x7FFFFFFF);
}
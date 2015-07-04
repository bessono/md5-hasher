/* ========================================================= 
/
=	md5-hasher
=	Author: Bessonv Alexandr Evgenivich
=	Author: e-mail: bessonomap@yandex.ru
=	Author web-site: http://bessonov.in.ua
=
============================================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <openssl/md5.h>

void int_md5(char *hash);
void make_md5(char *str);

static char sresult[16]="-";

int main(int argc, char *argv[]){
	if(argc >= 3){
		if(strstr(argv[1],"-i")){
			int_md5(argv[2]);
		}
	}
	
return 0;
}

void int_md5(char *hash){
	int i=0;
	char str[7] = "-";
	printf("hash = %s \n",hash);
	for(i=0; i < 99999999; i++){
		sprintf(str,"%d",i);
		make_md5(str);
		if(strstr(hash,sresult)){
			printf("\n bingo!!! password=%d \n",i);
			break;
		}
	}	
}

void make_md5(char *str){
	int i;
	char hash[16] ="-";
	char result[16] = "-";
	strcpy(result,"");
	MD5_CTX md5handler;
	char md5digest[MD5_DIGEST_LENGTH];
		
	MD5(str,strlen(str),md5digest);
	
	for(i=0; i<MD5_DIGEST_LENGTH; i++){
		sprintf(hash,"%02x",md5digest[i]);
		if(strlen(hash) > 6){
			hash[0] = hash[6];
			hash[1] = hash[7];
			hash[2] = '\0';
		}
		strcat(result,hash);
	
	}	
	strcpy(sresult,result);
	
}


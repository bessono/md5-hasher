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
void str_md5(char *hash);
void make_md5(char *str);

static char sresult[16]="-";


int main(int argc, char *argv[]){
	if((argc == 2) && (strstr(argv[1],"-h"))) {
		printf("\n ========================= \n");
		printf(" -h View this help \n");
		printf(" -i [hash] try to broot this hash in desimail format from 0 to 99999999.\n");
		printf("    if you suspect that password must be not symbolic \n");
		printf(" -s [hash] try to broot this hash in string formst \n");
		exit(0);	
	}

	if(argc >= 3){
		if(strstr(argv[1],"-i")){
			int_md5(argv[2]);
		}
		if(strstr(argv[1],"-s")){
			str_md5(argv[2]);
		}
	}
	
return 0;
}

void str_md5(char *hash){
	char symbols[38] = "qwertyuiopasdfghjklzxcvbnm1234567890_ ";
	char answer[6] = "-"; 
	
	int c_percent = 0;
	int i=0;
	int j1 = 0;
	int j2 = 0;
	int j3 = 0;
	int j4 = 0;
	int j5 = 0;
			
	for(j1=0; j1 <= strlen(symbols);j1++){
		c_percent = j1*strlen(symbols)/100;
		printf("%d percent is complited \n", c_percent);
		answer[0] = symbols[j1];
		for(j2 = 0 ; j2 <= strlen(symbols); j2++){
			answer[1] = symbols[j2];
			for(j3 = 0; j3 < strlen(symbols); j3++){
				answer[2] = symbols[j3];
				for(j4 = 0; j4 <= strlen(symbols); j4++){
					answer[3] = symbols[j4];
					for(j5 = 0; j5 <= strlen(symbols); j5++){
						answer[4] = symbols[j5];
						answer[5] = '\0';
						for(i=0; i<=strlen(answer); i++){
							if(answer[i] == ' '){answer[i] = '\0';}
						}
						make_md5(answer);
						if(strstr(sresult,hash)){
							printf("\n bingo!!! password=%s \a \n",answer);
							exit(0);
						}
					}
					j5=0;
				}
				j4 = 0;	
			}
			j3=0;		
		}	
		j2=0;			
	}		
}

void int_md5(char *hash){
	int i=0;
	int c_percent = 0;
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


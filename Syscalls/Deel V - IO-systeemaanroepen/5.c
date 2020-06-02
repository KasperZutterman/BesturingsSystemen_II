#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

void standaard() {
	char buffer[BUFSIZ];
	int aantal;
	while((aantal = read(0, buffer, BUFSIZ))!=0) {
		write(1, buffer, aantal);
	}
}	


int main(int argc, char **argv) {
	if(argc==1) {
		standaard();
		return 0;
	}
	char buffer[BUFSIZ];
	int i = 1;
	for(i; i < argc; i++) {
		if(!strcmp(argv[i], "-")) {
			//standaard cat
			standaard();
		}
		else {
			//hier eerst nog checken of bestand wel uitschrijfbaar is
			//open file
			int fd = open(argv[i], O_RDONLY);
			struct stat st;
			fstat(fd, &st);
			if((st.st_mode & S_IFMT) != S_IFREG) {		
				write(0, argv[i], strlen(argv[i]));	
				write(0," is not a file!\n", strlen(" is not a file!\n"));
				continue;
			}
			if(fd < 0) {
				perror(argv[i]);
				continue;
			}
			int n;
			while((n=read(fd,buffer, BUFSIZ)) != 0) {
				write(0, buffer, n);
			}
			close(fd);
		}
	}	
	return 0;
}	

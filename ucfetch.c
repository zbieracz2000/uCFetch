//
// uCFetch, a light C-based fetch program for Linux
// Designed specifically for uCLinux
// by zbieracz2000
//
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/utsname.h>
#include<libgen.h>
#include<sys/sysinfo.h>

int main()
{
	char *user = getenv("USER");
	if(user==NULL) return EXIT_FAILURE;

	char hostname[1024];
	gethostname(hostname, 1024);

	FILE *p;
	char ch;
	p = popen("lsb_release -sd", "r");
	if(p == NULL) return EXIT_FAILURE;

	FILE* model;
	char modelname[70];
	model = fopen("/sys/devices/virtual/dmi/id/product_name", "r");
	
	const long minute = 60;
 	const long hour = minute * 60;
 	const long day = hour * 24;
	struct sysinfo si;
	sysinfo(&si);

	struct utsname uName;
	uname(&uName);
/*
	FILE* pak;
	char pk[7];
	pak = popen("xbps-query -l | wc -l", "r");
*/
	char *str = getenv("SHELL");
	char *shell;
	shell = basename(str);

	char *de = getenv("DESKTOP_SESSION");
	if(de==NULL) return EXIT_FAILURE;

	const double mb = 1024 * 1024;
	double used_mb = (si.totalram / mb) - (si.freeram / mb) - (si.bufferram / mb) - (si.sharedram / mb) - (si.sharedram / mb);

	// Prints user@host
	printf("\033[1;33m       .---.	 \033[0;32m%s@%s \n", user, hostname);

	// Prints name of the distro
	int fw = 0;
	printf("\033[1;33m      /     \\	 \033[0;34mOS: \t\t");
	while( (ch=fgetc(p)) != EOF)
	{
		if(isalpha(ch))
		{
			fw = 1;
			putchar(ch);
		}
		else
		{
			if(fw)
			{
				putchar(' ');
				fw = 0;
			}
		}
	}
	pclose(p);
	printf("\n");

	printf("\033[1;33m      \\.@-@./	 \033[0;35mHOST: \t\t");
	while(fgets(modelname, sizeof(modelname), model))
	{
		printf("%s", modelname);
	}

	// Prints linux & version
	printf("\033[1;33m      /`\\_/`\\	 \033[0;36mKERNEL: \t%s %s\n", uName.sysname, uName.release);

	// Prints uptime
	printf("\033[1;33m     //  _  \\\\	 \033[0;35mUPTIME: \t%ld hours, %02ld minutes\n", (si.uptime % day) / 3600, (si.uptime % hour) / minute);

	// Prints shell
	printf("\033[1;33m    | \\     )|	 \033[0;34mSHELL: \t%s\n", shell);

	// Prints the desktop environment
	printf("\033[1;33m   /`\\_`>  <_/ \\ \033[0;33mDE:\t\t%s\n", de);

	// Prints free RAM (include cache ram, as it cannot be removed)
	//printf ("	RAM: \t\t%5.1f MB\n", used_mb);
	return 0;
}

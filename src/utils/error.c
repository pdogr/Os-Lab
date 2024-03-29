#include "unp.h"
#include <stdarg.h>
#include <syslog.h>

static void err_doit(int ,int ,const char*,va_list);


void err_quit(const char* fmt,...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(0,LOG_ERR,fmt,ap);
	va_end(ap);
	exit(0);
}
void err_sys(const char *fmt,...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,LOG_ERR,fmt,ap);
	va_end(ap);
	exit(1);
}

static void err_doit(int flg,int level,const char* fmt,va_list ap){

   //print the error and corresponding message
	int errno_save,n;
	char buf[MAXLINE+1];

   //save error number
	errno_save=errno;
	#ifdef HAVE_VSNPRINTF
		vsnprintf(buf,MAXLINE,fmt,ap);
	#else 
		vsprintf(buf,fmt,ap);
	#endif

	n=strlen(buf);

	if(flg)
		snprintf(buf+n,MAXLINE-n,": %s",strerror(errno_save));
	strcat(buf,"\n");
		fflush(stdout);
		fputs(buf,stderr);
		fflush(stderr);
	return ;
}

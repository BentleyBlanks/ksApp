#include <ks/utility/ksLog.h>

#include <ofMain.h>
#include <stddef.h>
#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

ofFileLoggerChannel fileLog;

void ksLog(const char * _Format,...)
{
	va_list args;
	va_start(args,_Format);

	FILE* out = stdout;
	vfprintf(out, _Format, args);
	fprintf(out, "\n");

	fileLog.log(OF_LOG_NOTICE,"",_Format,args);

	va_end( args );
}

void ksLog(const string & message)
{
	//ofLog(OF_LOG_NOTICE,message);
	ostream& out = cout;
	out << message << endl;
	fileLog.log(OF_LOG_NOTICE,"",message);
}

void ksErrorLog(const string & path/* ="log/logfile.log" */, bool append/* =true */)
{
	fileLog.setFile(path,append);
}
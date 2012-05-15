#include <string>
#include <time.h>

using namespace std;
//string SysStrToStr(System::String^ s ){
//    using System::IntPtr;
//    using System::Runtime::InteropServices::Marshal;
//
//	string os;
//    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer( );
//    os = chars;
//    Marshal::FreeHGlobal(IntPtr((void*)chars));
//	return os;
//}

//string TimeToString(time_t date/*, string &format = "%Y-%m-%d"*/){
//	time(&date);
//	struct tm  *timeStruct = localtime(&date);
//	char buffer [80];
//	strftime(buffer,80,"%Y-%m-%d",timeStruct);
//	return (string)buffer;
//}
#include <string>

using namespace std;

string SysStrToStr(System::String^ s ){
    using System::IntPtr;
    using System::Runtime::InteropServices::Marshal;

	string os;
    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer( );
    os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}
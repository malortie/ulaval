#ifndef TP2_COMPILER_H__
#define TP2_COMPILER_H__

#define MSC_CRT_RUNTIME_HEAP_DEBUG_DEFINED	( _DEBUG ) && defined ( _MSC_VER ) && defined ( _WIN32 )
#define USE_MSC_CRT_RUNTIME_HEAP_DEBUG		( _DEBUG ) && ( _MSC_VER ) && ( _WIN32 )
#define MSC_CRT_RUNTIME_HEAP_DEBUG_ENABLED MSC_CRT_RUNTIME_HEAP_DEBUG_DEFINED && USE_MSC_CRT_RUNTIME_HEAP_DEBUG

#if defined MSC_CRT_RUNTIME_HEAP_DEBUG_ENABLED
#include <crtdbg.h>
#endif // MSC_CRT_RUNTIME_HEAP_DEBUG_ENABLED

#define ENABLE_MSC_CRT_RUNTIME_HEAP_INSPECTION		tp2::__enable_inspection
#define TERMINATE_MSC_CRT_RUNTIME_HEAP_INSPECTION	tp2::__check_memory_leaks


namespace tp2 {

static void __enable_inspection()
{
#if defined MSC_CRT_RUNTIME_HEAP_DEBUG_ENABLED
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif
}

static void __check_memory_leaks()
{
#if defined MSC_CRT_RUNTIME_HEAP_DEBUG_ENABLED
	_ASSERT(_CrtCheckMemory());
#endif
}

}

#endif // TP2_COMPILER_H__
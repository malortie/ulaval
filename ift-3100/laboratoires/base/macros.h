#ifndef MACROS_H__
#define MACROS_H__

#ifndef _STRINGIZEX
#define _STRINGIZEX(x) #x
#ifndef _STRINGIZE
#define _STRINGIZE(x) _STRINGIZEX(x)
#endif // !defined ( _STRINGIZE )
#endif // !defined ( _STRINGIZEX )

#define STRING_CONCAT( _str1, _str2 )				_str1 ## _str2
#define STRING_CONCAT_STRINGIZE( _str1, _str2 )		_STRINGIZE( _str1 ) ## _STRINGIZE( _str2 )

#endif // MACROS_H__
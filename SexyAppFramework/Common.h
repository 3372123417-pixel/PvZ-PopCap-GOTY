#ifndef __SEXYAPPFRAMEWORK_COMMON_H__
#define __SEXYAPPFRAMEWORK_COMMON_H__

#pragma warning(disable:4786)
#pragma warning(disable:4503)

#undef _WIN32_WINNT
#undef WIN32_LEAN_AND_MEAN

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500
#undef _UNICODE
#undef UNICODE

#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <cstdlib>

#include <windows.h>
#include <shellapi.h> 
#include <mmsystem.h>
#include "ModVal.h"

#ifdef _USE_WIDE_STRING

typedef std::wstring		SexyString;
#define _S(x)				L ##x


#define sexystrncmp			wcsncmp
#define sexystrcmp			wcscmp
#define sexystricmp			wcsicmp
#define sexysscanf			swscanf
#define sexyatoi			_wtoi
#define sexystrcpy			wcscpy

#define SexyStringToStringFast(x)	WStringToString(x)
#define SexyStringToWStringFast(x)	(x)
#define StringToSexyStringFast(x)	StringToWString(x)
#define WStringToSexyStringFast(x)	(x)

#ifndef SEXYFRAMEWORK_NO_REDEFINE_WIN_API
// Redefine the functions and structs we need to be wide-string
#undef CreateWindowEx
#undef RegisterClass
#undef MessageBox
#undef ShellExecute
#undef GetTextExtentPoint32
#undef RegisterWindowMessage
#undef CreateMutex
#undef DrawTextEx
#undef TextOut

#define CreateWindowEx				CreateWindowExW
#define RegisterClass				RegisterClassW
#define WNDCLASS					WNDCLASSW
#define MessageBox					MessageBoxW
#define ShellExecute				ShellExecuteW
#define GetTextExtentPoint32		GetTextExtentPoint32W
#define RegisterWindowMessage		RegisterWindowMessageW
#define CreateMutex					CreateMutexW
#define DrawTextEx					DrawTextExW
#define TextOut						TextOutW
#endif

#else

typedef std::string			SexyString;
#define _S(x)				x


#define sexystrncmp			strncmp
#define sexystrcmp			strcmp
#define sexystricmp			stricmp
#define sexysscanf			sscanf
#define sexyatoi			atoi
#define sexystrcpy			strcpy

#define SexyStringToStringFast(x)	(x)
#define SexyStringToWStringFast(x)	StringToWString(x)
#define StringToSexyStringFast(x)	(x)
#define WStringToSexyStringFast(x)	WStringToString(x)

#endif

#define LONG_BIGE_TO_NATIVE(l) (((l >> 24) & 0xFF) | ((l >> 8) & 0xFF00) | ((l << 8) & 0xFF0000) | ((l << 24) & 0xFF000000))
#define WORD_BIGE_TO_NATIVE(w) (((w >> 8) & 0xFF) | ((w << 8) & 0xFF00))
#define LONG_LITTLEE_TO_NATIVE(l) (l)
#define WORD_LITTLEE_TO_NATIVE(w) (w)

#define LENGTH(anyarray) (sizeof(anyarray) / sizeof(anyarray[0]))

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef __int64 int64;

typedef std::map<std::string, std::string>		DefinesMap;
typedef std::map<std::wstring, std::wstring>	WStringWStringMap;
typedef SexyString::value_type					SexyChar;
#define HAS_SEXYCHAR

namespace Sexy
{

const ulong SEXY_RAND_MAX = 0x7FFFFFFF;

extern bool			gDebug;
extern HINSTANCE	gHInstance;

int					Rand();
int					Rand(int range);
float				Rand(float range);
void				SRand(ulong theSeed);
extern std::string	vformat(const char* fmt, va_list argPtr);
extern std::wstring	vformat(const wchar_t* fmt, va_list argPtr);
extern std::string	StrFormat(const char* fmt ...);
extern std::wstring	StrFormat(const wchar_t* fmt ...);
bool				CheckFor98Mill();
bool				CheckForVista();
std::string			GetAppDataFolder();
void				SetAppDataFolder(const std::string& thePath);
std::string			URLEncode(const std::string& theString);
std::string			StringToUpper(const std::string& theString);
std::wstring		StringToUpper(const std::wstring& theString);
std::string			StringToLower(const std::string& theString);
std::wstring		StringToLower(const std::wstring& theString);
std::wstring		StringToWString(const std::string &theString);
std::string			WStringToString(const std::wstring &theString);
SexyString			StringToSexyString(const std::string& theString);
SexyString			WStringToSexyString(const std::wstring& theString);
std::string			SexyStringToString(const SexyString& theString);
std::wstring		SexyStringToWString(const SexyString& theString);
std::string			Upper(const std::string& theData);
std::wstring		Upper(const std::wstring& theData);
std::string			Lower(const std::string& theData);
std::wstring		Lower(const std::wstring& theData);
std::string			Trim(const std::string& theString);
std::wstring		Trim(const std::wstring& theString);
bool				StringToInt(const std::string theString, int* theIntVal);
bool				StringToDouble(const std::string theString, double* theDoubleVal);
bool				StringToInt(const std::wstring theString, int* theIntVal);
bool				StringToDouble(const std::wstring theString, double* theDoubleVal);
int					StrFindNoCase(const char *theStr, const char *theFind);
bool				StrPrefixNoCase(const char *theStr, const char *thePrefix, int maxLength = 10000000);
SexyString			CommaSeperate(int theValue);
std::string			Evaluate(const std::string& theString, const DefinesMap& theDefinesMap);
std::string			XMLDecodeString(const std::string& theString);
std::string			XMLEncodeString(const std::string& theString);
std::wstring		XMLDecodeString(const std::wstring& theString);
std::wstring		XMLEncodeString(const std::wstring& theString);

// UTF-8 / Encoding detection and conversion helpers
bool				IsValidUTF8(const char* theData, int theLen);
std::string			Win1252ToUTF8(const char* theData, int theLen);
std::string			AutoDetectEncodingToUTF8(const char* theData, int theLen);

bool				Deltree(const std::string& thePath);
bool				FileExists(const std::string& theFileName);
void				MkDir(const std::string& theDir);
std::string			GetFileName(const std::string& thePath, bool noExtension = false);
std::string			GetFileDir(const std::string& thePath, bool withSlash = false);
std::string			RemoveTrailingSlash(const std::string& theDirectory);
std::string			AddTrailingSlash(const std::string& theDirectory, bool backSlash = false);
time_t				GetFileDate(const std::string& theFileName);
std::string			GetCurDir();
std::string			GetFullPath(const std::string& theRelPath);
std::string			GetPathFrom(const std::string& theRelPath, const std::string& theDir);
bool				AllowAllAccess(const std::string& theFileName);


inline void			inlineUpper(std::string &theData)
{
    //std::transform(theData.begin(), theData.end(), theData.begin(), toupper);

	int aStrLen = (int) theData.length();
	for (int i = 0; i < aStrLen; i++)
	{
		theData[i] = toupper(theData[i]);
	}
}

inline void			inlineUpper(std::wstring &theData)
{
    //std::transform(theData.begin(), theData.end(), theData.begin(), toupper);

	int aStrLen = (int) theData.length();
	for (int i = 0; i < aStrLen; i++)
	{
		theData[i] = towupper(theData[i]);
	}
}

inline void			inlineLower(std::string &theData)
{
    std::transform(theData.begin(), theData.end(), theData.begin(), tolower);
}

inline void			inlineLower(std::wstring &theData)
{
    std::transform(theData.begin(), theData.end(), theData.begin(), tolower);
}

inline void			inlineLTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
    theData.erase(0, theData.find_first_not_of(theChars));
}

inline void			inlineLTrim(std::wstring &theData, const std::wstring& theChars = L" \t\r\n")
{
    theData.erase(0, theData.find_first_not_of(theChars));
}


inline void			inlineRTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
    theData.resize(theData.find_last_not_of(theChars) + 1);
}

inline void			inlineTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
	inlineRTrim(theData, theChars);
	inlineLTrim(theData, theChars);
}

struct StringLessNoCase { bool operator()(const std::string &s1, const std::string &s2) const { return _stricmp(s1.c_str(),s2.c_str())<0; } };

inline bool UTF8DecodeNext(const std::string& theString, size_t& theOffset, unsigned int& theOutChar)
{
	if (theOffset >= theString.size())
		return false;

	unsigned char aFirst = (unsigned char)theString[theOffset];
	int aSeqLen;
	unsigned int aCodePoint;

	if (aFirst < 0x80)
	{
		aSeqLen = 1;
		aCodePoint = aFirst;
	}
	else if ((aFirst & 0xE0) == 0xC0)
	{
		if (theOffset + 1 >= theString.size()) return false;
		unsigned char aSecond = (unsigned char)theString[theOffset + 1];
		if ((aSecond & 0xC0) != 0x80) return false;
		aCodePoint = ((aFirst & 0x1F) << 6) | (aSecond & 0x3F);
		if (aCodePoint < 0x80) return false;
		aSeqLen = 2;
	}
	else if ((aFirst & 0xF0) == 0xE0)
	{
		if (theOffset + 2 >= theString.size()) return false;
		unsigned char aSecond = (unsigned char)theString[theOffset + 1];
		unsigned char aThird  = (unsigned char)theString[theOffset + 2];
		if ((aSecond & 0xC0) != 0x80 || (aThird & 0xC0) != 0x80) return false;
		aCodePoint = ((aFirst & 0x0F) << 12) | ((aSecond & 0x3F) << 6) | (aThird & 0x3F);
		if (aCodePoint < 0x800) return false;
		aSeqLen = 3;
	}
	else if ((aFirst & 0xF8) == 0xF0)
	{
		if (theOffset + 3 >= theString.size()) return false;
		unsigned char aSecond = (unsigned char)theString[theOffset + 1];
		unsigned char aThird  = (unsigned char)theString[theOffset + 2];
		unsigned char aFourth = (unsigned char)theString[theOffset + 3];
		if ((aSecond & 0xC0) != 0x80 || (aThird & 0xC0) != 0x80 || (aFourth & 0xC0) != 0x80) return false;
		aCodePoint = ((aFirst & 0x07) << 18) | ((aSecond & 0x3F) << 12) | ((aThird & 0x3F) << 6) | (aFourth & 0x3F);
		if (aCodePoint < 0x10000 || aCodePoint > 0x10FFFF) return false;
		aSeqLen = 4;
	}
	else
	{
		return false;
	}

	theOutChar = aCodePoint;
	theOffset += aSeqLen;
	return true;
}

// Opening punctuation that must not appear at end of a line
inline bool IsOpeningPunctuation(wchar_t theChar)
{
	switch (theChar)
	{
	case L'\u3008': case L'\u300A': case L'\u300C': case L'\u300E':
	case L'\u3010': case L'\u3014': case L'\u3016': case L'\u3018':
	case L'\u301A':
	case L'\uFF08': case L'\uFF3B': case L'\uFF5B':
	case L'\u2018': case L'\u201A': case L'\u201B': case L'\u201C':
		return true;
	default:
		return false;
	}
}

// Closing punctuation that must not appear at start of a line
inline bool IsClosingPunctuation(wchar_t theChar)
{
	switch (theChar)
	{
	case L'\u3009': case L'\u300B': case L'\u300D': case L'\u300F':
	case L'\u3011': case L'\u3015': case L'\u3017': case L'\u3019':
	case L'\u301B':
	case L'\uFF09': case L'\uFF3D': case L'\uFF5D':
	case L'\u2019': case L'\u201D':
	case L'\u3001': case L'\u3002':
	case L'\uFF0C': case L'\uFF0E':
	case L'\uFF01': case L'\uFF1F':
	case L'\uFF1A': case L'\uFF1B':
		return true;
	default:
		return false;
	}
}

// Characters that allow auto line-break (CJK, etc.)
inline bool IsAutoBreakChar(wchar_t theChar)
{
	if (theChar < 0x80)
		return false;
	return (theChar >= 0x2018 && theChar <= 0x201D) ||
		(theChar >= 0x2600 && theChar <= 0x27BF) ||
		(theChar >= 0x3000 && theChar <= 0x303F) ||
		(theChar >= 0x3040 && theChar <= 0x309F) ||
		(theChar >= 0x30A0 && theChar <= 0x30FF) ||
		(theChar >= 0x3400 && theChar <= 0x4DBF) ||
		(theChar >= 0x4E00 && theChar <= 0x9FFF) ||
		(theChar >= 0xAC00 && theChar <= 0xD7AF) ||
		(theChar >= 0xF900 && theChar <= 0xFAFF) ||
		(theChar >= 0xFE30 && theChar <= 0xFE4F) ||
		(theChar >= 0xFF01 && theChar <= 0xFF60) ||
		(theChar >= 0x20000 && theChar <= 0x2FA1F);
}

}

#endif //__SEXYAPPFRAMEWORK_COMMON_H__
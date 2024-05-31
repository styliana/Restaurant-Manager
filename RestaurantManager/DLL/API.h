#pragma once 
#ifdef _BUILD 
#define EXPORT_API __declspec(dllexport) 
#else 
#define EXPORT_API __declspec(dllimport) 
#endif // _BUILD 
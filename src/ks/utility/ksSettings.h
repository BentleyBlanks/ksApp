#ifndef KS_SETTINGS_H
#define KS_SETTINGS_H

#include <iostream>

#define KS_MAX_CONTENT_LENGTH_1 128
#define KS_MAX_CONTENT_LENGTH_2 256
#define KS_MAX_CONTENT_LENGTH_3 512
#define KS_MAX_CONTENT_LENGTH_4 1024

#define KS_MAX_NAME_LENGTH 32

#define KS_DEFAULT_NAME "HHHHHHHHHHHHHHHHHHH"

// 万花筒具体类型
//enum ksType
//{
//    // --!上界
//    KS_TYPE_DEFAULT = 0,
//    
//    // 用户自定义类型
//    KS_TYPE_SUPERPOSITION,
//    
//    // --!下界
//    // ksType中类型个数
//    KS_TYPE_MAXCOUNTS
//};

// Floekr2d版本信息
// --!来自box2d http://en.wikipedia.org/wiki/Software_versioning
struct ksVersion
{
	int major;		///< significant changes
	int minor;		///< incremental changes
	int revision;		///< bug fixes

	void print()
	{
		std::cout << "TattyUI版本:" << major << "." << minor << "." << revision << std::endl;
	}
};

// 当前版本号
extern ksVersion kaleisoscopeVersion;

#endif

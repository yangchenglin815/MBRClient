#ifndef ENUMDATA_H
#define ENUMDATA_H

//数据库类型
enum DatabaseType {
	e_splite,
	e_sqlServer,
	e_mysql,
	e_firebird
};

enum 
{
	Register_Registered = 0,            // 已注册
	Register_NotRegistered = 1,            // 未注册
	Register_TimeOut = 2,            // 过期
	Register_Forbidden = 3,             // 注册码已禁用
	Register_WillTimeOut = 4,           // 即将过期
};

enum 
{
	BioType_None = 0,
	BioType_Face = 11,
	BioType_FVein = 12,
	//    BiometricType_ParmVein = 13,
	//    BiometricType_Eye = 14,
	BioType_FPrint = 15,
	//    BiometricType_Voice = 16,
};

enum 
{
	//    BioModel_Default = 0,
	ModelType_VIS = 111,         // 可见光
	ModelType_NIR = 112,         // 近红外
	ModelType_FVein = 121,        // 指静脉反射
	ModelType_FPrint = 151,        // 指纹
};

enum 
{
	CacheCode_Dict = 1001,      // 字典缓存
	CacheCode_Area = 1002,     // 行政区域缓存
	CacheCode_Param = 1003,      // 参数缓存
	CacheCode_Org = 1004,      // 统筹区缓存
	CacheCode_Unit = 1005,      // 单位缓存
};

#endif
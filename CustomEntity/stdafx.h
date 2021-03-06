#pragma once
#define CUSTOMENTITY_MODULE

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN  // 从 Windows 头中排除极少使用的资料
#endif

#include <windows.h>
#include <map>

// TODO: 在此处引用程序需要的其他头文件
#using <mscorlib.dll>
#using <System.dll>

// 引用.net版cad依赖库,直接添加引用会找不到（bug？）,
// 需要手动拷贝acdbmgd.dll,acmgd.dll,accoremgd.dll至项目目录
// 或者在其他#using添加包含文件的目录
#using <acdbmgd.dll>
#using <acmgd.dll>
#using <accoremgd.dll>
#using <AcCui.dll>

#include <vcclr.h>
#include <dbxHeaders.h>
#include <dbents.h>
#include <aced.h>
#include <dbtrans.h>
#include <tchar.h>


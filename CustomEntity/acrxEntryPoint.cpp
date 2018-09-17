#pragma once
#include "stdafx.h" // 这句要放在第一句
#include "FaneTriangle.h"
#include "CustomEntity.h"

static AcMgObjectFactoryBase** g_PEs = NULL;

extern "C" {
	AcRx::AppRetCode __declspec(dllexport) acrxEntryPoint(AcRx::AppMsgCode code, void *pkt);
}

AcRx::AppRetCode __declspec(dllexport) acrxEntryPoint(AcRx::AppMsgCode code, void *pkt) {

	switch (code)
	{
	case AcRx::kNullMsg:
		break;
	case AcRx::kInitAppMsg: { // case 多语句最好加大括号
		acrxDynamicLinker->unlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		
		FaneTriangle::rxInit();

		if (!acrxServiceIsRegistered(_T("FaneTriangle")))
			acrxRegisterService(_T("FaneTriangle"));

		acrxBuildClassHierarchy();

		// 不知道有什么卵用，网上查不到资料,这句要放在rxInit和acrxBuildClassHierarchy之后
		static AcMgObjectFactoryBase* PEs[] =
		{
			new AcMgObjectFactory<CustomEntity::FaneTriangleWrapper,FaneTriangle>(),
			NULL
		};

		g_PEs = PEs;
		
	}break;

	case AcRx::kUnloadAppMsg: {
		AcRxObject * obj = acrxServiceDictionary->remove(_T("FaneTriangle"));
		if (obj != NULL)
			delete obj;

		deleteAcRxClass(FaneTriangle::desc());
		acrxBuildClassHierarchy();
		
	}break;

	case AcRx::kLoadDwgMsg:
		break;
	case AcRx::kUnloadDwgMsg:
		break;
	case AcRx::kInvkSubrMsg:
		break;
	case AcRx::kCfgMsg:
		break;
	case AcRx::kEndMsg:
		break;
	case AcRx::kQuitMsg:
		break;
	case AcRx::kSaveMsg:
		break;
	case AcRx::kDependencyMsg:
		break;
	case AcRx::kNoDependencyMsg:
		break;
	case AcRx::kOleUnloadAppMsg:
		break;
	case AcRx::kPreQuitMsg: {
		int i = 0;
		while (g_PEs[i] != NULL)
			delete g_PEs[i++];
		
	}break;

	case AcRx::kInitDialogMsg:
		break;
	case AcRx::kEndDialogMsg:
		break;
	case AcRx::kSuspendMsg:
		break;
	case AcRx::kInitTabGroupMsg:
		break;
	case AcRx::kEndTabGroupMsg:
		break;
	default:
		break;
	}

	return AcRx::kRetOK;
}
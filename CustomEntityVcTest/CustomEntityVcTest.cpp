// CustomEntityVcTest.cpp: 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "..\CustomEntity\FaneTriangle.h"

class CustomEntityVcTest : public AcRxArxApp {
public:
	CustomEntityVcTest() : AcRxArxApp(){}

	virtual AcRx::AppRetCode On_kInitAppMsg(void *pkt) {

		AcRx::AppRetCode retcode = AcRxArxApp::On_kInitAppMsg(pkt);
		return retcode;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg(void *pkt) {
		AcRx::AppRetCode retcode = AcRxArxApp::On_kUnloadAppMsg(pkt);
		return retcode;
	}

	virtual void RegisterServerComponents(){}

	static void CustomEntityAddTriangle() {
		FaneTriangle *faneTriangle = new FaneTriangle(AcGePoint3d(0,0,0), AcGePoint3d(100, 0, 0), AcGePoint3d(50, 100, 88));
		PostToModelSpace(faneTriangle);
	}

	static AcDbObjectId PostToModelSpace(AcDbEntity *entity, AcDbDatabase *db = acdbHostApplicationServices()->workingDatabase()) {

		if (entity == NULL)
		{
			return AcDbObjectId::kNull;
		}

		if (!db)
		{
			db = acdbHostApplicationServices()->workingDatabase();
		}

		AcTransaction * trans = acdbTransactionManager->startTransaction();
		
		AcDbObject *btObj;
		AcDbBlockTable *blockTable;
		AcDbBlockTableRecord *blockTableRecord;

		Acad::ErrorStatus es = trans->getObject(btObj, db->blockTableId(), AcDb::kForRead);
		if (es != Acad::eOk)
		{
			return AcDbObjectId::kNull;
		}
		blockTable = AcDbBlockTable::cast(btObj);
		es = blockTable->getAt(ACDB_MODEL_SPACE, blockTableRecord,AcDb::kForWrite);
		if (es != Acad::eOk)
		{
			blockTable->close();
			return AcDbObjectId::kNull;
		}

		AcDbObjectId entId;
		es = blockTableRecord->appendAcDbEntity(entId, entity);
		if (es != Acad::eOk)
		{
			blockTable->close();
			delete entity;
			entity = NULL;

			return AcDbObjectId::kNull;
		}

		blockTable->close();
		blockTableRecord->close();
		entity->close();

		return entId;
	}
	
};

IMPLEMENT_ARX_ENTRYPOINT(CustomEntityVcTest)
ACED_ARXCOMMAND_ENTRY_AUTO(CustomEntityVcTest,CustomEntity,AddTriangle,AddTriangle,ACRX_CMD_MODAL,NULL)

#pragma once
#include "dbmain.h"

class __declspec(dllexport) FaneTriangle :public AcDbEntity
{
protected:
	static Adesk::UInt32 kVersionNumber;

public:
	FaneTriangle();
	~FaneTriangle();
	FaneTriangle(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &pt3);

	ACRX_DECLARE_MEMBERS(FaneTriangle);

	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler *pFiler);

	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw *mode);

private:
	AcGePoint3d mVerts[3];
};


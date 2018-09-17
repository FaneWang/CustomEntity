#pragma once
#include "stdafx.h"
#include "FaneTriangle.h"



//版本号，必须是类的第一个数据成员
Adesk::UInt32 FaneTriangle::kVersionNumber = 1;

ACRX_DXF_DEFINE_MEMBERS(
	FaneTriangle,
	AcDbEntity,
	AcDb::kDHL_CURRENT,
	AcDb::kMReleaseCurrent,
	AcDbProxyEntity::kNoOperation,
	FANETRIANGLE,
	"FANETRIANGLEENTITYDBAPP"
	"|Desc: a custom entity"
	"|Author: fane"
)

FaneTriangle::FaneTriangle() : AcDbEntity()
{
}


FaneTriangle::~FaneTriangle()
{
}

FaneTriangle::FaneTriangle(const AcGePoint3d &pt1, const AcGePoint3d &pt2, const AcGePoint3d &pt3 )
{
	mVerts[0] = pt1;
	mVerts[1] = pt2;
	mVerts[2] = pt3;
}

Acad::ErrorStatus FaneTriangle::dwgOutFields(AcDbDwgFiler *pFiler) const {
	assertReadEnabled();
	Acad::ErrorStatus es = AcDbEntity::dwgOutFields(pFiler);
	if (es != Acad::eOk)
	{
		return es;
	}

	if ((es = pFiler->writeUInt32(kVersionNumber)) != Acad::eOk)
	{
		return es;
	}

	for (size_t i = 0; i < 3; i++)
	{
		pFiler->writeItem(mVerts[i]);
	}

	return pFiler->filerStatus();
}

Acad::ErrorStatus FaneTriangle::dwgInFields(AcDbDwgFiler *pFiler) {
	assertWriteEnabled();

	Acad::ErrorStatus es = AcDbEntity::dwgInFields(pFiler);
	if (es != Acad::eOk)
	{
		return es;
	}

	Adesk::UInt32 version = 0;
	if ((es = pFiler->readUInt32(&version)) != Acad::eOk) // 传引用改变实参，传值赋值给形参
	{
		return es;
	}

	if (version > FaneTriangle::kVersionNumber)
	{
		return	Acad::eMakeMeProxy;
	}

	for (size_t i = 0; i < 3; i++)
	{
		pFiler->readItem(&mVerts[i]);
	}

	return pFiler->filerStatus();
}

Adesk::Boolean FaneTriangle::subWorldDraw(AcGiWorldDraw *mode) {
	assertReadEnabled();

	for (size_t i = 0; i < 3; i++)
	{
		size_t nextIndex = i + 1;

		if (i == 2)
		{
			nextIndex = 0;
		}

		AcGePoint3d points[2];
		points[0] = mVerts[i];
		points[1] = mVerts[nextIndex];
		mode->geometry().polyline(2, points);
	}

	return AcDbEntity::subWorldDraw(mode);
}





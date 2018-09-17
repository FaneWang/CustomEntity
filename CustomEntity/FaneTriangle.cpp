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

Acad::ErrorStatus FaneTriangle::subGetOsnapPoints(
	AcDb::OsnapMode osnapMode,
	int gsSelectionMark,
	const AcGePoint3d& pickPoint,
	const AcGePoint3d& lastPoint,
	const AcGeMatrix3d& viewXform,
	AcGePoint3dArray& snapPoints,
	AcDbIntArray& geomIds
) const {
	assertReadEnabled();

	AcDbPolyline *polyline = GetPolyline();
	Acad::ErrorStatus es = polyline->getOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds);
	delete polyline;
	return es;
}

Acad::ErrorStatus FaneTriangle::subGetOsnapPoints(
	AcDb::OsnapMode osnapMode,
	int gsSelectionMark,
	const AcGePoint3d& pickPoint,
	const AcGePoint3d& lastPoint,
	const AcGeMatrix3d& viewXform,
	AcGePoint3dArray& snapPoints,
	AcDbIntArray& geomIds,
	const AcGeMatrix3d& insertionMat
) const {
	assertReadEnabled();
	return AcDbEntity::getOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds, insertionMat);
}

Acad::ErrorStatus FaneTriangle::subGetGripPoints(
	AcGePoint3dArray& gripPoints,
	AcDbIntArray&  osnapModes,
	AcDbIntArray&  geomIds
) const {
	assertReadEnabled();
	for (size_t i = 0; i < 3; i++)
	{
		gripPoints.append(mVerts[i]);
	}

	return Acad::eOk;
}

Acad::ErrorStatus FaneTriangle::subMoveGripPointsAt(
	const AcDbIntArray& indices,
	const AcGeVector3d& offset
) {
	mVerts[indices[0]] += offset;
	return Acad::eOk;
}

Acad::ErrorStatus FaneTriangle::subTransformBy(
	const AcGeMatrix3d& xform
) {
	for (size_t i = 0; i < 3; i++)
	{
		mVerts[i].transformBy(xform);
	}
	return Acad::eOk;
}

Acad::ErrorStatus FaneTriangle::subGetGeomExtents(
	AcDbExtents& extents
) const {
	for (size_t i = 0; i < 3; i++)
	{
		extents.addPoint(mVerts[i]);
	}
	return	Acad::eOk;
}

Acad::ErrorStatus FaneTriangle::subExplode(
	AcDbVoidPtrArray& entitySet
) const {
	for (size_t i = 0; i < 3; i++)
	{
		int nextIndex = i + 1;
		if (i == 2)
		{
			nextIndex = 0;
		}

		AcDbLine *pLine = new AcDbLine(mVerts[i], mVerts[nextIndex]);
		pLine->setPropertiesFrom(this);
		entitySet.append(pLine);
	}
	return Acad::eOk;
}


void FaneTriangle::subList() const {
	AcDbEntity::list();
	for (size_t i = 0; i < 3; i++)
	{
		acutPrintf(TEXT("\n 顶点%d：（%g，%g，%g）"),mVerts[i].x, mVerts[i].y, mVerts[i].z);
	}
}


void FaneTriangle::getVerts(AcGePoint3dArray &verts) const {
	assertReadEnabled();
	verts.setLogicalLength(0);
	for (size_t i = 0; i < 3; i++)
	{
		verts.append(mVerts[i]);
	}
}

double FaneTriangle::getArea() const {
	AcDbPolyline *pLine = GetPolyline();
	double area = 0;
	pLine->getArea(area);
	delete pLine;
	return area;
}

void FaneTriangle::setVertAt(int index, const AcGePoint3d &pt) {
	assertWriteEnabled();
	if (index >= 0 && index <= 2)
	{
		mVerts[index] = pt;
	}
}


AcDbPolyline* FaneTriangle::GetPolyline() const {
	AcDbPolyline* polyline = new AcDbPolyline();

	for (size_t i = 0; i < 3; i++)
	{
		polyline->addVertexAt(i, ToPoint2d(mVerts[i]));
	}
	polyline->setClosed(Adesk::kTrue);
	return polyline;
}

AcGePoint2d FaneTriangle::ToPoint2d(const AcGePoint3d &pt) const {
	return AcGePoint2d(pt.x, pt.y);
}





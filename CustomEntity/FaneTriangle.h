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

	virtual Acad::ErrorStatus subGetOsnapPoints(
		AcDb::OsnapMode osnapMode,
		int gsSelectionMark,
		const AcGePoint3d& pickPoint,
		const AcGePoint3d& lastPoint,
		const AcGeMatrix3d& viewXform,
		AcGePoint3dArray& snapPoints,
		AcDbIntArray& geomIds
	) const;

	virtual Acad::ErrorStatus subGetOsnapPoints(
		AcDb::OsnapMode osnapMode,
		int gsSelectionMark,
		const AcGePoint3d& pickPoint,
		const AcGePoint3d& lastPoint,
		const AcGeMatrix3d& viewXform,
		AcGePoint3dArray& snapPoints,
		AcDbIntArray& geomIds,
		const AcGeMatrix3d& insertionMat
	) const;

	virtual Acad::ErrorStatus subGetGripPoints(
			AcGePoint3dArray& gripPoints,
			AcDbIntArray&  osnapModes,
			AcDbIntArray&  geomIds) const;

	virtual Acad::ErrorStatus subMoveGripPointsAt(
			const AcDbIntArray& indices,
			const AcGeVector3d& offset);

	virtual Acad::ErrorStatus subTransformBy(
			const AcGeMatrix3d& xform);

	virtual Acad::ErrorStatus subGetGeomExtents(
			AcDbExtents& extents) const;

	virtual Acad::ErrorStatus subExplode(
			AcDbVoidPtrArray& entitySet) const;

	virtual void subList() const;

	void getVerts(AcGePoint3dArray &verts) const;

	double getArea() const;

	void setVertAt(int index, const AcGePoint3d &pt);

private:
	AcGePoint3d mVerts[3];
	AcDbPolyline* GetPolyline() const;
	// �β��ϵ�const��ʾ�����ٺ����ڲ��ı��β�ֵ���������const������ĸ��β������ã�
	// �ǿ���ͨ�����ı䱻���ö����ֵ�ģ������ϵ�const��ʾ�ú��������޸����Ա����
	AcGePoint2d ToPoint2d(const AcGePoint3d &pt) const; 
};


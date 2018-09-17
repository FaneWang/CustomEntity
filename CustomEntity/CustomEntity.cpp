#pragma once
#include "stdafx.h"
#include "CustomEntity.h"

namespace CustomEntity {

	FaneTriangleWrapper::FaneTriangleWrapper() : Autodesk::AutoCAD::DatabaseServices::Entity(System::IntPtr(new FaneTriangle()),true){}

	FaneTriangleWrapper::FaneTriangleWrapper(System::IntPtr unmanagedPointer,bool autoDelete) : Autodesk::AutoCAD::DatabaseServices::Entity(unmanagedPointer,autoDelete){}

	FaneTriangleWrapper::FaneTriangleWrapper(Point3d pt1, Point3d pt2, Point3d pt3) : Autodesk::AutoCAD::DatabaseServices::Entity(System::IntPtr(new FaneTriangle(GETPOINT3D(pt1), GETPOINT3D(pt2), GETPOINT3D(pt3))),true){}
}


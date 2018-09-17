// (C) Copyright 2018 by Fane
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.EditorInput;
using CustomEntity;

// 这句代码并不是强制性的，但它可以提升加载性能
[assembly: CommandClass(typeof(CustomEntityCSharpTest.MyCommands))]

namespace CustomEntityCSharpTest
{
    // 当用户在文档环境中第一次执行一个命令时
    // AutoCAD会为每个文档实例化这个类
    // 换句话说，这个类通常不包含静态成员
    public class MyCommands
    {
        // 命令属性可以应用到任何公共类的任何公共函数
        // 应用命令的函数通常不应该有参数和返回值
        // 如果是普通方法，那么会为每个文档单独实例化
        // 如果是一个静态方法，那么就与文档环境无关

        // 本地化名称的重载形式会导致资源异常，因此不使用，通常的是全局名（所有语言）
        [CommandMethod("MyGroup", "MyCommand", CommandFlags.Modal)]
        public void MyCommand() // 这个方法可以使用任意名称，执行命令时使用上一句代码定义的名称
        {
            // Put your code here
            Database db = HostApplicationServices.WorkingDatabase;
            using (OpenCloseTransaction trans = db.TransactionManager.StartOpenCloseTransaction())
            {
                BlockTable bt = (BlockTable)trans.GetObject(db.BlockTableId, OpenMode.ForRead);
                BlockTableRecord btr = (BlockTableRecord)trans.GetObject(db.CurrentSpaceId, OpenMode.ForWrite);
                Point3d pt1 = new Point3d();
                Point3d pt2 = new Point3d();
                Point3d pt3 = new Point3d();

                if (GetPoint("\n输入起点:",out pt1) && GetPoint("\n输入起点:", out pt2) && GetPoint("\n输入起点:", out pt3))
                {
                    Editor ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor;
                    FaneTriangleWrapper faneTriangle = new FaneTriangleWrapper(pt1, pt2, pt3);
                    //double area = faneTriangle.GetArea();
                    Point3dCollection collection = null;
                    faneTriangle.GetVerts(collection);
                    foreach (Point3d item in collection)
                    {                        
                        ed.WriteMessage("\n三角形的顶点X坐标：{0}", item.X);
                    }
                    btr.AppendEntity(faneTriangle);
                    trans.AddNewlyCreatedDBObject(faneTriangle, true);
                    
                    trans.Commit();
                }
            }
        }


        public bool GetPoint(string prompt,out Point3d pt)
        {
            Editor ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor;
            PromptPointResult ppr = ed.GetPoint(prompt);
            if (ppr.Status == PromptStatus.OK)
            {
                pt = ppr.Value;
                Matrix3d mat = ed.CurrentUserCoordinateSystem;
                pt.TransformBy(mat);
                return true;
            }
            else
            {
                pt = new Point3d();
                return false;
            }
        }


        public bool GetPoint(string prompt,Point3d basePoint,out Point3d pt)
        {
            Editor ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor;
            PromptPointOptions ppo = new PromptPointOptions(prompt);
            ppo.BasePoint = basePoint;
            ppo.UseBasePoint = true;
            PromptPointResult ppr = ed.GetPoint(ppo);

            if (ppr.Status == PromptStatus.OK)
            {
                pt = ppr.Value;
                Matrix3d mat = ed.CurrentUserCoordinateSystem;
                pt.TransformBy(mat);
                return true;
            }
            else
            {
                pt = new Point3d();
                return false;
            }
        }

    }
}

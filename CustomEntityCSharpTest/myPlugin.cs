// (C) Copyright 2018 by Fane
using System;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.EditorInput;

// 这句代码并不是强制性的，但它可以提升加载性能
[assembly: ExtensionApplication(typeof(CustomEntityCSharpTest.MyPlugin))]

namespace CustomEntityCSharpTest
{
    // 这个类只会被AutoCAD实例化一次，并在整个程序运行期间存在
    // 如果不做任何一次性的初始化动作，那么应该移除这个类
    class MyPlugin : IExtensionApplication
    {
        public void Initialize()
        {
            // put your code here
        }

        public void Terminate()
        {
            // put your code here
        }
    }
}

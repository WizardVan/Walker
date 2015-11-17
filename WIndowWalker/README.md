A Windows Class name enumerator.It returns class name not title of windows.

EnumWindows function is a system function that can enumerate all top windows class.You can read how to use this function on MSDN.

EnumWindowsProc is a callback function for EnumWindows to get class name of the windows handler sent by EnumWindowsProc.

FindWindow function need windows class name as parameters to determine whether a program is running.

程序主要就是枚举所有窗口然后拿到类名，黑名单扔给findwindows。

EnumWindows 系统函数，遍历所有顶层窗口

EnumWindowsProc 回调函数，用来处理由EnumWindows返回的句柄

FindWindow 通过类名来检查窗口是否存在

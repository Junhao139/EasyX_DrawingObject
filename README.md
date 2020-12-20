# EasyX_DrawingObject
 - 简介：使用 EasyX 作为主要绘图库，将绘图对象化，节省开发时间。
 
 
更新日志入口：[`更新日志`](https://github.com/Junhao139/EasyX_DrawingObject/UpdateLog.md)
文档入口（暂无）：[`技术文档`](https://github.com/Junhao139/EasyX_DrawingObject/)

配置需要：
* 库
  * ```#include <easyx.h>``` (下载地址：[Easyx](https://easyx.cn/downloads/))
  * ```#include <altstr.h>``` (Visual Studio 自带)


主要使用方法：
```cpp
WindowProc wnd(640, 480, 0xffffff);
```

然后声明一个对象：
```cpp
IP_Rectangle rect = IP_Rectangle();
```

将对象传入窗口渲染流：
```cpp
wnd.AddElement(&rect);
```

再开启窗口（当然您可以在对象声明后的任何位置使用此函数）：
**！本函数是不可或缺的。**
```cpp
wnd.Start();
```


这样子就可以让 WindowProc 的对象来绘图了。

就像您在 EasyX 中经常用到的 ```_getch()``` 函数（作为结尾暂停）一样，您也可以将该函数或者一个循环添加到结尾，来避免因程序结束而窗口自行消失的情况。如果您确实在结尾做了暂停措施但窗口依然消失了，那有可能是编译器提前对类执行了析构函数。您只需要这样一行代码就可以关闭这种情况，但是会有一个限制：
```cpp
wnd.AutomaticClose(false);  /* 阻止自行关闭 */
```
使用该函数后需要在您想要关闭窗口的位置写上：
```cpp
wnd.Close();
```

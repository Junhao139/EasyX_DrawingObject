# EasyX_DrawingObject
使用 EasyX 作为主要绘图库，将绘图对象化，节省开发时间。


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


这样子就可以让 WindowProc 的对象来绘图了。

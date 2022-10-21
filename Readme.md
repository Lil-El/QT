# QT

## [安装](https://www.qt.io/download)

- 组件选择：除了默认之外，还要选择**QT version**
    - MSVC: 表示使用vs运行项目
    - MinGW: 这个要选择，包含了GNU和windows头文件的集合
    - QT: QT开头的以及Addition Tools要选择
    - `如果忘记选择了，可以在QT的安装目录下运行MaintenanceTool.exe`

## Create Project

- 选择QT版本时，如果没有需要下载对应的组件，见上
- 选择代码目录时，不需要为项目添加目录，设置为project的目录就可以了
- Kit Selection时没有选项，要在Manage中的QT Version中点击“Link with QT...”按钮，设置QT的版本目录（QT的安装目录）

## Git

- 工具->Git-> Remote.. -> 设置git地址：name：origin，url：https://github.com/Lil-El/QT.git （fetch，pull，push）
- 工具->Git-> Remote.. -> commit文件

## Plugin

- Help->关于插件->勾选格式化、Beautifier的插件，并重启
- [参考](https://blog.csdn.net/qq_35976351/article/details/85037645)

## TODO

- https://blog.csdn.net/SwordArcher/article/details/81560401
- https://www.w3cschool.cn/learnroadqt/m4x21j43.html
- https://zhuanlan.zhihu.com/p/450087085
- https://www.runoob.com/w3cnote/cpp-std-thread.html
- https://blog.csdn.net/qq_20853741/article/details/114093265

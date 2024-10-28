#pragma once
#include "imgui.h"
namespace App
{
    //主UI函数，放停靠空间的代码
    void RenderUI();

    //隐藏窗口的TabBar
    void HideTabBar();
    //导航页面
    void ShowTreeView();
    //内容页面
    void ShowMainView();
    /*
    * 内容页面0-5
    */
    void ShowPageView0();
    void ShowPageView1();
    void ShowPageView2();
    void ShowPageView3();
    void ShowPageView4();
}


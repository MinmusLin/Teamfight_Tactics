/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AppDelegate.cpp
 * File Function: AppDelegate类的实现
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include "AppDelegate.h"
#include "Scene/StartupScene.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"

// 分辨率设置
static cocos2d::Size s_designResolutionSize = cocos2d::Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
static cocos2d::Size s_smallResolutionSize = cocos2d::Size(SMALL_RESOLUTION_WIDTH, SMALL_RESOLUTION_HEIGHT);
static cocos2d::Size s_mediumResolutionSize = cocos2d::Size(MEDIUM_RESOLUTION_WIDTH, MEDIUM_RESOLUTION_HEIGHT);
static cocos2d::Size s_largeResolutionSize = cocos2d::Size(LARGE_RESOLUTION_WIDTH, LARGE_RESOLUTION_HEIGHT);

// 析构函数
AppDelegate::~AppDelegate()
{
    cocos2d::experimental::AudioEngine::end();
}

// 初始化 OpenGL 上下文属性
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

// 当应用程序完成启动并准备进入主循环时调用此函数
bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = cocos2d::Director::getInstance(); // 获取游戏引擎的导演实例
    auto glview = director->getOpenGLView(); // 获取 OpenGL 视图

    // 如果 OpenGL 视图不存在，根据平台创建
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // 在 Windows、Mac、Linux 平台上创建 OpenGL 视图
        glview = cocos2d::GLViewImpl::createWithRect(APPLICATION_TITLE, cocos2d::Rect(0, 0, s_designResolutionSize.width, s_designResolutionSize.height));
#else
        // 在其他平台上创建 OpenGL 视图
        glview = cocos2d::GLViewImpl::create(APPLICATION_TITLE);
#endif
        // 设置 OpenGL 视图
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(false); // 关闭显示性能统计信息
    director->setAnimationInterval(1 / FRAME_RATE); // 设置游戏循环的帧率
    glview->setDesignResolutionSize(s_designResolutionSize.width, s_designResolutionSize.height, ResolutionPolicy::NO_BORDER); // 设置设计分辨率
    const auto frameSize = glview->getFrameSize(); // 获取窗口的帧大小

    // 根据窗口大小设置内容缩放因子
    if (frameSize.height > s_mediumResolutionSize.height) {
        director->setContentScaleFactor(MIN(s_largeResolutionSize.height / s_designResolutionSize.height, s_largeResolutionSize.width / s_designResolutionSize.width));
    }
    else if (frameSize.height > s_smallResolutionSize.height) {
        director->setContentScaleFactor(MIN(s_mediumResolutionSize.height / s_designResolutionSize.height, s_mediumResolutionSize.width / s_designResolutionSize.width));
    }
    else {
        director->setContentScaleFactor(MIN(s_smallResolutionSize.height / s_designResolutionSize.height, s_smallResolutionSize.width / s_designResolutionSize.width));
    }

    // 运行启动场景
    director->runWithScene(StartupScene::createScene());

    return true;
}

// 当应用程序进入后台时调用此函数
void AppDelegate::applicationDidEnterBackground()
{
    cocos2d::Director::getInstance()->stopAnimation();
    cocos2d::experimental::AudioEngine::pauseAll();
}

// 当应用程序从后台返回到前台时调用此函数
void AppDelegate::applicationWillEnterForeground()
{
    cocos2d::Director::getInstance()->startAnimation();
    cocos2d::experimental::AudioEngine::resumeAll();
}
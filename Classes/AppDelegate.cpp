/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AppDelegate.cpp
 * File Function: AppDelegate类的实现
 * Author:        林继申
 * Update Date:   2023/12/4
 ****************************************************************/

#include "AppDelegate.h"
#include "Scenes\InitialScene.h"
#include "..\proj.win32\Constant.h"

#define USE_AUDIO_ENGINE 0
#define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time."
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size s_designResolutionSize = cocos2d::Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
static cocos2d::Size s_smallResolutionSize = cocos2d::Size(SMALL_RESOLUTION_WIDTH, SMALL_RESOLUTION_HEIGHT);
static cocos2d::Size s_mediumResolutionSize = cocos2d::Size(MEDIUM_RESOLUTION_WIDTH, MEDIUM_RESOLUTION_HEIGHT);
static cocos2d::Size s_largeResolutionSize = cocos2d::Size(LARGE_RESOLUTION_WIDTH, LARGE_RESOLUTION_HEIGHT);

// 析构函数
AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// 初始化 OpenGL 上下文属性
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    GLView::setGLContextAttrs(glContextAttrs);
}

// 当应用程序完成启动并准备进入主循环时调用此函数
bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect(APPLICATION_TITLE, cocos2d::Rect(0, 0, s_designResolutionSize.width, s_designResolutionSize.height));
#else
        glview = GLViewImpl::create(APPLICATION_TITLE);
#endif
        director->setOpenGLView(glview);
    }
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0f / ANIMATION_INTERVAL);
    glview->setDesignResolutionSize(s_designResolutionSize.width, s_designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    if (frameSize.height > s_mediumResolutionSize.height) {
        director->setContentScaleFactor(MIN(s_largeResolutionSize.height / s_designResolutionSize.height, s_largeResolutionSize.width / s_designResolutionSize.width));
    }
    else if (frameSize.height > s_smallResolutionSize.height) {
        director->setContentScaleFactor(MIN(s_mediumResolutionSize.height / s_designResolutionSize.height, s_mediumResolutionSize.width / s_designResolutionSize.width));
    }
    else {
        director->setContentScaleFactor(MIN(s_smallResolutionSize.height / s_designResolutionSize.height, s_smallResolutionSize.width / s_designResolutionSize.width));
    }
    director->runWithScene(InitialScene::createScene());
    return true;
}

// 当应用程序进入后台时调用此函数
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// 当应用程序从后台返回到前台时调用此函数
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AppDelegate.cpp
 * File Function: AppDelegate���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/24
 ****************************************************************/

#include "AppDelegate.h"
#include "Scene/StartupScene.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "proj.win32/Constant.h"

// ��Ƶ����ѡ��
#define USE_AUDIO_ENGINE 0
#define USE_SIMPLE_AUDIO_ENGINE 1
#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time."
#endif

// �����ռ�
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

// �ֱ�������
static cocos2d::Size s_designResolutionSize = cocos2d::Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
static cocos2d::Size s_smallResolutionSize = cocos2d::Size(SMALL_RESOLUTION_WIDTH, SMALL_RESOLUTION_HEIGHT);
static cocos2d::Size s_mediumResolutionSize = cocos2d::Size(MEDIUM_RESOLUTION_WIDTH, MEDIUM_RESOLUTION_HEIGHT);
static cocos2d::Size s_largeResolutionSize = cocos2d::Size(LARGE_RESOLUTION_WIDTH, LARGE_RESOLUTION_HEIGHT);

// ��������
AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// ��ʼ�� OpenGL ����������
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

// ��Ӧ�ó������������׼��������ѭ��ʱ���ô˺���
bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = cocos2d::Director::getInstance(); // ��ȡ��Ϸ����ĵ���ʵ��
    auto glview = director->getOpenGLView(); // ��ȡ OpenGL ��ͼ

    // ��� OpenGL ��ͼ�����ڣ�����ƽ̨����
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        // �� Windows��Mac��Linux ƽ̨�ϴ��� OpenGL ��ͼ
        glview = cocos2d::GLViewImpl::createWithRect(GBKToUTF8::getString(APPLICATION_TITLE), cocos2d::Rect(0, 0, s_designResolutionSize.width, s_designResolutionSize.height));
#else
        // ������ƽ̨�ϴ��� OpenGL ��ͼ
        glview = cocos2d::GLViewImpl::create(GBKToUTF8::getString(APPLICATION_TITLE));
#endif
        // ���� OpenGL ��ͼ
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(false); // �ر���ʾ����ͳ����Ϣ
    director->setAnimationInterval(1 / FRAME_RATE); // ������Ϸѭ����֡��
    glview->setDesignResolutionSize(s_designResolutionSize.width, s_designResolutionSize.height, ResolutionPolicy::NO_BORDER); // ������Ʒֱ���
    const auto frameSize = glview->getFrameSize(); // ��ȡ���ڵ�֡��С

    // ���ݴ��ڴ�С����������������
    if (frameSize.height > s_mediumResolutionSize.height) {
        director->setContentScaleFactor(MIN(s_largeResolutionSize.height / s_designResolutionSize.height, s_largeResolutionSize.width / s_designResolutionSize.width));
    }
    else if (frameSize.height > s_smallResolutionSize.height) {
        director->setContentScaleFactor(MIN(s_mediumResolutionSize.height / s_designResolutionSize.height, s_mediumResolutionSize.width / s_designResolutionSize.width));
    }
    else {
        director->setContentScaleFactor(MIN(s_smallResolutionSize.height / s_designResolutionSize.height, s_smallResolutionSize.width / s_designResolutionSize.width));
    }

    // ������������
    director->runWithScene(StartupScene::createScene());

    return true;
}

// ��Ӧ�ó�������̨ʱ���ô˺���
void AppDelegate::applicationDidEnterBackground()
{
    cocos2d::Director::getInstance()->stopAnimation();
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// ��Ӧ�ó���Ӻ�̨���ص�ǰ̨ʱ���ô˺���
void AppDelegate::applicationWillEnterForeground()
{
    cocos2d::Director::getInstance()->startAnimation();
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
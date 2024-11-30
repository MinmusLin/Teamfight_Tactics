/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AppDelegate.cpp
 * File Function: AppDelegate���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include "AppDelegate.h"
#include "Scene/StartupScene.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"

// �ֱ�������
static cocos2d::Size s_designResolutionSize = cocos2d::Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
static cocos2d::Size s_smallResolutionSize = cocos2d::Size(SMALL_RESOLUTION_WIDTH, SMALL_RESOLUTION_HEIGHT);
static cocos2d::Size s_mediumResolutionSize = cocos2d::Size(MEDIUM_RESOLUTION_WIDTH, MEDIUM_RESOLUTION_HEIGHT);
static cocos2d::Size s_largeResolutionSize = cocos2d::Size(LARGE_RESOLUTION_WIDTH, LARGE_RESOLUTION_HEIGHT);

// ��������
AppDelegate::~AppDelegate()
{
    cocos2d::experimental::AudioEngine::end();
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
        glview = cocos2d::GLViewImpl::createWithRect(APPLICATION_TITLE, cocos2d::Rect(0, 0, s_designResolutionSize.width, s_designResolutionSize.height));
#else
        // ������ƽ̨�ϴ��� OpenGL ��ͼ
        glview = cocos2d::GLViewImpl::create(APPLICATION_TITLE);
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
    cocos2d::experimental::AudioEngine::pauseAll();
}

// ��Ӧ�ó���Ӻ�̨���ص�ǰ̨ʱ���ô˺���
void AppDelegate::applicationWillEnterForeground()
{
    cocos2d::Director::getInstance()->startAnimation();
    cocos2d::experimental::AudioEngine::resumeAll();
}
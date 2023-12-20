/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModePreparationScene.cpp
 * File Function: OfflineModePreparationScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#include "OfflineModePreparationScene.h"
#include "OfflineModeBattleScene.h"
#include "Control/OfflineModeControl.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"

USING_NS_CC;

// ��ϰģʽ��Ϸ������
extern OfflineModeControl* g_offlineModeControl;

// ��������
Scene* OfflineModePreparationScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OfflineModePreparationScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool OfflineModePreparationScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }
    
    // ���ر���
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModePreparationScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuActiveButton.png");

    // ���ð�ťλ��
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + 450, screenSize.height / 2 - 100)); // TODO: ��ťλ��ͨ�����������

    // Ϊ��ť����¼�������
    returnMenuButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            delete g_offlineModeControl;
            g_offlineModeControl = nullptr;
            Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), Color3B::WHITE));
        }
        });

    // ����ť��ӵ�������
    this->addChild(returnMenuButton);

    // ������ϰģʽ��Ϸ������
    g_offlineModeControl->run(this);

    // ����������
    auto progressBar = ui::LoadingBar::create("../Resources/LoadingBars/CountdownLoadingBar.png");
    progressBar->setPosition(Vec2(BATTLE_SCENE_LOADINGBAR_X, BATTLE_SCENE_LOADINGBAR_Y));
    progressBar->setPercent(0);
    progressBar->setName("CountdownLoadingBar");
    this->addChild(progressBar);

    // ������ǩ����ʾ����
    auto progressLabel = Label::createWithTTF("", "../Resources/Fonts/FZZGY_J_EB.ttf", BATTLE_SCENE_LOADINGBAR_LABLE_FONT_SIZE);
    progressLabel->setPosition(Vec2(progressBar->getPosition().x - progressBar->getContentSize().width / 2 + BATTLE_SCENE_LOADINGBAR_LABLE_OFFSET_X, progressBar->getPosition().y));
    progressLabel->setVisible(false);
    progressLabel->setName("CountdownLoadingBarLabel");
    this->addChild(progressLabel);

    // ���ý����������߼����ʱ��
    setScheduleOnce(progressBar, progressLabel);

    return true;
}

// ���������½���ʱ����
void OfflineModePreparationScene::onEnter()
{
    // ���û���� onEnter ����
    Scene::onEnter();

    // ���ý������ͱ�ǩ
    auto progressBar = dynamic_cast<ui::LoadingBar*>(this->getChildByName("CountdownLoadingBar"));
    auto progressLabel = dynamic_cast<Label*>(this->getChildByName("CountdownLoadingBarLabel"));
    if (progressBar && progressLabel) {
        progressBar->setPercent(0);
        progressLabel->setVisible(false);

        // ȡ��֮ǰ�����ж�ʱ��
        this->unscheduleAllCallbacks();

        // �������ý����������߼����ʱ��
        setScheduleOnce(progressBar, progressLabel);
    }
}

// ���ý����������߼����ʱ��
void OfflineModePreparationScene::setScheduleOnce(ui::LoadingBar* progressBar, Label* progressLabel)
{
    // ˢ���̵�
    g_offlineModeControl->getHumanPlayer()->refreshShop(this);

    // ���½������ͱ�ǩ
    const float interval = BATTLE_SCENE_LOADINGBAR_DURATION / 1000.0f; // ÿ 0.1% ����ʱ��
    for (int i = 0; i <= 1000; i++) {
        this->scheduleOnce([progressBar, progressLabel, i](float dt) {
            int sceond = static_cast<int>(BATTLE_SCENE_LOADINGBAR_DURATION - i * BATTLE_SCENE_LOADINGBAR_DURATION / 1000 + 0.999);
            progressLabel->setVisible(sceond <= BATTLE_SCENE_LOADINGBAR_LABLE_THRESHOLD);
            progressBar->setPercent(i / 10.0);
            progressLabel->setString((sceond >= 10 ? "" : " ") + std::to_string(sceond) + "s");
            float percentage = progressBar->getPercent() / 100.0f;
            float xPosition = progressBar->getPosition().x - progressBar->getContentSize().width / 2 + progressBar->getContentSize().width * percentage + BATTLE_SCENE_LOADINGBAR_LABLE_OFFSET_X;
            progressLabel->setPosition(Vec2(xPosition, progressBar->getPosition().y));
            }, interval * i, "CountdownLoadingBar" + std::to_string(i));
    }

    // ���ü�ʱ��
    this->scheduleOnce([this](float dt) {
        // �����ͷ���һ������������¼���ǿ�Ʒ��µ�ǰս��Ӣ�ۣ�
        EventMouse event(EventMouse::MouseEventType::MOUSE_UP);
        event.setMouseButton(EventMouse::MouseButton::BUTTON_LEFT);
        _eventDispatcher->dispatchEvent(&event);

        // ������ϰģʽ��ս����
        Director::getInstance()->pushScene(OfflineModeBattleScene::create());
        }, BATTLE_SCENE_LOADINGBAR_DURATION + SCENE_TRANSITION_DURATION, "IsAlreadyPrepared");
}
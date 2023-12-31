/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModePreparationScene.cpp
 * File Function: OnlineModePreparationScene���ʵ��
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include "OnlineModePreparationScene.h"
#include "Control/OnlineModeControl.h"
#include "Scene/OnlineModeBattleScene.h"
#include "Button/HoverButton.h"
#include "Layer/ScoreBoardLayer.h"
#include "MenuScene.h"
#include "proj.win32/AudioPlayer.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ����ģʽ��Ϸ������
extern OnlineModeControl* g_onlineModeControl;

// ��������
Scene* OnlineModePreparationScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OnlineModePreparationScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool OnlineModePreparationScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ���� HumanPlayer ��ĵ�ǰ����ָ��
    g_onlineModeControl->getHumanPlayer()->setCurrentScene(this);

    // ��������
    audioPlayer("../Resources/Music/PreparationScene_RagsToRings.mp3", true);

    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModePreparationScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // �����ȼ���ǩ
    Label* levelLabel;
    const int currentBattleChampionCount = g_onlineModeControl->getHumanPlayer()->getMaxBattleChampionCount();
    if (currentBattleChampionCount >= (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune") == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1))) {
        levelLabel = Label::createWithTTF(u8"��ߵȼ�", "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_LEVEL_LABEL_FONT_SIZE);
    }
    else {
        levelLabel = Label::createWithTTF(u8"�ȼ���" + std::to_string(currentBattleChampionCount - BATTLE_AREA_MIN_CHAMPION_COUNT + 1), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_LEVEL_LABEL_FONT_SIZE);
    }
    levelLabel->setAnchorPoint(Vec2(0, 0.5));
    levelLabel->setPosition(Vec2(screenSize.width / 2 + SHOP_LEVEL_LABEL_OFFSET_X, screenSize.height / 2 + SHOP_LEVEL_LABEL_OFFSET_Y));
    levelLabel->setName("LevelLabel");
    this->addChild(levelLabel);

    // �������������ǩ
    Label* coinLabel = Label::createWithTTF(std::to_string(g_onlineModeControl->getHumanPlayer()->getGoldCoin()), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_COIN_LABEL_FONT_SIZE);
    coinLabel->setAnchorPoint(Vec2(1, 0.5));
    coinLabel->setPosition(Vec2(screenSize.width / 2 + SHOP_COIN_LABEL_OFFSET_X, screenSize.height / 2 + SHOP_COIN_LABEL_OFFSET_Y));
    coinLabel->setName("CoinLabel");
    this->addChild(coinLabel);

    // ����������
    auto progressBar = cocos2d::ui::LoadingBar::create("../Resources/ImageElements/CountdownLoadingBar.png");
    progressBar->setPosition(Vec2(BATTLE_SCENE_LOADINGBAR_X, BATTLE_SCENE_LOADINGBAR_Y));
    progressBar->setPercent(0);
    progressBar->setName("CountdownLoadingBar");
    this->addChild(progressBar);

    // ������ǩ����ʾ����
    auto progressLabel = Label::createWithTTF("", "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", BATTLE_SCENE_LOADINGBAR_LABEL_FONT_SIZE);
    progressLabel->setPosition(Vec2(progressBar->getPosition().x - progressBar->getContentSize().width / 2 + BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X, progressBar->getPosition().y));
    progressLabel->setVisible(false);
    progressLabel->setName("CountdownLoadingBarLabel");
    this->addChild(progressLabel);

    // ���ý����������߼����ʱ��
    setScheduleOnce(progressBar, progressLabel);

    // ������ť
    auto uplevelButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/UplevelDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/UplevelHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/UplevelActiveButton.png");
    auto refreshButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/RefreshDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/RefreshHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/RefreshActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/ReturnMenuActiveButton.png");

    // ���ð�ťλ��
    uplevelButton->setPosition(Vec2(screenSize.width / 2 + SHOP_UPLEVEL_BUTTON_OFFSET_X, screenSize.height / 2 + SHOP_UPLEVEL_BUTTON_OFFSET_Y));
    refreshButton->setPosition(Vec2(screenSize.width / 2 + SHOP_REFRESH_BUTTON_OFFSET_X, screenSize.height / 2 + SHOP_REFRESH_BUTTON_OFFSET_Y));
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_X, screenSize.height / 2 + BATTLE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y));

    // �������������ǩ
    auto refreshCoinLabel = Label::createWithTTF(std::to_string(REFRESH_SHOP_PRICE), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_COIN_LABEL_FONT_SIZE);
    refreshCoinLabel->setAnchorPoint(Vec2(1, 0.5));
    refreshCoinLabel->setPosition(SHOP_COIN_LABEL_START_X, SHOP_REFRESH_COIN_LABEL_START_Y);
    this->addChild(refreshCoinLabel, 2);
    auto uplevelCoinLabel = Label::createWithTTF(std::to_string(UPLEVEL_PRICE.at(g_onlineModeControl->getHumanPlayer()->getMaxBattleChampionCount())), "../Resources/Fonts/DingDingJinBuTi.ttf", SHOP_COIN_LABEL_FONT_SIZE);
    uplevelCoinLabel->setAnchorPoint(Vec2(1, 0.5));
    uplevelCoinLabel->setPosition(SHOP_COIN_LABEL_START_X, SHOP_UPLEVEL_COIN_LABEL_START_Y);
    this->addChild(uplevelCoinLabel, 2);

    // Ϊ��ť����¼�������
    uplevelButton->addTouchEventListener([this, uplevelCoinLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            g_onlineModeControl->getHumanPlayer()->addBattleChampionCount();
            const int maxBattleChampionCount = g_onlineModeControl->getHumanPlayer()->getMaxBattleChampionCount();
            uplevelCoinLabel->setString(maxBattleChampionCount >= (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune") == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1)) ? "" : std::to_string(UPLEVEL_PRICE.at(maxBattleChampionCount)));
        }
        });
    refreshButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            g_onlineModeControl->getHumanPlayer()->refreshShop();
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            delete g_onlineModeControl;
            g_onlineModeControl = nullptr;
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    // ����ť��ӵ�������
    this->addChild(uplevelButton, 1);
    this->addChild(refreshButton, 1);
    this->addChild(returnMenuButton);

    // ��ʼ��ս��Ӣ��ɾ����ť
    g_onlineModeControl->getHumanPlayer()->initializeDeleteChampionButton();

    // �����������
    auto scoreBoardLayer = ScoreBoardLayer::create();
    scoreBoardLayer->initialize(g_onlineModeControl->getCurrentConnections());
    scoreBoardLayer->showScoreBoard(g_onlineModeControl->getCurrentConnections(), g_onlineModeControl->getPlayerNames(), g_onlineModeControl->getPlayerHealthPoints());
    scoreBoardLayer->setName("ScoreBoardLayer");
    this->addChild(scoreBoardLayer);

    return true;
}

// ���������½���ʱ����
void OnlineModePreparationScene::onEnter()
{
    // ���û���� onEnter ����
    Scene::onEnter();

    // ���÷������
    auto scoreBoardLayer = dynamic_cast<ScoreBoardLayer*>(this->getChildByName("ScoreBoardLayer"));
    scoreBoardLayer->showScoreBoard(g_onlineModeControl->getCurrentConnections(), g_onlineModeControl->getPlayerNames(), g_onlineModeControl->getPlayerHealthPoints());

    // ���ý������ͱ�ǩ
    auto progressBar = dynamic_cast<cocos2d::ui::LoadingBar*>(this->getChildByName("CountdownLoadingBar"));
    auto progressLabel = dynamic_cast<Label*>(this->getChildByName("CountdownLoadingBarLabel"));
    if (progressBar && progressLabel) {
        // ���ý������ٷֱ�
        progressBar->setPercent(0);
        progressLabel->setVisible(false);

        // ȡ��֮ǰ�����ж�ʱ��
        this->unscheduleAllCallbacks();

        // �������ý����������߼����ʱ��
        setScheduleOnce(progressBar, progressLabel);
    }
}

// ���ý����������߼����ʱ��
void OnlineModePreparationScene::setScheduleOnce(cocos2d::ui::LoadingBar* progressBar, Label* progressLabel)
{
    // ˢ���̵�
    g_onlineModeControl->getHumanPlayer()->refreshShop();

    // ���½������ͱ�ǩ
    constexpr float interval = BATTLE_SCENE_LOADINGBAR_DURATION / 1000.0f; // ÿ 0.1% ����ʱ��
    for (int i = 0; i <= 1000; i++) {
        this->scheduleOnce([progressBar, progressLabel, i](float dt) {
            int sceond = static_cast<int>(BATTLE_SCENE_LOADINGBAR_DURATION - i * BATTLE_SCENE_LOADINGBAR_DURATION / 1000 + 0.999);
            progressLabel->setVisible(sceond <= BATTLE_SCENE_LOADINGBAR_LABEL_THRESHOLD);
            progressBar->setPercent(i / 10.0);
            progressLabel->setString((sceond >= 10 ? "" : " ") + std::to_string(sceond) + "s");
            const float percentage = progressBar->getPercent() / 100.0f;
            const float xPosition = progressBar->getPosition().x - progressBar->getContentSize().width / 2 + progressBar->getContentSize().width * percentage + BATTLE_SCENE_LOADINGBAR_LABEL_OFFSET_X;
            progressLabel->setPosition(Vec2(xPosition, progressBar->getPosition().y));
            }, interval * i, "CountdownLoadingBar" + std::to_string(i));
    }

    // ���ü�ʱ��
    this->scheduleOnce([this](float dt) {
        // �����ͷ���һ���������ͷ��¼���ǿ�Ʒ��µ�ǰս��Ӣ�ۣ�
        cocos2d::EventMouse event(cocos2d::EventMouse::MouseEventType::MOUSE_UP);
        event.setMouseButton(cocos2d::EventMouse::MouseButton::BUTTON_LEFT);
        _eventDispatcher->dispatchEvent(&event);

        // ��������ģʽ��ս����
        char buffer[BUFFER_SIZE];
        sprintf(buffer, BATTLE_MAP_FORMAT, g_onlineModeControl->serializePlayerMap().c_str());
        g_onlineModeControl->sendMessage(buffer, strlen(buffer));
        cocos2d::Director::getInstance()->pushScene(OnlineModeBattleScene::create());
        }, BATTLE_SCENE_LOADINGBAR_DURATION + SCENE_TRANSITION_DURATION, "IsAlreadyPrepared");
}
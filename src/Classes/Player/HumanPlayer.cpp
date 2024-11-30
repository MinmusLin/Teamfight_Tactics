/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.cpp
 * File Function: HumanPlayer类的实现
 * Author:        林继申、杨宇琨
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include <algorithm>
#include "HumanPlayer.h"
#include "LocationMap/LocationMap.h"
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Event;
using cocos2d::EventMouse;
using cocos2d::Vec2;

// 构造函数
HumanPlayer::HumanPlayer(const std::string nickname) :
    Player(nickname),
    currentScene(nullptr),
    deleteChampionButton(nullptr),
    championAttributesLayer(nullptr),
    placementMarkerLayer(nullptr),
    nearestPlacementMarker(nullptr),
    startLocation({ WaitingArea, -1 }),
    maxBattleChampionCount(BATTLE_AREA_MIN_CHAMPION_COUNT),
    goldCoin(INITIAL_GOLD_COIN)
{
    healthPoints = (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune")) == Warriors)
        ? INITIAL_HEALTH_POINTS + RUNE_WARRIOR_HEALTH_POINTS_BUFF
        : INITIAL_HEALTH_POINTS;
    std::fill_n(shopChampionCategory, MAX_SELECTABLE_CHAMPION_COUNT, NoChampion);
    std::fill_n(shopChampionButton, MAX_SELECTABLE_CHAMPION_COUNT, nullptr);
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        std::fill_n(battleChampion[i], BATTLE_MAP_COLUMNS, nullptr);
    }
    std::fill_n(waitingChampion, WAITING_MAP_COUNT, nullptr);
}

// 析构函数
HumanPlayer::~HumanPlayer()
{
    for (int i = 0; i < WAITING_MAP_COUNT; i++) {
        if (waitingChampion[i] != nullptr) {
            delete waitingChampion[i];
        }
    }
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleChampion[i][j] != nullptr) {
                delete battleChampion[i][j];
            }
        }
    }
}

// 设置当前场景指针
void HumanPlayer::setCurrentScene(cocos2d::Scene* currentScene)
{
    this->currentScene = currentScene;
}

// 刷新商店
void HumanPlayer::refreshShop()
{
    // 检查金币数量
    if (goldCoin < REFRESH_SHOP_PRICE) {
        return;
    }

    // 加载点击音效
    audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

    // 销毁已存在按钮
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        if (shopChampionButton[i] != nullptr) {
            removeChampionFromShop(i);
        }
    }

    // 刷新商店战斗英雄种类
    refreshShopChampionCategory();
    refreshCoinLabel(-REFRESH_SHOP_PRICE);

    // 更新商店战斗英雄按钮
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        // 创建按钮
        shopChampionButton[i] = HoverButton::create(static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("DefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("HoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("ActiveButton.png"));

        // 设置按钮位置
        shopChampionButton[i]->setPosition(Vec2(SHOP_CHAMPION_START_X + i * (SHOP_CHAMPION_INTERVAL + SHOP_CHAMPION_WIDTH), SHOP_CHAMPION_START_Y));

        // 为按钮添加事件处理器
        shopChampionButton[i]->addTouchEventListener([this, i](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                addChampion(i);
            }
            });

        // 将按钮添加到场景中
        currentScene->addChild(shopChampionButton[i]);
    }
}

// 获取战斗区最大英雄数量
int HumanPlayer::getMaxBattleChampionCount() const
{
    return maxBattleChampionCount;
}

// 获取战斗区当前英雄数量
int HumanPlayer::getCurrentBattleChampionCount() const
{
    int count = 0;
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleMap[i][j] != NoChampion) {
                count++;
            }
        }
    }
    return count;
}

// 增加战斗区英雄数量
void HumanPlayer::addBattleChampionCount(const int num)
{
    TalentRune talentRune = static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune"));
    if (maxBattleChampionCount < (talentRune == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1) && goldCoin >= UPLEVEL_PRICE.at(maxBattleChampionCount)) {
        // 加载点击音效
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        refreshCoinLabel(-UPLEVEL_PRICE.at(maxBattleChampionCount));
        maxBattleChampionCount += num;
        auto levelLabel = dynamic_cast<Label*>(currentScene->getChildByName("LevelLabel"));
        if (maxBattleChampionCount >= (talentRune == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1)) {
            levelLabel->setString(u8"最高等级");
        }
        else {
            levelLabel->setString(u8"等级：" + std::to_string(maxBattleChampionCount - BATTLE_AREA_MIN_CHAMPION_COUNT + 1));
        }
    }
}

// 获取金币数量
int HumanPlayer::getGoldCoin() const
{
    return goldCoin;
}

// 增加金币数量
void HumanPlayer::addGoldCoin(const int num)
{
    goldCoin += num;
    if (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune")) == Pirate)
        goldCoin += RUNE_PIRATE_GOLD_COINS_BUFF;
}

// 初始化战斗英雄删除按钮
void HumanPlayer::initializeDeleteChampionButton()
{
    deleteChampionButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/DeleteChampionDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/DeleteChampionHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/DeleteChampionActiveButton.png");
    deleteChampionButton->setPosition(Vec2(BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_X, BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_Y));
    deleteChampionButton->setVisible(false);
    deleteChampionButton->setEnabled(false);
    currentScene->addChild(deleteChampionButton);
}

// 设置战斗区地图
void HumanPlayer::setBattleMap(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS])
{
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            this->battleMap[i][j] = battleMap[i][j];
        }
    }
}

// 添加战斗英雄
void HumanPlayer::addChampion(const int index)
{
    for (int pos = 0; pos < WAITING_MAP_COUNT; pos++) {
        if (waitingMap[pos] == NoChampion) {
            // 检查金币数量
            if (goldCoin < CHAMPION_ATTR_MAP.at(shopChampionCategory[index]).price) {
                return;
            }

            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            // 从商店中移除战斗英雄
            refreshCoinLabel(-CHAMPION_ATTR_MAP.at(shopChampionCategory[index]).price);
            removeChampionFromShop(index);

            // 升级战斗英雄并修改候战区棋盘信息
            if (countSpecificChampion(shopChampionCategory[index]) >= CHAMPION_UPLEVEL_COUNT - 1) {
                ChampionCategory newChampion = static_cast<ChampionCategory>(shopChampionCategory[index] + 1);
                waitingMap[pos] = newChampion;
                uplevelChampion(shopChampionCategory[index]);
                try {
                    waitingChampion[pos] = new Champion(newChampion);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }
            }
            else {
                waitingMap[pos] = shopChampionCategory[index];
                try {
                    waitingChampion[pos] = new Champion(shopChampionCategory[index]);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }
            }

            // 将精灵添加到当前场景
            auto champion = waitingChampion[pos];
            auto championSprite = champion->getSprite();
            championSprite->setPosition(LocationMap::getInstance().getLocationMap().at({ WaitingArea, pos }));
            currentScene->addChild(championSprite, 1);

            // 鼠标事件监听器
            auto mouseListener = cocos2d::EventListenerMouse::create();
            mouseListener->onMouseDown = CC_CALLBACK_1(HumanPlayer::onMouseDown, this, championSprite);
            mouseListener->onMouseMove = CC_CALLBACK_1(HumanPlayer::onMouseMove, this, championSprite);
            mouseListener->onMouseUp = CC_CALLBACK_1(HumanPlayer::onMouseUp, this, championSprite);
            currentScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, championSprite);

            break;
        }
    }
}

// 按下鼠标事件触发函数
void HumanPlayer::onMouseDown(Event* event, Sprite* championSprite)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    Vec2 location = mouseEvent->getLocationInView();
    if (championSprite->getBoundingBox().containsPoint(location) && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        // 标记选中状态
        championSprite->setUserData(reinterpret_cast<void*>(1));
        nearestPlacementMarker = Sprite::create("../Resources/ImageElements/NearestPlacementMarker.png");
        nearestPlacementMarker->setVisible(false);
        currentScene->addChild(nearestPlacementMarker);

        // 确定战斗英雄移动起始位置属性
        for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
            if (pair.second.equals(championSprite->getPosition())) {
                startLocation = pair.first;
                break;
            }
        }

        // 更新地图信息并开启显示战斗英雄属性层和放置标记层
        if (startLocation.status == WaitingArea) {
            ChampionCategory currentChampionCategory = waitingMap[startLocation.position];
            waitingMap[startLocation.position] = NoChampion;
            showChampionAttributesLayerAndPlacementMarkerLayer(currentChampionCategory);
        }
        else {
            ChampionCategory currentChampionCategory = battleMap[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS];
            battleMap[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS] = NoChampion;
            showChampionAttributesLayerAndPlacementMarkerLayer(currentChampionCategory);
        }
    }
}

// 移动鼠标事件触发函数
void HumanPlayer::onMouseMove(Event* event, Sprite* championSprite)
{
    if (championSprite->getUserData() != nullptr) {
        // 遍历所有可放置位置
        nearestPlacementMarker->setPosition(findNearestPoint(championSprite));
        nearestPlacementMarker->setVisible(true);

        // 移动战斗英雄
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 location = mouseEvent->getLocationInView();
        if (location.x >= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LEFT_BOUNDARY
            && location.x <= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_RIGHT_BOUNDARY
            && location.y >= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LOWER_BOUNDARY
            && location.y <= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_UPPER_BOUNDARY) {
            nearestPlacementMarker->setVisible(false);
        }
        championSprite->setPosition(location);
    }
}

// 释放鼠标事件触发函数
void HumanPlayer::onMouseUp(Event* event, Sprite* championSprite)
{
    if (championSprite->getUserData() != nullptr) {
        // 取消选中状态
        championSprite->setUserData(nullptr);
        nearestPlacementMarker->removeFromParent();
        nearestPlacementMarker = nullptr;

        // 删除当前战斗英雄
        bool isDelete = false;
        const Vec2 currentPos = championSprite->getPosition();
        if (currentPos.x >= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LEFT_BOUNDARY
            && currentPos.x <= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_RIGHT_BOUNDARY
            && currentPos.y >= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_LOWER_BOUNDARY
            && currentPos.y <= BATTLE_SCENE_DELETE_CHAMPION_BUTTON_UPPER_BOUNDARY) {
            isDelete = true;
            deleteCurrentChampion();
        }

        if (!isDelete) {
            // 遍历所有可放置位置
            Vec2 nearestPoint = findNearestPoint(championSprite);

            // 确定战斗英雄移动目标位置属性
            Location targetLocation;
            for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                if (pair.second.equals(nearestPoint)) {
                    targetLocation = pair.first;
                    break;
                }
            }

            // 更新地图信息
            Champion* currentChampion;
            if (startLocation.status == WaitingArea) {
                currentChampion = waitingChampion[startLocation.position];
                waitingChampion[startLocation.position] = nullptr;
            }
            else {
                currentChampion = battleChampion[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS];
                battleChampion[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS] = nullptr;
            }
            if (targetLocation.status == WaitingArea) {
                waitingChampion[targetLocation.position] = currentChampion;
                waitingMap[targetLocation.position] = currentChampion->getAttributes().championCategory;
            }
            else {
                battleChampion[targetLocation.position / BATTLE_MAP_COLUMNS][targetLocation.position % BATTLE_MAP_COLUMNS] = currentChampion;
                battleMap[targetLocation.position / BATTLE_MAP_COLUMNS][targetLocation.position % BATTLE_MAP_COLUMNS] = currentChampion->getAttributes().championCategory;
            }

            // 移动战斗英雄
            championSprite->setPosition(nearestPoint);
        }

        // 关闭显示战斗英雄属性层和放置标记层
        hideChampionAttributesLayerAndPlacementMarkerLayer();
    }
}

// 从商店中移除战斗英雄
void HumanPlayer::removeChampionFromShop(const int index)
{
    shopChampionButton[index]->setEnabled(false);
    currentScene->removeChild(shopChampionButton[index]);
    shopChampionButton[index] = nullptr;
}

// 开启显示战斗英雄属性层和放置标记层
void HumanPlayer::showChampionAttributesLayerAndPlacementMarkerLayer(const ChampionCategory championCategory)
{
    if (championAttributesLayer == nullptr) {
        // 创建战斗英雄属性层
        championAttributesLayer = ChampionAttributesLayer::create();
        championAttributesLayer->showAttributes(championCategory);
        currentScene->addChild(championAttributesLayer);

        // 创建放置标记层
        placementMarkerLayer = PlacementMarkerLayer::create();
        placementMarkerLayer->showPlacementMarker(battleMap, waitingMap);
        currentScene->addChild(placementMarkerLayer);

        // 开启战斗英雄删除按钮
        deleteChampionButton->setEnabled(true);
        deleteChampionButton->setVisible(true);
    }
}

// 关闭显示战斗英雄属性层和放置标记层
void HumanPlayer::hideChampionAttributesLayerAndPlacementMarkerLayer()
{
    currentScene->removeChild(championAttributesLayer);
    championAttributesLayer = nullptr;
    currentScene->removeChild(placementMarkerLayer);
    placementMarkerLayer = nullptr;
    deleteChampionButton->setVisible(false);
    deleteChampionButton->setEnabled(false);
}

// 删除当前战斗英雄
void HumanPlayer::deleteCurrentChampion()
{
    if (startLocation.status == WaitingArea) {
        refreshCoinLabel(CHAMPION_ATTR_MAP.at(waitingChampion[startLocation.position]->getAttributes().championCategory).price);
        waitingChampion[startLocation.position]->getSprite()->removeFromParent();
        waitingChampion[startLocation.position] = nullptr;
    }
    else {
        refreshCoinLabel(CHAMPION_ATTR_MAP.at(battleChampion[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS]->getAttributes().championCategory).price);
        battleChampion[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS]->getSprite()->removeFromParent();
        battleChampion[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS] = nullptr;
    }
}

// 刷新金币数量标签
void HumanPlayer::refreshCoinLabel(int num)
{
    goldCoin += num;
    auto coinLabel = dynamic_cast<Label*>(currentScene->getChildByName("CoinLabel"));
    coinLabel->setString(std::to_string(goldCoin));
}

// 统计特定种类战斗英雄的数量
int HumanPlayer::countSpecificChampion(const ChampionCategory championCategory)
{
    int count = 0;
    for (int i = 0; i < WAITING_MAP_COUNT; i++) {
        if (waitingMap[i] == championCategory) {
            count++;
        }
    }
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleMap[i][j] == championCategory) {
                count++;
            }
        }
    }
    return count;
}

// 升级战斗英雄
void HumanPlayer::uplevelChampion(const ChampionCategory championCategory)
{
    for (int i = 0; i < WAITING_MAP_COUNT; i++) {
        if (waitingMap[i] == championCategory) {
            waitingMap[i] = NoChampion;
            waitingChampion[i]->getSprite()->removeFromParent();
            waitingChampion[i] = nullptr;
        }
    }
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleMap[i][j] == championCategory) {
                battleMap[i][j] = NoChampion;
                battleChampion[i][j]->getSprite()->removeFromParent();
                battleChampion[i][j] = nullptr;
            }
        }
    }
}

// 寻找最近可放置坐标
Vec2 HumanPlayer::findNearestPoint(Sprite* championSprite)
{
    float minDistance = FLT_MAX;
    Vec2 nearestPoint;
    if (getCurrentBattleChampionCount() < maxBattleChampionCount) { // 未达到战斗区最大英雄数量
        const Vec2 currentPos = championSprite->getPosition();
        for (const auto& entry : LocationMap::getInstance().getLocationMap()) {
            const Location currentLocation = entry.first;
            bool isEmpty = true;
            if (currentLocation.status == WaitingArea) {
                if (waitingMap[currentLocation.position] != NoChampion) {
                    isEmpty = false;
                }
            }
            else {
                if (currentLocation.position / BATTLE_MAP_COLUMNS >= PLACE_MAP_ROWS
                    || battleMap[currentLocation.position / BATTLE_MAP_COLUMNS][currentLocation.position % BATTLE_MAP_COLUMNS] != NoChampion) {
                    isEmpty = false;
                }
            }
            if (isEmpty) {
                const cocos2d::Vec2& point = entry.second;
                float distance = currentPos.distance(point);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPoint = point;
                }
            }
        }
    }
    else { // 已达到战斗区最大英雄数量
        Vec2 currentPos = championSprite->getPosition();
        for (const auto& entry : LocationMap::getInstance().getLocationMap()) {
            Location currentLocation = entry.first;
            bool isEmpty = false;
            if (currentLocation.status == WaitingArea && waitingMap[currentLocation.position] == NoChampion) {
                isEmpty = true;
            }
            if (isEmpty) {
                const cocos2d::Vec2& point = entry.second;
                float distance = currentPos.distance(point);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestPoint = point;
                }
            }
        }
    }
    return nearestPoint;
}

// 刷新商店战斗英雄种类
void HumanPlayer::refreshShopChampionCategory()
{
    champions = countChampionCategories();
    BattleStage currentStage = evaluateStage(getStageScore());
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        shopChampionCategory[i] = selectRandomChampion(currentStage);
    }
}
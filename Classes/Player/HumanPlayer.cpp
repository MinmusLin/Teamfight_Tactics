/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.cpp
 * File Function: HumanPlayer类的实现
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#include <iostream>
#include <algorithm>
#include "HumanPlayer.h"
#include "LocationMap/LocationMap.h"
#include "GBKToUTF8/GBKToUTF8.h"

USING_NS_CC;

// 构造函数
HumanPlayer::HumanPlayer(std::string nickname) : 
    Player(nickname),
    maxBattleChampionCount(BATTLE_AREA_MIN_CHAMPION_COUNT),
    goldCoin(INITIAL_GOLD_COIN)
{
    std::fill_n(shopChampionCategory, MAX_SELECTABLE_CHAMPION_COUNT, NoChampion);
    std::fill_n(shopChampionButton, MAX_SELECTABLE_CHAMPION_COUNT, nullptr);
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        std::fill_n(battleChampion[i], BATTLE_MAP_COLUMNS, nullptr);
    }
    std::fill_n(waitingChampion, WAITING_MAP_COUNT, nullptr);
    attributesLayer = ChampionAttributesLayer::create();
    attributesLayer->retain(); // 增加引用计数，防止被自动释放
}

// 析构函数
HumanPlayer::~HumanPlayer()
{
    for (int i = 0; i < WAITING_MAP_COUNT; i++) {
        if (waitingChampion[i] != nullptr) {
            delete waitingChampion[i];
        }
    }
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleChampion[i][j] != nullptr) {
                delete battleChampion[i][j];
            }
        }
    }
    if (attributesLayer) {
        attributesLayer->release(); // 减少引用计数
        attributesLayer = nullptr; // 清除指针，避免悬挂指针
    }
}

// 刷新商店
void HumanPlayer::refreshShop(Scene* currentScene)
{
    // 销毁已存在按钮
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; ++i) {
        if (shopChampionButton[i] != nullptr) {
            removeChampionFromShop(i, currentScene);
        }
    }

    // 刷新商店战斗英雄种类
    refreshShopChampionCategory();

    // 更新金币数量
    goldCoin -= REFRESH_SHOP_PRICE;
    auto coinLabel = dynamic_cast<Label*>(currentScene->getChildByName("CoinLabel"));
    coinLabel->setString(std::to_string(goldCoin));

    // 更新商店战斗英雄按钮
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        // 创建按钮
        shopChampionButton[i] = HoverButton::create(static_cast<std::string>("../Resources/Buttons/ShopButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("DefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/ShopButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("HoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/ShopButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("ActiveButton.png"));

        // 设置按钮位置
        shopChampionButton[i]->setPosition(Vec2(SHOP_CHAMPION_START_X + i * (SHOP_CHAMPION_INTERVAL + SHOP_CHAMPION_WIDTH), SHOP_CHAMPION_START_Y));

        // 为按钮添加事件处理器
        shopChampionButton[i]->addTouchEventListener([this, i, currentScene](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::BEGAN) {
                addChampion(i, currentScene);
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
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleMap[i][j] != NoChampion) {
                count++;
            }
        }
    }
    return count;
}

// 增加战斗区英雄数量
void HumanPlayer::addBattleChampionCount(Scene* currentScene, const int num)
{
    if (maxBattleChampionCount < BATTLE_AREA_MAX_CHAMPION_COUNT) {
        goldCoin -= UPLEVEL_PRICE.at(maxBattleChampionCount);
        auto coinLabel = dynamic_cast<Label*>(currentScene->getChildByName("CoinLabel"));
        coinLabel->setString(std::to_string(goldCoin));
        maxBattleChampionCount += num;
        auto levelLabel = dynamic_cast<Label*>(currentScene->getChildByName("LevelLabel"));
        if (maxBattleChampionCount >= BATTLE_AREA_MAX_CHAMPION_COUNT) {
            levelLabel->setString(GBKToUTF8::getString("最高等级"));
        }
        else {
            levelLabel->setString(GBKToUTF8::getString("等级：") + std::to_string(maxBattleChampionCount - BATTLE_AREA_MIN_CHAMPION_COUNT + 1));
        }
    }
}

// 获取金币数量
int HumanPlayer::getGoldCoin() const
{
    return goldCoin;
}

// 添加战斗英雄
void HumanPlayer::addChampion(const int index, Scene* currentScene)
{
    for (int pos = 0; pos < WAITING_MAP_COUNT; pos++) {
        if (waitingMap[pos] == NoChampion) {
            // 从商店中移除战斗英雄
            removeChampionFromShop(index, currentScene);

            // 修改候战区棋盘信息
            waitingMap[pos] = shopChampionCategory[index];
            try {
                waitingChampion[pos] = new Champion(shopChampionCategory[index]);
            }
            catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                throw;
            }

            // 将精灵添加到当前场景
            auto champion = waitingChampion[pos];
            auto championSprite = champion->getSprite();
            championSprite->setPosition(LocationMap::getInstance().getLocationMap().at({ WaitingArea, pos }));
            currentScene->addChild(championSprite);

            // 鼠标事件监听器
            auto mouseListener = EventListenerMouse::create();
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

        // 确定战斗英雄移动起始位置属性
        for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
            if (pair.second.equals(championSprite->getPosition())) {
                startLocation = pair.first;
                break;
            }
        }

        // 更新地图信息
        if (startLocation.status == WaitingArea) {
            waitingMap[startLocation.position] = NoChampion;
        }
        else {
            battleMap[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS] = NoChampion;
        }

        // 获取英雄指针
        Champion* champion = getChampionByLocation(startLocation);
        if (champion) {
            showAttributesLayer(*champion);
        }
    }
}

// 移动鼠标事件触发函数
void HumanPlayer::onMouseMove(Event* event, Sprite* championSprite)
{
    if (championSprite->getUserData() != nullptr) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 location = mouseEvent->getLocationInView();
        championSprite->setPosition(location);
    }
}

// 释放鼠标事件触发函数
void HumanPlayer::onMouseUp(Event* event, Sprite* championSprite)
{
    if (championSprite->getUserData() != nullptr) {
        // 取消选中状态
        championSprite->setUserData(nullptr);

        // 遍历所有可放置放置
        float minDistance = FLT_MAX;
        Vec2 nearestPoint;
        if (getCurrentBattleChampionCount() < maxBattleChampionCount) { // 未达到战斗区最大英雄数量
            Vec2 currentPos = championSprite->getPosition();
            for (const auto& entry : LocationMap::getInstance().getLocationMap()) {
                Location currentLocation = entry.first;
                bool isEmpty = true;
                if (currentLocation.status == WaitingArea) {
                    if (waitingMap[currentLocation.position] != NoChampion) {
                        isEmpty = false;
                    }
                }
                else {
                    if (battleMap[currentLocation.position / BATTLE_MAP_COLUMNS][currentLocation.position % BATTLE_MAP_COLUMNS] != NoChampion) {
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

        // 隐藏属性图层
        hideAttributesLayer();
    }
}

// 从商店中移除战斗英雄
void HumanPlayer::removeChampionFromShop(const int index, cocos2d::Scene* currentScene)
{
    shopChampionButton[index]->setEnabled(false);
    currentScene->removeChild(shopChampionButton[index]);
    shopChampionButton[index] = nullptr;
}

// 刷新商店战斗英雄种类
void HumanPlayer::refreshShopChampionCategory()
{
    // TODO: 杨兆镇：商店推荐算法
    shopChampionCategory[0] = CHAMPION_ATTR_MAP.at(Champion1).championCategory;
    shopChampionCategory[1] = CHAMPION_ATTR_MAP.at(Champion2).championCategory;
    shopChampionCategory[2] = CHAMPION_ATTR_MAP.at(Champion3).championCategory;
    shopChampionCategory[3] = CHAMPION_ATTR_MAP.at(Champion4).championCategory;
    shopChampionCategory[4] = CHAMPION_ATTR_MAP.at(Champion5).championCategory;
}

// 获取对应英雄指针
Champion* HumanPlayer::getChampionByLocation(const Location& location)
{
    // 检查是否是候战区的位置
    if (location.status == WaitingArea) {
        // 假设候战区的位置和 waitingChampion 数组的索引是对应的
        return waitingChampion[location.position];
    }
    // 检查是否是战斗区的位置
    else if (location.status == BattleArea) {
        // 假设战斗区的位置可以转换为二维数组的行和列索引
        int row = location.position / BATTLE_MAP_COLUMNS;
        int col = location.position % BATTLE_MAP_COLUMNS;
        return battleChampion[row][col];
    }
    // 如果位置不在上述区域，返回 nullptr
    return nullptr;
}

// 显示属性图层
void HumanPlayer::showAttributesLayer(const Champion& champion)
{
    if (!attributesLayer) {
        attributesLayer = ChampionAttributesLayer::create();
        attributesLayer->retain(); // 增加引用计数，防止被自动释放
    }
    // 确保图层已添加到当前场景
    if (attributesLayer->getParent() == nullptr) {
        cocos2d::Scene* currentScene = cocos2d::Director::getInstance()->getRunningScene();
        if (currentScene) {
            currentScene->addChild(attributesLayer);
        }
    }

    if (attributesLayer) {
        attributesLayer->showAttributes(champion);
    }
}

// 隐藏属性图层
void HumanPlayer::hideAttributesLayer()
{
    if (attributesLayer) {
        attributesLayer->hide();
    }
}
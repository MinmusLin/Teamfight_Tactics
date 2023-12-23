/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.cpp
 * File Function: HumanPlayer���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/24
 ****************************************************************/

#include <iostream>
#include <algorithm>
#include "HumanPlayer.h"
#include "LocationMap/LocationMap.h"
#include "GBKToUTF8/GBKToUTF8.h"

USING_NS_CC;

// ���캯��
HumanPlayer::HumanPlayer(const std::string nickname) :
    Player(nickname),
    deleteChampionButton(nullptr),
    championAttributesLayer(nullptr),
    placementMarkerLayer(nullptr),
    maxBattleChampionCount(BATTLE_AREA_MIN_CHAMPION_COUNT),
    goldCoin(INITIAL_GOLD_COIN)
{
    std::fill_n(shopChampionCategory, MAX_SELECTABLE_CHAMPION_COUNT, NoChampion);
    std::fill_n(shopChampionButton, MAX_SELECTABLE_CHAMPION_COUNT, nullptr);
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        std::fill_n(battleChampion[i], BATTLE_MAP_COLUMNS, nullptr);
    }
    std::fill_n(waitingChampion, WAITING_MAP_COUNT, nullptr);
}

// ��������
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
}

// ˢ���̵�
void HumanPlayer::refreshShop(Scene* currentScene)
{
    // �����Ѵ��ڰ�ť
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; ++i) {
        if (shopChampionButton[i] != nullptr) {
            removeChampionFromShop(i, currentScene);
        }
    }

    // ˢ���̵�ս��Ӣ������
    refreshShopChampionCategory();

    // ���½������
    goldCoin -= REFRESH_SHOP_PRICE;
    auto coinLabel = dynamic_cast<Label*>(currentScene->getChildByName("CoinLabel"));
    coinLabel->setString(std::to_string(goldCoin));

    // �����̵�ս��Ӣ�۰�ť
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        // ������ť
        shopChampionButton[i] = HoverButton::create(static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("DefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("HoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("ActiveButton.png"));

        // ���ð�ťλ��
        shopChampionButton[i]->setPosition(Vec2(SHOP_CHAMPION_START_X + i * (SHOP_CHAMPION_INTERVAL + SHOP_CHAMPION_WIDTH), SHOP_CHAMPION_START_Y));

        // Ϊ��ť����¼�������
        shopChampionButton[i]->addTouchEventListener([this, i, currentScene](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::BEGAN) {
                addChampion(i, currentScene);
            }
            });

        // ����ť��ӵ�������
        currentScene->addChild(shopChampionButton[i]);
    }
}

// ��ȡս�������Ӣ������
int HumanPlayer::getMaxBattleChampionCount() const
{
    return maxBattleChampionCount;
}

// ��ȡս������ǰӢ������
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

// ����ս����Ӣ������
void HumanPlayer::addBattleChampionCount(Scene* currentScene, const int num)
{
    if (maxBattleChampionCount < BATTLE_AREA_MAX_CHAMPION_COUNT) {
        goldCoin -= UPLEVEL_PRICE.at(maxBattleChampionCount);
        auto coinLabel = dynamic_cast<Label*>(currentScene->getChildByName("CoinLabel"));
        coinLabel->setString(std::to_string(goldCoin));
        maxBattleChampionCount += num;
        auto levelLabel = dynamic_cast<Label*>(currentScene->getChildByName("LevelLabel"));
        if (maxBattleChampionCount >= BATTLE_AREA_MAX_CHAMPION_COUNT) {
            levelLabel->setString(GBKToUTF8::getString("��ߵȼ�"));
        }
        else {
            levelLabel->setString(GBKToUTF8::getString("�ȼ���") + std::to_string(maxBattleChampionCount - BATTLE_AREA_MIN_CHAMPION_COUNT + 1));
        }
    }
}

// ��ȡ�������
int HumanPlayer::getGoldCoin() const
{
    return goldCoin;
}

// ��ʼ��ս��Ӣ��ɾ����ť
void HumanPlayer::initializeDeleteChampionButton(Scene* currentScene)
{
    deleteChampionButton = HoverButton::create("../Resources/Buttons/OfflineModePreparationSceneButtons/DeleteChampionDefaultButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/DeleteChampionHoverButton.png",
        "../Resources/Buttons/OfflineModePreparationSceneButtons/DeleteChampionActiveButton.png");
    deleteChampionButton->setPosition(Vec2(BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_X, BATTLE_SCENE_DELETE_CHAMPION_BUTTON_START_Y));
    deleteChampionButton->setVisible(false);
    deleteChampionButton->setEnabled(false);
    currentScene->addChild(deleteChampionButton);
}

// ���ս��Ӣ��
void HumanPlayer::addChampion(const int index, Scene* currentScene)
{
    for (int pos = 0; pos < WAITING_MAP_COUNT; pos++) {
        if (waitingMap[pos] == NoChampion) {
            // ���̵����Ƴ�ս��Ӣ��
            removeChampionFromShop(index, currentScene);

            // �޸ĺ�ս��������Ϣ
            waitingMap[pos] = shopChampionCategory[index];
            try {
                waitingChampion[pos] = new Champion(shopChampionCategory[index]);
            }
            catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                throw;
            }

            // ��������ӵ���ǰ����
            auto champion = waitingChampion[pos];
            auto championSprite = champion->getSprite();
            championSprite->setPosition(LocationMap::getInstance().getLocationMap().at({ WaitingArea, pos }));
            currentScene->addChild(championSprite);

            // ����¼�������
            auto mouseListener = EventListenerMouse::create();
            mouseListener->onMouseDown = CC_CALLBACK_1(HumanPlayer::onMouseDown, this, championSprite);
            mouseListener->onMouseMove = CC_CALLBACK_1(HumanPlayer::onMouseMove, this, championSprite);
            mouseListener->onMouseUp = CC_CALLBACK_1(HumanPlayer::onMouseUp, this, championSprite);
            currentScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, championSprite);

            break;
        }
    }
}

// ��������¼���������
void HumanPlayer::onMouseDown(Event* event, Sprite* championSprite)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    Vec2 location = mouseEvent->getLocationInView();
    if (championSprite->getBoundingBox().containsPoint(location) && mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        // ���ѡ��״̬
        championSprite->setUserData(reinterpret_cast<void*>(1));

        // ȷ��ս��Ӣ���ƶ���ʼλ������
        for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
            if (pair.second.equals(championSprite->getPosition())) {
                startLocation = pair.first;
                break;
            }
        }

        // ���µ�ͼ��Ϣ��������ʾս��Ӣ�����Բ�ͷ��ñ�ǲ�
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

// �ƶ�����¼���������
void HumanPlayer::onMouseMove(Event* event, Sprite* championSprite)
{
    if (championSprite->getUserData() != nullptr) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Vec2 location = mouseEvent->getLocationInView();
        championSprite->setPosition(location);
    }
}

// �ͷ�����¼���������
void HumanPlayer::onMouseUp(Event* event, Sprite* championSprite)
{
    if (championSprite->getUserData() != nullptr) {
        // ȡ��ѡ��״̬
        championSprite->setUserData(nullptr);

        // ɾ����ǰս��Ӣ��
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
            // �������пɷ��÷���
            float minDistance = FLT_MAX;
            Vec2 nearestPoint;
            if (getCurrentBattleChampionCount() < maxBattleChampionCount) { // δ�ﵽս�������Ӣ������
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
                        if (currentLocation.position / BATTLE_MAP_COLUMNS >= PLACE_MAP_ROWS) {
                            isEmpty = false;
                        }
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
            else { // �Ѵﵽս�������Ӣ������
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

            // ȷ��ս��Ӣ���ƶ�Ŀ��λ������
            Location targetLocation;
            for (const auto& pair : LocationMap::getInstance().getLocationMap()) {
                if (pair.second.equals(nearestPoint)) {
                    targetLocation = pair.first;
                    break;
                }
            }

            // ���µ�ͼ��Ϣ
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

            // �ƶ�ս��Ӣ��
            championSprite->setPosition(nearestPoint);
        }
        
        // �ر���ʾս��Ӣ�����Բ�ͷ��ñ�ǲ�
        hideChampionAttributesLayerAndPlacementMarkerLayer();
    }
}

// ���̵����Ƴ�ս��Ӣ��
void HumanPlayer::removeChampionFromShop(const int index, cocos2d::Scene* currentScene)
{
    shopChampionButton[index]->setEnabled(false);
    currentScene->removeChild(shopChampionButton[index]);
    shopChampionButton[index] = nullptr;
}

// ������ʾս��Ӣ�����Բ�ͷ��ñ�ǲ�
void HumanPlayer::showChampionAttributesLayerAndPlacementMarkerLayer(const ChampionCategory championCategory)
{
    if (championAttributesLayer == nullptr) {
        // ��ȡ��ǰ�������г���
        auto currentScene = Director::getInstance()->getRunningScene();

        // ����ս��Ӣ�����Բ�
        championAttributesLayer = ChampionAttributesLayer::create();
        championAttributesLayer->showAttributes(championCategory);
        currentScene->addChild(championAttributesLayer);

        // �������ñ�ǲ�
        placementMarkerLayer = PlacementMarkerLayer::create();
        placementMarkerLayer->showPlacementMarker(battleMap, waitingMap);
        currentScene->addChild(placementMarkerLayer);

        // ����ս��Ӣ��ɾ����ť
        deleteChampionButton->setEnabled(true);
        deleteChampionButton->setVisible(true);
    }
}

// �ر���ʾս��Ӣ�����Բ�ͷ��ñ�ǲ�
void HumanPlayer::hideChampionAttributesLayerAndPlacementMarkerLayer()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    currentScene->removeChild(championAttributesLayer);
    championAttributesLayer = nullptr;
    currentScene->removeChild(placementMarkerLayer);
    placementMarkerLayer = nullptr;
    deleteChampionButton->setVisible(false);
    deleteChampionButton->setEnabled(false);
}

// ɾ����ǰս��Ӣ��
void HumanPlayer::deleteCurrentChampion()
{
    if (startLocation.status == WaitingArea) {
        waitingChampion[startLocation.position]->getSprite()->removeFromParent();
        waitingChampion[startLocation.position] = nullptr;
    }
    else {
        battleChampion[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS]->getSprite()->removeFromParent();
        battleChampion[startLocation.position / BATTLE_MAP_COLUMNS][startLocation.position % BATTLE_MAP_COLUMNS] = nullptr;
    }
}

// ˢ���̵�ս��Ӣ������
void HumanPlayer::refreshShopChampionCategory()
{
    // TODO: �������̵��Ƽ��㷨
    shopChampionCategory[0] = CHAMPION_ATTR_MAP.at(Champion1).championCategory;
    shopChampionCategory[1] = CHAMPION_ATTR_MAP.at(Champion3).championCategory;
    shopChampionCategory[2] = CHAMPION_ATTR_MAP.at(Champion5).championCategory;
    shopChampionCategory[3] = CHAMPION_ATTR_MAP.at(Champion7).championCategory;
    shopChampionCategory[4] = CHAMPION_ATTR_MAP.at(Champion9).championCategory;
}
/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.cpp
 * File Function: HumanPlayer���ʵ��
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include <algorithm>
#include "HumanPlayer.h"
#include "LocationMap/LocationMap.h"
#include "proj.win32/AudioPlayer.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Event;
using cocos2d::EventMouse;
using cocos2d::Vec2;

// ���캯��
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

// ��������
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

// ���õ�ǰ����ָ��
void HumanPlayer::setCurrentScene(cocos2d::Scene* currentScene)
{
    this->currentScene = currentScene;
}

// ˢ���̵�
void HumanPlayer::refreshShop()
{
    // ���������
    if (goldCoin < REFRESH_SHOP_PRICE) {
        return;
    }

    // ���ص����Ч
    audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

    // �����Ѵ��ڰ�ť
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        if (shopChampionButton[i] != nullptr) {
            removeChampionFromShop(i);
        }
    }

    // ˢ���̵�ս��Ӣ������
    refreshShopChampionCategory();
    refreshCoinLabel(-REFRESH_SHOP_PRICE);

    // �����̵�ս��Ӣ�۰�ť
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        // ������ť
        shopChampionButton[i] = HoverButton::create(static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("DefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("HoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModePreparationSceneButtons/Champion") + std::to_string(shopChampionCategory[i]) + static_cast<std::string>("ActiveButton.png"));

        // ���ð�ťλ��
        shopChampionButton[i]->setPosition(Vec2(SHOP_CHAMPION_START_X + i * (SHOP_CHAMPION_INTERVAL + SHOP_CHAMPION_WIDTH), SHOP_CHAMPION_START_Y));

        // Ϊ��ť����¼�������
        shopChampionButton[i]->addTouchEventListener([this, i](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                addChampion(i);
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
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battleMap[i][j] != NoChampion) {
                count++;
            }
        }
    }
    return count;
}

// ����ս����Ӣ������
void HumanPlayer::addBattleChampionCount(const int num)
{
    TalentRune talentRune = static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune"));
    if (maxBattleChampionCount < (talentRune == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1) && goldCoin >= UPLEVEL_PRICE.at(maxBattleChampionCount)) {
        // ���ص����Ч
        audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

        refreshCoinLabel(-UPLEVEL_PRICE.at(maxBattleChampionCount));
        maxBattleChampionCount += num;
        auto levelLabel = dynamic_cast<Label*>(currentScene->getChildByName("LevelLabel"));
        if (maxBattleChampionCount >= (talentRune == General ? BATTLE_AREA_MAX_CHAMPION_COUNT : BATTLE_AREA_MAX_CHAMPION_COUNT - 1)) {
            levelLabel->setString(u8"��ߵȼ�");
        }
        else {
            levelLabel->setString(u8"�ȼ���" + std::to_string(maxBattleChampionCount - BATTLE_AREA_MIN_CHAMPION_COUNT + 1));
        }
    }
}

// ��ȡ�������
int HumanPlayer::getGoldCoin() const
{
    return goldCoin;
}

// ���ӽ������
void HumanPlayer::addGoldCoin(const int num)
{
    goldCoin += num;
    if (static_cast<TalentRune>(cocos2d::UserDefault::getInstance()->getIntegerForKey("TalentRune")) == Pirate)
        goldCoin += RUNE_PIRATE_GOLD_COINS_BUFF;
}

// ��ʼ��ս��Ӣ��ɾ����ť
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

// ����ս������ͼ
void HumanPlayer::setBattleMap(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS])
{
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            this->battleMap[i][j] = battleMap[i][j];
        }
    }
}

// ���ս��Ӣ��
void HumanPlayer::addChampion(const int index)
{
    for (int pos = 0; pos < WAITING_MAP_COUNT; pos++) {
        if (waitingMap[pos] == NoChampion) {
            // ���������
            if (goldCoin < CHAMPION_ATTR_MAP.at(shopChampionCategory[index]).price) {
                return;
            }

            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            // ���̵����Ƴ�ս��Ӣ��
            refreshCoinLabel(-CHAMPION_ATTR_MAP.at(shopChampionCategory[index]).price);
            removeChampionFromShop(index);

            // ����ս��Ӣ�۲��޸ĺ�ս��������Ϣ
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

            // ��������ӵ���ǰ����
            auto champion = waitingChampion[pos];
            auto championSprite = champion->getSprite();
            championSprite->setPosition(LocationMap::getInstance().getLocationMap().at({ WaitingArea, pos }));
            currentScene->addChild(championSprite, 1);

            // ����¼�������
            auto mouseListener = cocos2d::EventListenerMouse::create();
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
        nearestPlacementMarker = Sprite::create("../Resources/ImageElements/NearestPlacementMarker.png");
        nearestPlacementMarker->setVisible(false);
        currentScene->addChild(nearestPlacementMarker);

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
        // �������пɷ���λ��
        nearestPlacementMarker->setPosition(findNearestPoint(championSprite));
        nearestPlacementMarker->setVisible(true);

        // �ƶ�ս��Ӣ��
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

// �ͷ�����¼���������
void HumanPlayer::onMouseUp(Event* event, Sprite* championSprite)
{
    if (championSprite->getUserData() != nullptr) {
        // ȡ��ѡ��״̬
        championSprite->setUserData(nullptr);
        nearestPlacementMarker->removeFromParent();
        nearestPlacementMarker = nullptr;

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
            // �������пɷ���λ��
            Vec2 nearestPoint = findNearestPoint(championSprite);

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
void HumanPlayer::removeChampionFromShop(const int index)
{
    shopChampionButton[index]->setEnabled(false);
    currentScene->removeChild(shopChampionButton[index]);
    shopChampionButton[index] = nullptr;
}

// ������ʾս��Ӣ�����Բ�ͷ��ñ�ǲ�
void HumanPlayer::showChampionAttributesLayerAndPlacementMarkerLayer(const ChampionCategory championCategory)
{
    if (championAttributesLayer == nullptr) {
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

// ˢ�½��������ǩ
void HumanPlayer::refreshCoinLabel(int num)
{
    goldCoin += num;
    auto coinLabel = dynamic_cast<Label*>(currentScene->getChildByName("CoinLabel"));
    coinLabel->setString(std::to_string(goldCoin));
}

// ͳ���ض�����ս��Ӣ�۵�����
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

// ����ս��Ӣ��
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

// Ѱ������ɷ�������
Vec2 HumanPlayer::findNearestPoint(Sprite* championSprite)
{
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
    return nearestPoint;
}

// ˢ���̵�ս��Ӣ������
void HumanPlayer::refreshShopChampionCategory()
{
    champions = countChampionCategories();
    BattleStage currentStage = evaluateStage(getStageScore());
    for (int i = 0; i < MAX_SELECTABLE_CHAMPION_COUNT; i++) {
        shopChampionCategory[i] = selectRandomChampion(currentStage);
    }
}
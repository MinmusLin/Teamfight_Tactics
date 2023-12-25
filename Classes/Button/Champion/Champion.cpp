/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.cpp
 * File Function: Champion类的实现
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#include "Champion.h"
#include "LocationMap/LocationMap.h"
#include "cocos2d.h"
#include "Battle/Battle.h"

 // 构造函数
Champion::Champion(const ChampionCategory championCategory) :
    attributes(CHAMPION_ATTR_MAP.at(championCategory))
{
    sprite = Sprite::create(attributes.championImagePath);
    currentEnemy = nullptr;
    currentBattle = nullptr;
    attackIntervalTimer = 0;
    isMoving = false;
    currentMove = nullptr;
    moveIntervalTimer = 0;
    currentDestination = { 0,0 };
    maxHealthPoints = attributes.healthPoints;
    maxMagicPoints = attributes.magicPoints;

}

// 获取精灵类指针
cocos2d::Sprite* Champion::getSprite() const
{
    return sprite;
}

// 获取战斗英雄属性
ChampionAttributes Champion::getAttributes() const
{
    return attributes;
}

// 设置英雄所属阵营
void Champion::setCamp(bool isMyChampion)
{
    isMy = isMyChampion;
}

// 设置英雄所属阵营
bool Champion::getCamp() const
{
    return isMy;
}

//计算两点距离
float Champion::distanceBetweenPoints(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2) {
    const float dx = p2.x - p1.x;
    const float dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// 获取最近的地方英雄
void Champion::findNearestEnemy()
{
    Champion* nearestEnemy = nullptr;
    float nearestDistance = std::numeric_limits<float>::max(); // 设置一个最大距离初始值

    // 遍历地图或场景中的敌方英雄
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (currentBattle->getChampion(i, j) != nullptr) {
                if (currentBattle->getChampion(i, j)->isMy != isMy) { // 假设 ENEMY 是敌方英雄的标识
                    float distance = distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * 9 + j }),
                        LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * 9 + currentLocation.y }));

                    // 如果距离比当前最近的距离小，则更新最近敌人和最近距离
                    if (distance < nearestDistance) {
                        nearestDistance = distance;
                        nearestEnemy = currentBattle->getChampion(i, j);
                    }

                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
    }
    currentEnemy = nearestEnemy;
    return;
}

// 判断攻击范围内是否有敌人
bool Champion::isInAttackRange()
{
    if (currentEnemy == nullptr)
        return false;
    float Distance = distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, currentEnemy->currentLocation.x * 9 + currentEnemy->currentLocation.y }),
        LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * 9 + currentLocation.y }));
    if (Distance <= attributes.attackRange * CHAMPION_HORIZONTAL_INTERVAL) {
        return true;
    }
    else {
        return false;
    }

}

// 移动
BattleLocation Champion::moveTowards(Champion* nearestEnemy)
{
    // 如果最近的敌人为空，无法移动，返回当前位置
    if (nearestEnemy == nullptr)
        return currentLocation;

    // 获取最近敌人的位置
    BattleLocation enemyLocation = nearestEnemy->currentLocation;
    BattleLocation bestMove = currentLocation;
    if (nearestEnemy->currentLocation.x > currentLocation.x) {
        if (nearestEnemy->currentLocation.y <= currentLocation.y) {
            if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左上角走
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//往左走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右上角走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左下走
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//往右走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右下走
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右上角走
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左上角走
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//往右走
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//往左走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右下走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左下走
            else {
                return currentLocation;
            }
            return bestMove;
        }
    }
    else if (nearestEnemy->currentLocation.x == currentLocation.x) {
        if (nearestEnemy->currentLocation.y < currentLocation.y) {
            if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//往左走
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左上走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左下走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往下上走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右上走
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//往右走
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//往右走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右上角走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右下走
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左上角走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左下走
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//往左走
            else {
                return currentLocation;
            }
            return bestMove;
        }
    }
    else {
        if (nearestEnemy->currentLocation.y <= currentLocation.y) {
            if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左下走
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//往左走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右下走
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//往右走
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左上角走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右上角走
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右下走
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//往右走
            else  if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左下走
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//往左走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//往右上角走
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//往左上角走
            else {
                return currentLocation;
            }
            return bestMove;
        }
    }
}

// 攻击
void Champion::attack()
{
    if (isInAttackRange()) {
        if (currentEnemy) {
            // 在攻击范围内，执行攻击操作
            currentEnemy->beingAttack(attributes.attackDamage);
            attributes.magicPoints += 20;
        }
    }
}

// 受到攻击
void Champion::beingAttack(const int& damage)
{
    attributes.healthPoints -= damage / attributes.defenseCoefficient;
    attributes.magicPoints += 20;
}

// 死亡退出
void Champion::Die()
{
    auto championSprite = getSprite();
    championSprite->getParent()->removeChild(sprite, true);
    Champion* temp = currentBattle->getChampion(currentLocation.x, currentLocation.y);
    currentBattle->championMap[currentLocation.x][currentLocation.y] = nullptr;
    delete temp;
    return;
}

// 死亡退出
void Champion::skill()
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (currentBattle->getChampion(i, j) != nullptr) {
                // 在射程+1范围内所有英雄全部受到一次攻击
                if (currentBattle->getChampion(i, j)->isMy != isMy && distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * 9 + j }),
                    LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * 9 + currentLocation.y }))<= attributes.attackRange * CHAMPION_HORIZONTAL_INTERVAL+1) { // 假设 ENEMY 是敌方英雄的标识
                    currentBattle->getChampion(i, j)->beingAttack(attributes.attackDamage);
                }
                else {
                    continue;
                }
            }
            else {
                continue;
            }
        }
    }
}

// 判断是否在场内
bool Champion::isInMap(const int& x, const int& y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 9;
}

// 设置当前英雄位置
void Champion::setCurrentPosition(const int& x, const int& y)
{
    currentLocation.x = x;
    currentLocation.y = y;
}

// 绑定战斗
void Champion::setBattle(Battle* myBattle)
{
    currentBattle = myBattle;
}

// 设置英雄移动状态
bool Champion::getIsMoving() const
{
    return isMoving;
}

// 设置英雄移动状态
Champion* Champion::getCurrentEnemy() const
{
    return currentEnemy;
}

// 获取移动时间计时
float Champion::getMoveIntervalTimer() const
{
    return moveIntervalTimer;
}

// 增加移动时间间隔
void Champion::addMoveIntervalTimer(float delta)
{
    moveIntervalTimer += delta;
}

// 重置移动时间间隔
void Champion::resetMoveIntervalTimer()
{
    moveIntervalTimer = 0;
}

// 获取攻击时间间隔
float Champion::getAttackIntervalTimer() const
{
    return attackIntervalTimer;
}

// 增加攻击时间
void Champion::addAttackIntervalTimer(float delta)
{
    attackIntervalTimer += delta;
}

// 重置攻击时间间隔
void Champion::resetAttackIntervalTimer()
{
    attackIntervalTimer = 0.0f;
}

// 获取当前移动
cocos2d::MoveTo* Champion::getCurrentMove() const
{
    return currentMove;
}

// 获取当前战斗
Battle* Champion::getCurrentBattle() const
{
    return currentBattle;
}

// 获取英雄移动状态
void Champion::setIsMoving()
{
    isMoving = true;
}

// 获取英雄移动状态
void Champion::resetIsMoving()
{
    isMoving = false;
}

// 设置当前移动
void Champion::setCurrentMove(cocos2d::MoveTo* move)
{
    currentMove = move;
}

// 重置当前移动
void Champion::resetCurrentMove()
{
    currentMove = nullptr;
}

// 获取当前敌人
BattleLocation Champion::getCurrentLocation() const
{
    return currentLocation;
}

// 获取攻击时间间隔
BattleLocation Champion::getCurrentDestination() const
{
    return currentDestination;
}

// 增加攻击时间间隔
void Champion::setCurrentDestination(BattleLocation destination)
{
    currentDestination = destination;
}

// 重置攻击时间间隔
void Champion::resetCurrentDestination()
{
    currentDestination = { currentLocation.x,currentLocation.y };
}

// 获取英雄移动状态
bool Champion::getIsAttacking() const
{
    return isAttaking;
}

// 获取英雄移动状态
void Champion::setIsAttacking()
{
    isAttaking = true;
}

// 获取英雄移动状态
void Champion::resetIsAttacking()
{
    isAttaking = false;
}

// 在 Champion 类中创建并添加血条和蓝条
void Champion::initHealthBar() {
    // 创建血条和蓝条的 Sprite 或 Label
    auto healthBar = Sprite::create("health_bar.png");
    auto manaBar = Sprite::create("mana_bar.png");

    // 设置血条和蓝条的位置，相对于英雄
    healthBar->setPosition(cocos2d::Vec2(0, 50)); // 假设血条在英雄头顶上方
    manaBar->setPosition(cocos2d::Vec2(0, 40));   // 假设蓝条在血条下方

    // 将血条和蓝条添加为英雄的子节点
    this->addChild(healthBar);
    this->addChild(manaBar);

    // 将血条和蓝条设为私有成员，方便后续更新显示
    this->healthBar = healthBar;
    this->manaBar = manaBar;
}

// 更新血条和蓝条的位置
void Champion::updateHealthBarPosition() {
    // 根据英雄的位置调整血条和蓝条的位置，使其固定在头顶
    cocos2d::Vec2 heroPosition = this->getPosition();
    this->healthBar->setPosition(cocos2d::Vec2(heroPosition.x, heroPosition.y + 50));
    this->manaBar->setPosition(cocos2d::Vec2(heroPosition.x, heroPosition.y + 40));
}

// 更新血条和蓝条的显示
void Champion::updateHealthBarDisplay() {
    // 根据英雄当前的血量和蓝量更新血条和蓝条的显示
    float currentHealth = attributes.healthPoints; // 获取英雄当前血量
    float currentMana = attributes.magicPoints;     // 获取英雄当前蓝量

    // 根据当前血量和蓝量设置血条和蓝条的显示比例或其他显示方式
    this->healthBar->setScaleX(currentHealth / maxHealthPoints); // 假设血条的 scaleX 代表血量比例
    this->manaBar->setScaleX(currentMana / maxMagicPoints);       // 假设蓝条的 scaleX 代表蓝量比例
}
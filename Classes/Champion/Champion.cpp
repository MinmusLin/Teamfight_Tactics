/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.cpp
 * File Function: Champion类的实现
 * Author:        杨宇琨、刘淑仪、林继申
 * Update Date:   2023/12/27
 ****************************************************************/

#include "Champion.h"
#include "LocationMap/LocationMap.h"

// 构造函数
Champion::Champion(const ChampionCategory championCategory) :
    currentBattle(nullptr),
    attributes(CHAMPION_ATTR_MAP.at(championCategory)),
    currentLocation({0, 0}),
    currentDestination({ 0, 0 }),
    currentEnemy(nullptr),
    sword(nullptr),
    currentMove(nullptr),
    isMyFlag(false),
    isMoving(false),
    isAttaking(false),
    attackIntervalTimer(0.0f),
    moveIntervalTimer(0.0f)
{
    sprite = Sprite::create(attributes.championImagePath);
    maxHealthPoints = attributes.healthPoints;
    maxMagicPoints = attributes.skillTriggerThreshold;
}

// 绑定战斗类
void Champion::setBattle(Battle* myBattle)
{
    currentBattle = myBattle;
}

// 设置战斗英雄所属阵营
void Champion::setCamp(const bool isMyFlag)
{
    this->isMyFlag = isMyFlag;
}

// 获取战斗英雄所属阵营
bool Champion::getCamp() const
{
    return isMyFlag;
}

// 设置当前战斗英雄位置
void Champion::setCurrentPosition(const int& x, const int& y)
{
    currentLocation = { x, y };
}

// 获取战斗英雄移动状态
bool Champion::getIsMoving() const
{
    return isMoving;
}

// 设置战斗英雄移动状态
void Champion::setIsMoving()
{
    isMoving = true;
}

// 重置战斗英雄移动状态
void Champion::resetIsMoving()
{
    isMoving = false;
}

// 获取战斗英雄攻击状态
bool Champion::getIsAttacking() const
{
    return isAttaking;
}

// 设置战斗英雄攻击状态
void Champion::setIsAttacking()
{
    isAttaking = true;
}

// 重置战斗英雄攻击状态
void Champion::resetIsAttacking()
{
    isAttaking = false;
}

// 获取当前锁定敌人战斗英雄指针
Champion* Champion::getCurrentEnemy() const
{
    return currentEnemy;
}

// 获取当前敌人战斗位置属性
BattleLocation Champion::getCurrentLocation() const
{
    return currentLocation;
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

// 获取当前目标位置
BattleLocation Champion::getCurrentDestination() const
{
    return currentDestination;
}

// 设置当前目标位置
void Champion::setCurrentDestination(const BattleLocation destination)
{
    currentDestination = destination;
}

// 重置当前目标位置
void Champion::resetCurrentDestination()
{
    currentDestination = { currentLocation.x, currentLocation.y };
}

// 获取攻击时间间隔
float Champion::getAttackIntervalTimer() const
{
    return attackIntervalTimer;
}

// 增加攻击时间间隔
void Champion::addAttackIntervalTimer(const float delta)
{
    attackIntervalTimer += delta;
}

// 重置攻击时间间隔
void Champion::resetAttackIntervalTimer()
{
    attackIntervalTimer = 0.0f;
}

// 获取移动时间间隔
float Champion::getMoveIntervalTimer() const
{
    return moveIntervalTimer;
}

// 增加移动时间间隔
void Champion::addMoveIntervalTimer(const float delta)
{
    moveIntervalTimer += delta;
}

// 重置移动时间间隔
void Champion::resetMoveIntervalTimer()
{
    moveIntervalTimer = 0.0f;
}

// 获取当前移动
cocos2d::MoveTo* Champion::getCurrentMove() const
{
    return currentMove;
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

// 获取当前战斗类指针
Battle* Champion::getCurrentBattle() const
{
    return currentBattle;
}

// 获取最近敌方战斗英雄
void Champion::findNearestEnemy()
{
    Champion* nearestEnemy = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();

    // 遍历敌方战斗英雄
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (currentBattle->getChampion(i, j) != nullptr) {
                if (currentBattle->getChampion(i, j)->isMyFlag != isMyFlag) {
                    float distance = distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j }),
                        LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * BATTLE_MAP_COLUMNS + currentLocation.y }));
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
}

// 判断攻击范围内是否存在敌人战斗英雄
bool Champion::isInAttackRange()
{
    if (currentEnemy == nullptr) {
        return false;
    }
    float Distance = distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, currentEnemy->currentLocation.x * BATTLE_MAP_COLUMNS + currentEnemy->currentLocation.y }),
        LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * BATTLE_MAP_COLUMNS + currentLocation.y }));
    if (Distance <= attributes.attackRange * CHAMPION_HORIZONTAL_INTERVAL) {
        return true;
    }
    else {
        return false;
    }
}

// 判断当前位置是否在战斗区地图内
bool Champion::isInMap(const int& x, const int& y)
{
    return x >= 0 && x < BATTLE_MAP_ROWS && y >= 0 && y < BATTLE_MAP_COLUMNS;
}

// 移动
BattleLocation Champion::moveTowards(Champion* nearestEnemy)
{
    // 如果无最近敌人战斗英雄，则返回当前位置
    if (nearestEnemy == nullptr) {
        return currentLocation;
    }

    // 获取最近敌人战斗英雄位置
    BattleLocation enemyLocation = nearestEnemy->currentLocation;
    BattleLocation bestMove = currentLocation;
    if (nearestEnemy->currentLocation.x > currentLocation.x) {
        if (nearestEnemy->currentLocation.y <= currentLocation.y) {
            if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左上走
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // 往左走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右上走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左下走
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // 往右走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右下走
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右上走
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左上走
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // 往右走
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // 往左走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右下走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左下走
            else {
                return currentLocation;
            }
            return bestMove;
        }
    }
    else if (nearestEnemy->currentLocation.x == currentLocation.x) {
        if (nearestEnemy->currentLocation.y < currentLocation.y) {
            if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // 往左走
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左上走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左下走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往下上走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右上走
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // 往右走
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // 往右走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右上走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右下走
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左上走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左下走
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // 往左走
            else {
                return currentLocation;
            }
            return bestMove;
        }
    }
    else {
        if (nearestEnemy->currentLocation.y <= currentLocation.y) {
            if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左下走
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // 往左走
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右下走
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // 往右走
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左上走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右上走
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右下走
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // 往右走
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左下走
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // 往左走
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // 往右上走
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // 往左上走
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
    if (isInAttackRange() && currentEnemy) {
        // 受到攻击
        currentEnemy->beingAttack(attributes.attackDamage);
        attributes.magicPoints += INCREASED_MAGIC_POINTS;

        // 武器动画
        auto rotateToAction = cocos2d::RotateTo::create(WEAPON_ANIMATION_ROTATION_DURATION, sword->getRotation() + WEAPON_ANIMATION_ROTATION_ANGLE);
        auto rotateBackToAction = cocos2d::RotateTo::create(WEAPON_ANIMATION_ROTATION_DURATION, sword->getRotation());
        auto sequenceAction = cocos2d::Sequence::create(rotateToAction, rotateBackToAction, nullptr);
        auto repeatAction = cocos2d::Repeat::create(sequenceAction, WEAPON_ANIMATION_ROTATION_COUNT); // 假设重复 4 次
        sword->runAction(repeatAction);
    }
}

// 技能
void Champion::skill()
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (currentBattle->getChampion(i, j) != nullptr) {
                // 在射程 + 1 范围内所有敌方战斗英雄受到一次攻击
                if (currentBattle->getChampion(i, j)->isMyFlag != isMyFlag && distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * BATTLE_MAP_COLUMNS + j }),
                    LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * BATTLE_MAP_COLUMNS + currentLocation.y })) <= attributes.attackRange * CHAMPION_HORIZONTAL_INTERVAL + 1) {
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

// 死亡
void Champion::die()
{
    auto championSprite = getSprite();
    sword->getParent()->removeChild(sword,true);
    championSprite->getParent()->removeChild(sprite, true);
    Champion* temp = currentBattle->getChampion(currentLocation.x, currentLocation.y);
    currentBattle->championMap[currentLocation.x][currentLocation.y] = nullptr;
    delete temp;
}

// 设置武器是否可见
void Champion::setSwordVisible(const bool visible)
{
    if (sword) {
        sword->setVisible(visible);
    }
}

// 初始化武器
void Champion::initializeSword(const cocos2d::Vec2& position) {
    sword = cocos2d::Sprite::create("../Resources/Layers/Sword.png");
    if (sword) {
        sword->setPosition(position);
        sword->setVisible(false);
    }
}

// 设置武器位置
void Champion::setSwordPosition(const cocos2d::Vec2& position)
{
    sword->setPosition(position);
}

// 获取武器精灵类指针
cocos2d::Sprite* Champion::getSword() const
{
    return sword;
}

// 受到攻击
void Champion::beingAttack(const int& damage)
{
    attributes.healthPoints -= damage / attributes.defenseCoefficient;
    attributes.magicPoints += INCREASED_MAGIC_POINTS;
}

// 计算两点间距离
float Champion::distanceBetweenPoints(const cocos2d::Vec2& a, const cocos2d::Vec2& b)
{
    return a.distance(b);
}
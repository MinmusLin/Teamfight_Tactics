/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.cpp
 * File Function: Champion���ʵ��
 * Author:        �������������ǡ��ּ���
 * Update Date:   2023/12/27
 ****************************************************************/

#include "Champion.h"
#include "LocationMap/LocationMap.h"

// ���캯��
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

// ��ս����
void Champion::setBattle(Battle* myBattle)
{
    currentBattle = myBattle;
}

// ����ս��Ӣ��������Ӫ
void Champion::setCamp(const bool isMyFlag)
{
    this->isMyFlag = isMyFlag;
}

// ��ȡս��Ӣ��������Ӫ
bool Champion::getCamp() const
{
    return isMyFlag;
}

// ���õ�ǰս��Ӣ��λ��
void Champion::setCurrentPosition(const int& x, const int& y)
{
    currentLocation = { x, y };
}

// ��ȡս��Ӣ���ƶ�״̬
bool Champion::getIsMoving() const
{
    return isMoving;
}

// ����ս��Ӣ���ƶ�״̬
void Champion::setIsMoving()
{
    isMoving = true;
}

// ����ս��Ӣ���ƶ�״̬
void Champion::resetIsMoving()
{
    isMoving = false;
}

// ��ȡս��Ӣ�۹���״̬
bool Champion::getIsAttacking() const
{
    return isAttaking;
}

// ����ս��Ӣ�۹���״̬
void Champion::setIsAttacking()
{
    isAttaking = true;
}

// ����ս��Ӣ�۹���״̬
void Champion::resetIsAttacking()
{
    isAttaking = false;
}

// ��ȡ��ǰ��������ս��Ӣ��ָ��
Champion* Champion::getCurrentEnemy() const
{
    return currentEnemy;
}

// ��ȡ��ǰ����ս��λ������
BattleLocation Champion::getCurrentLocation() const
{
    return currentLocation;
}

// ��ȡ������ָ��
cocos2d::Sprite* Champion::getSprite() const
{
    return sprite;
}

// ��ȡս��Ӣ������
ChampionAttributes Champion::getAttributes() const
{
    return attributes;
}

// ��ȡ��ǰĿ��λ��
BattleLocation Champion::getCurrentDestination() const
{
    return currentDestination;
}

// ���õ�ǰĿ��λ��
void Champion::setCurrentDestination(const BattleLocation destination)
{
    currentDestination = destination;
}

// ���õ�ǰĿ��λ��
void Champion::resetCurrentDestination()
{
    currentDestination = { currentLocation.x, currentLocation.y };
}

// ��ȡ����ʱ����
float Champion::getAttackIntervalTimer() const
{
    return attackIntervalTimer;
}

// ���ӹ���ʱ����
void Champion::addAttackIntervalTimer(const float delta)
{
    attackIntervalTimer += delta;
}

// ���ù���ʱ����
void Champion::resetAttackIntervalTimer()
{
    attackIntervalTimer = 0.0f;
}

// ��ȡ�ƶ�ʱ����
float Champion::getMoveIntervalTimer() const
{
    return moveIntervalTimer;
}

// �����ƶ�ʱ����
void Champion::addMoveIntervalTimer(const float delta)
{
    moveIntervalTimer += delta;
}

// �����ƶ�ʱ����
void Champion::resetMoveIntervalTimer()
{
    moveIntervalTimer = 0.0f;
}

// ��ȡ��ǰ�ƶ�
cocos2d::MoveTo* Champion::getCurrentMove() const
{
    return currentMove;
}

// ���õ�ǰ�ƶ�
void Champion::setCurrentMove(cocos2d::MoveTo* move)
{
    currentMove = move;
}

// ���õ�ǰ�ƶ�
void Champion::resetCurrentMove()
{
    currentMove = nullptr;
}

// ��ȡ��ǰս����ָ��
Battle* Champion::getCurrentBattle() const
{
    return currentBattle;
}

// ��ȡ����з�ս��Ӣ��
void Champion::findNearestEnemy()
{
    Champion* nearestEnemy = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();

    // �����з�ս��Ӣ��
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

// �жϹ�����Χ���Ƿ���ڵ���ս��Ӣ��
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

// �жϵ�ǰλ���Ƿ���ս������ͼ��
bool Champion::isInMap(const int& x, const int& y)
{
    return x >= 0 && x < BATTLE_MAP_ROWS && y >= 0 && y < BATTLE_MAP_COLUMNS;
}

// �ƶ�
BattleLocation Champion::moveTowards(Champion* nearestEnemy)
{
    // ������������ս��Ӣ�ۣ��򷵻ص�ǰλ��
    if (nearestEnemy == nullptr) {
        return currentLocation;
    }

    // ��ȡ�������ս��Ӣ��λ��
    BattleLocation enemyLocation = nearestEnemy->currentLocation;
    BattleLocation bestMove = currentLocation;
    if (nearestEnemy->currentLocation.x > currentLocation.x) {
        if (nearestEnemy->currentLocation.y <= currentLocation.y) {
            if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // ������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // ������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
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
            } // ��������
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // ������
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // ������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
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
            } // ������
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // ������
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
            } // ������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // ������
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
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // ������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // ������
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
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
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            } // ������
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else if (isInMap(currentLocation.x, currentLocation.y - 1)
                && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            } // ������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            } // ��������
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0))
                && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            } // ��������
            else {
                return currentLocation;
            }
            return bestMove;
        }
    }
}

// ����
void Champion::attack()
{
    if (isInAttackRange() && currentEnemy) {
        // �ܵ�����
        currentEnemy->beingAttack(attributes.attackDamage);
        attributes.magicPoints += INCREASED_MAGIC_POINTS;

        // ��������
        auto rotateToAction = cocos2d::RotateTo::create(WEAPON_ANIMATION_ROTATION_DURATION, sword->getRotation() + WEAPON_ANIMATION_ROTATION_ANGLE);
        auto rotateBackToAction = cocos2d::RotateTo::create(WEAPON_ANIMATION_ROTATION_DURATION, sword->getRotation());
        auto sequenceAction = cocos2d::Sequence::create(rotateToAction, rotateBackToAction, nullptr);
        auto repeatAction = cocos2d::Repeat::create(sequenceAction, WEAPON_ANIMATION_ROTATION_COUNT); // �����ظ� 4 ��
        sword->runAction(repeatAction);
    }
}

// ����
void Champion::skill()
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (currentBattle->getChampion(i, j) != nullptr) {
                // ����� + 1 ��Χ�����ез�ս��Ӣ���ܵ�һ�ι���
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

// ����
void Champion::die()
{
    auto championSprite = getSprite();
    sword->getParent()->removeChild(sword,true);
    championSprite->getParent()->removeChild(sprite, true);
    Champion* temp = currentBattle->getChampion(currentLocation.x, currentLocation.y);
    currentBattle->championMap[currentLocation.x][currentLocation.y] = nullptr;
    delete temp;
}

// ���������Ƿ�ɼ�
void Champion::setSwordVisible(const bool visible)
{
    if (sword) {
        sword->setVisible(visible);
    }
}

// ��ʼ������
void Champion::initializeSword(const cocos2d::Vec2& position) {
    sword = cocos2d::Sprite::create("../Resources/Layers/Sword.png");
    if (sword) {
        sword->setPosition(position);
        sword->setVisible(false);
    }
}

// ��������λ��
void Champion::setSwordPosition(const cocos2d::Vec2& position)
{
    sword->setPosition(position);
}

// ��ȡ����������ָ��
cocos2d::Sprite* Champion::getSword() const
{
    return sword;
}

// �ܵ�����
void Champion::beingAttack(const int& damage)
{
    attributes.healthPoints -= damage / attributes.defenseCoefficient;
    attributes.magicPoints += INCREASED_MAGIC_POINTS;
}

// ������������
float Champion::distanceBetweenPoints(const cocos2d::Vec2& a, const cocos2d::Vec2& b)
{
    return a.distance(b);
}
/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.cpp
 * File Function: Champion���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#include "Champion.h"
#include "LocationMap/LocationMap.h"
#include "cocos2d.h"
#include "Battle/Battle.h"

 // ���캯��
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

// ����Ӣ��������Ӫ
void Champion::setCamp(bool isMyChampion)
{
    isMy = isMyChampion;
}

// ����Ӣ��������Ӫ
bool Champion::getCamp() const
{
    return isMy;
}

//�����������
float Champion::distanceBetweenPoints(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2) {
    const float dx = p2.x - p1.x;
    const float dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// ��ȡ����ĵط�Ӣ��
void Champion::findNearestEnemy()
{
    Champion* nearestEnemy = nullptr;
    float nearestDistance = std::numeric_limits<float>::max(); // ����һ���������ʼֵ

    // ������ͼ�򳡾��еĵз�Ӣ��
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (currentBattle->getChampion(i, j) != nullptr) {
                if (currentBattle->getChampion(i, j)->isMy != isMy) { // ���� ENEMY �ǵз�Ӣ�۵ı�ʶ
                    float distance = distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * 9 + j }),
                        LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * 9 + currentLocation.y }));

                    // �������ȵ�ǰ����ľ���С�������������˺��������
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

// �жϹ�����Χ���Ƿ��е���
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

// �ƶ�
BattleLocation Champion::moveTowards(Champion* nearestEnemy)
{
    // �������ĵ���Ϊ�գ��޷��ƶ������ص�ǰλ��
    if (nearestEnemy == nullptr)
        return currentLocation;

    // ��ȡ������˵�λ��
    BattleLocation enemyLocation = nearestEnemy->currentLocation;
    BattleLocation bestMove = currentLocation;
    if (nearestEnemy->currentLocation.x > currentLocation.x) {
        if (nearestEnemy->currentLocation.y <= currentLocation.y) {
            if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//�����Ͻ���
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//�����Ͻ���
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//��������
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//�����Ͻ���
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//�����Ͻ���
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//������
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//��������
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
            }//������
            else if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//��������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//��������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//������
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//�����Ͻ���
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//��������
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//�����Ͻ���
            else if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//��������
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//������
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
            }//��������
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//������
            else if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//������
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//�����Ͻ���
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//�����Ͻ���
            else {
                return currentLocation;
            }
            return bestMove;
        }
        else {
            if (isInMap(currentLocation.x - 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//��������
            else if (isInMap(currentLocation.x, currentLocation.y + 1) && currentBattle->championMap[currentLocation.x][currentLocation.y + 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y + 1;
            }//������
            else  if (isInMap(currentLocation.x - 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x - 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x - 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//��������
            else if (isInMap(currentLocation.x, currentLocation.y - 1) && currentBattle->championMap[currentLocation.x][currentLocation.y - 1] == nullptr) {
                bestMove.x = currentLocation.x;
                bestMove.y = currentLocation.y - 1;
            }//������
            else if (isInMap(currentLocation.x + 1, currentLocation.y + (currentLocation.x % 2 ? 0 : 1)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y + (currentLocation.x % 2 ? 0 : 1)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y + (currentLocation.x % 2 ? 0 : 1);
            }//�����Ͻ���
            else  if (isInMap(currentLocation.x + 1, currentLocation.y - (currentLocation.x % 2 ? 1 : 0)) && currentBattle->championMap[currentLocation.x + 1][currentLocation.y - (currentLocation.x % 2 ? 1 : 0)] == nullptr) {
                bestMove.x = currentLocation.x + 1;
                bestMove.y = currentLocation.y - (currentLocation.x % 2 ? 1 : 0);
            }//�����Ͻ���
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
    if (isInAttackRange()) {
        if (currentEnemy) {
            // �ڹ�����Χ�ڣ�ִ�й�������
            currentEnemy->beingAttack(attributes.attackDamage);
            attributes.magicPoints += 20;
        }
    }
}

// �ܵ�����
void Champion::beingAttack(const int& damage)
{
    attributes.healthPoints -= damage / attributes.defenseCoefficient;
    attributes.magicPoints += 20;
}

// �����˳�
void Champion::Die()
{
    auto championSprite = getSprite();
    championSprite->getParent()->removeChild(sprite, true);
    Champion* temp = currentBattle->getChampion(currentLocation.x, currentLocation.y);
    currentBattle->championMap[currentLocation.x][currentLocation.y] = nullptr;
    delete temp;
    return;
}

// �����˳�
void Champion::skill()
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (currentBattle->getChampion(i, j) != nullptr) {
                // �����+1��Χ������Ӣ��ȫ���ܵ�һ�ι���
                if (currentBattle->getChampion(i, j)->isMy != isMy && distanceBetweenPoints(LocationMap::getInstance().getLocationMap().at({ BattleArea, i * 9 + j }),
                    LocationMap::getInstance().getLocationMap().at({ BattleArea, currentLocation.x * 9 + currentLocation.y }))<= attributes.attackRange * CHAMPION_HORIZONTAL_INTERVAL+1) { // ���� ENEMY �ǵз�Ӣ�۵ı�ʶ
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

// �ж��Ƿ��ڳ���
bool Champion::isInMap(const int& x, const int& y)
{
    return x >= 0 && x < 8 && y >= 0 && y < 9;
}

// ���õ�ǰӢ��λ��
void Champion::setCurrentPosition(const int& x, const int& y)
{
    currentLocation.x = x;
    currentLocation.y = y;
}

// ��ս��
void Champion::setBattle(Battle* myBattle)
{
    currentBattle = myBattle;
}

// ����Ӣ���ƶ�״̬
bool Champion::getIsMoving() const
{
    return isMoving;
}

// ����Ӣ���ƶ�״̬
Champion* Champion::getCurrentEnemy() const
{
    return currentEnemy;
}

// ��ȡ�ƶ�ʱ���ʱ
float Champion::getMoveIntervalTimer() const
{
    return moveIntervalTimer;
}

// �����ƶ�ʱ����
void Champion::addMoveIntervalTimer(float delta)
{
    moveIntervalTimer += delta;
}

// �����ƶ�ʱ����
void Champion::resetMoveIntervalTimer()
{
    moveIntervalTimer = 0;
}

// ��ȡ����ʱ����
float Champion::getAttackIntervalTimer() const
{
    return attackIntervalTimer;
}

// ���ӹ���ʱ��
void Champion::addAttackIntervalTimer(float delta)
{
    attackIntervalTimer += delta;
}

// ���ù���ʱ����
void Champion::resetAttackIntervalTimer()
{
    attackIntervalTimer = 0.0f;
}

// ��ȡ��ǰ�ƶ�
cocos2d::MoveTo* Champion::getCurrentMove() const
{
    return currentMove;
}

// ��ȡ��ǰս��
Battle* Champion::getCurrentBattle() const
{
    return currentBattle;
}

// ��ȡӢ���ƶ�״̬
void Champion::setIsMoving()
{
    isMoving = true;
}

// ��ȡӢ���ƶ�״̬
void Champion::resetIsMoving()
{
    isMoving = false;
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

// ��ȡ��ǰ����
BattleLocation Champion::getCurrentLocation() const
{
    return currentLocation;
}

// ��ȡ����ʱ����
BattleLocation Champion::getCurrentDestination() const
{
    return currentDestination;
}

// ���ӹ���ʱ����
void Champion::setCurrentDestination(BattleLocation destination)
{
    currentDestination = destination;
}

// ���ù���ʱ����
void Champion::resetCurrentDestination()
{
    currentDestination = { currentLocation.x,currentLocation.y };
}

// ��ȡӢ���ƶ�״̬
bool Champion::getIsAttacking() const
{
    return isAttaking;
}

// ��ȡӢ���ƶ�״̬
void Champion::setIsAttacking()
{
    isAttaking = true;
}

// ��ȡӢ���ƶ�״̬
void Champion::resetIsAttacking()
{
    isAttaking = false;
}

// �� Champion ���д��������Ѫ��������
void Champion::initHealthBar() {
    // ����Ѫ���������� Sprite �� Label
    auto healthBar = Sprite::create("health_bar.png");
    auto manaBar = Sprite::create("mana_bar.png");

    // ����Ѫ����������λ�ã������Ӣ��
    healthBar->setPosition(cocos2d::Vec2(0, 50)); // ����Ѫ����Ӣ��ͷ���Ϸ�
    manaBar->setPosition(cocos2d::Vec2(0, 40));   // ����������Ѫ���·�

    // ��Ѫ�����������ΪӢ�۵��ӽڵ�
    this->addChild(healthBar);
    this->addChild(manaBar);

    // ��Ѫ����������Ϊ˽�г�Ա���������������ʾ
    this->healthBar = healthBar;
    this->manaBar = manaBar;
}

// ����Ѫ����������λ��
void Champion::updateHealthBarPosition() {
    // ����Ӣ�۵�λ�õ���Ѫ����������λ�ã�ʹ��̶���ͷ��
    cocos2d::Vec2 heroPosition = this->getPosition();
    this->healthBar->setPosition(cocos2d::Vec2(heroPosition.x, heroPosition.y + 50));
    this->manaBar->setPosition(cocos2d::Vec2(heroPosition.x, heroPosition.y + 40));
}

// ����Ѫ������������ʾ
void Champion::updateHealthBarDisplay() {
    // ����Ӣ�۵�ǰ��Ѫ������������Ѫ������������ʾ
    float currentHealth = attributes.healthPoints; // ��ȡӢ�۵�ǰѪ��
    float currentMana = attributes.magicPoints;     // ��ȡӢ�۵�ǰ����

    // ���ݵ�ǰѪ������������Ѫ������������ʾ������������ʾ��ʽ
    this->healthBar->setScaleX(currentHealth / maxHealthPoints); // ����Ѫ���� scaleX ����Ѫ������
    this->manaBar->setScaleX(currentMana / maxMagicPoints);       // ���������� scaleX ������������
}
#include "player.hpp"

Bullet* Player::SpawnBullet()
{
    Bullet* bullet = bulletsPool.GetItem();
    float radians = _turretRotation * (PI / 180);
    Vector2 direction = { sin(radians), cos(radians) };
    bullet->Init(_turretPosition, direction);
    return bullet;
}

void Player::Rotate(int direction)
{
    if (_turretRotation >= maxAngle)
        _turretRotation = maxAngle;

    if (_turretRotation <= -maxAngle)
        _turretRotation = -maxAngle;

    _turretRotation += direction * _rotationSpeed;
}

void Player::Shoot()
{
    PlaySound(_laserSound);
    bullets.push_back(SpawnBullet());
}

Vector2 Player::BasePosition() const { return _basePosition; }
Vector2 Player::TurretPosition() const { return _turretPosition; }
float Player::TurretRotation() const { return _turretRotation; }
float Player::RotSpeed() const { return _rotationSpeed; }
int Player::Score() const { return _score; }

Texture2D Player::BodyTexture() const { return _bodyTexture; }
Texture2D Player::TurretTexture() const { return _turretTexture; }

void Player::Init(Vector2 basePosition)
{
    _bodyTexture = LoadTexture("resources/Player/PlayerBody.png");
    _turretTexture = LoadTexture("resources/Player/Turret.png");

    _rotationSpeed = 5;
    maxAngle = 70;
    _timeout = 0.2;

    _score = 0;

    this->_basePosition = basePosition;
    _basePosition.x -= (float)_bodyTexture.width / 2;
    _basePosition.y -= (float)_bodyTexture.height;

    this->_turretPosition = basePosition;
    _turretPosition.x -= (float)_turretTexture.width / 2;
    _turretPosition.y -= (float)_turretTexture.height + (float)_bodyTexture.height;

    this->_shootingTimer = 0;

    _laserSound = LoadSound("resources/Music/shoot.wav");
}

void Player::Update(std::list<Helicopter*> helicopters, std::list<Trooper*> troopers)
{
    int dir;
    if (IsKeyDown(KEY_A))
        dir = -1;
    else if (IsKeyDown(KEY_D))
        dir = 1;
    else
        dir = 0;
    Rotate(dir);

    _shootingTimer += GetFrameTime();
    if (_shootingTimer >= _timeout && IsKeyPressed(KEY_SPACE))
    {
        _shootingTimer = 0;
        Shoot();
    }

    std::list<Bullet*>::iterator it = bullets.begin();
    while (it != bullets.end())
    {
        Bullet* bullet = (*it);
        if (bullet->IsOutOfScreen() || bullet->HelicopterHit() || bullet->TrooperHit())
        {
            bulletsPool.ReturnItem(bullet);
            bullets.erase(it++);
        }
        else
        {
            bullet->Update(helicopters, troopers);

            if (bullet->HelicopterHit())
            {
                _score += 10;
            }
            else if (bullet->TrooperHit())
            {
                _score += 5;
            }
            else if (bullet->IsOutOfScreen() && _score != 0)
            {
                _score -= 1;
            }
            ++it;
        }
    }
}

void Player::Draw()
{
    // Draw turret
    Rectangle turretBbox = Rectangle{ 0, 0, (float)_turretTexture.width, (float)_turretTexture.height };
    Rectangle destination = Rectangle{ SCR_WIDTH / 2, SCR_HEIGHT - (float)_bodyTexture.height + 5, (float)_turretTexture.width, (float)_turretTexture.height };
    Vector2 origin = Vector2{ (float)_turretTexture.width / 2, (float)_turretTexture.height };
    DrawTexturePro(_turretTexture, turretBbox, destination, origin, _turretRotation, WHITE);

    // Draw base
    DrawTextureEx(_bodyTexture, _basePosition, 0.0f, 1.0f, WHITE);

    for (Bullet* bullet : bullets)
    {
        bullet->Draw();
    }
}

void Player::Reset()
{
    UnloadSound(_laserSound);
    UnloadTexture(_bodyTexture);
    UnloadTexture(_turretTexture);
    _score = 0;
    _turretRotation = 0;
}
#include "Player.h"

#include <optional>

constexpr auto PlayerSpeed = 250.f;
const auto AnimationTime = sf::seconds(0.1f);

const auto TextSize = 50;
const auto BigSpace = 100.f;

Player::Player()
    : MoveAble(Resources::Objects::Player, Direction::Stay, AnimationTime), m_font(Resources::instance().getFont())
{
    setLivesIcon();
    setTexts();
}

void Player::setTexts()
{
    m_liveText.setFont(m_font);
    m_liveText.setCharacterSize(TextSize);
    m_liveText.setFillColor(sf::Color::Black);
    m_liveText.setOutlineThickness(2);
    m_liveText.setOutlineColor(sf::Color{ 0,150,80 });
    m_scoreText = m_liveText;

    updateLivesText();
    updateScoreText();
    setTextsPos();
}

void Player::setTextsPos()
{
    float x = m_livesIcon.getPosition().x + m_livesIcon.getGlobalBounds().width + 20.f;
    float y = BACBGROUND_HEIGHT + ((WINDOW_HEIGHT - BACBGROUND_HEIGHT) - (m_liveText.getGlobalBounds().height)) / 2;
    m_liveText.setPosition(sf::Vector2f(x, y));

    x = WINDOW_WIDTH - m_scoreText.getGlobalBounds().width - BigSpace;
    y = BACBGROUND_HEIGHT + ((WINDOW_HEIGHT - BACBGROUND_HEIGHT) - (m_scoreText.getGlobalBounds().height)) / 2;
    m_scoreText.setPosition(sf::Vector2f(x, y));
}

void Player::updateLivesText()
{
    m_liveText.setString(std::string("X " + std::to_string(m_lives)));
}

void Player::updateScoreText()
{
    m_scoreText.setString(std::string("score: " + std::to_string(m_score)));
}

void Player::setLivesIcon()
{
    m_livesIcon = m_sprite;
    auto rect = sf::IntRect(sf::Vector2i(154, 44), sf::Vector2i(16, 16));
    m_livesIcon.setTextureRect(rect);
    float x = FRAME_WIDTH;
    float y = BACBGROUND_HEIGHT + ((WINDOW_HEIGHT - BACBGROUND_HEIGHT) - m_livesIcon.getGlobalBounds().height) / 2;
    m_livesIcon.setPosition(sf::Vector2f(x, y));
}

void Player::setPos(sf::Vector2f& pos)
{
    m_sprite.setPosition(pos);
}

void Player::dirFromKey()
{
    static const
        std::initializer_list<std::pair<sf::Keyboard::Key, Direction>>
        keyToVectorMapping =
    {
        { sf::Keyboard::Right, Direction::Right },
        { sf::Keyboard::Left,  Direction::Left  },
        { sf::Keyboard::Up   , Direction::Up    },
        { sf::Keyboard::Down , Direction::Down  },
        { sf::Keyboard::Space, Direction::Stay  },
    };

    for (const auto& pair : keyToVectorMapping)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            direction(pair.second);
            return;
        }
    }
    m_dir = Direction::Stay;
    //m_faceRight = true;
    m_animation.direction(m_dir);
}

void Player::direction(Direction dir)
{
    m_dir = dir;
    m_animation.direction(dir);
 /*   if (dir == Direction::Left)
        m_faceRight = false;
    else
        m_faceRight = true;*/
}

void Player::handleEvents(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::C: shoot(); break;

    default:
        break;
    }
}

void Player::borderCollision(sf::RectangleShape& border)
{

    for (auto& s : m_shots) {
        auto topCordinate = (*s).getGlobalBounds().top;
        if (topCordinate <= border.getGlobalBounds().top)
            (*s).setIsDisposed(true);
    }
    moveInside(border);
}

void Player::shoot()
{    
    //m_shots.emplace_back(std::unique_ptr<BaseShot>(new BaseShot(m_sprite.getPosition())));
    m_shots.emplace_back(std::shared_ptr<RegularShot>(new RegularShot(m_sprite.getPosition(), Resources::Objects::RegularShot)));
}

void Player::draw(sf::RenderWindow& window)
{
    for (auto& s : m_shots) {
        (*s).draw(window);
    }
    window.draw(m_sprite);
    window.draw(m_livesIcon);
    window.draw(m_liveText);
    window.draw(m_scoreText);
}

void Player::removeLife()
{
    m_lives--;
    if (m_lives <= 0)
        m_isDisposed = true;
    updateLivesText();
}

bool Player::isLeftLives()
{
    return (m_lives >= 0 ? true : false);
}

void Player::addScore(BallSize size)
{
    switch (size)
    {
    case BallSize::Big:    m_score += 1;
        break;
    case BallSize::Medium: m_score += 2;
        break;
    case BallSize::Small:  m_score += 4;
        break;
    default:
        break;
    }
    updateScoreText();
}

void Player::resetPlayer(Situation& situation)
{
    handleSituation(situation);
    setIsDisposed(false);
    updateLivesText();
}

void Player::handleSituation(Situation& situation)
{
    switch (situation)
    {
    case Situation::GameOver:
    case Situation::GameFinished:
    case Situation::EscKeyPressed:
        m_lives = DEFAULT_LIFE;
        m_score = 0;

    case Situation::LevelFailed:
    case Situation::LevelSucced:
        m_shots.clear(); break;

    default: // exeption!!
        break;
    }
    setIsDisposed(false);
    updateLivesText();
    updateScoreText();
}

void Player::update(sf::Time delta)
{
    updateShots(delta);
    dirFromKey();
    if (m_dir == Direction::Stay)
    {
        return;
    }

    m_sprite.move(toVector(m_dir) * delta.asSeconds() * PlayerSpeed);
    m_animation.update(delta);
}

void Player::updateShots(sf::Time delta)
{
    for (auto& s : m_shots) {
        (*s).update(delta);
    }
}



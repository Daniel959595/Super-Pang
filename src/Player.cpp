#include "Player.h"

#include <optional>

constexpr auto PlayerSpeed = 350.f;
const auto AnimationTime = sf::seconds(0.1f);

const auto TextSize = 50;
const auto BigSpace = 100.f;

Player::Player()
    : MoveAble(Resources::Objects::Player, Direction::Stay, AnimationTime), m_font(Resources::instance().getFont())
      , m_shotType(Resources::Objects::RegularShot)
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

void Player::activateGift(Resources::Objects giftType)
{
    switch (giftType)
    {    
    case Resources::ScoreGift: this->addScore(GIFT_SCORE); break;
    case Resources::ShotsGift: break;
    case Resources::ExtraLifeGift: m_lives += 1; break;
    default: // exeption!!!
        break;
    }
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
        { sf::Keyboard::Up   , Direction::Stay    },
        { sf::Keyboard::Down , Direction::Stay  },
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
    m_animation.direction(m_dir);
}

void Player::direction(Direction dir)
{
    m_dir = dir;
    m_animation.direction(dir);
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

const sf::FloatRect Player::getHitBox() const
{
    auto thisBounds = this->getGlobalBounds();
    float x = thisBounds.left + (thisBounds.width / 5)*2;
    float y = thisBounds.top + (thisBounds.height / 4);
    
    auto rect = sf::FloatRect(x, y, thisBounds.width / 5, thisBounds.height - (thisBounds.height / 4));
    return rect;
}

void Player::shoot()
{    
    if (isCanShoot()) {
        Sounds::instance().activateSound(Sounds::Sound::RegularShot);
        m_shots.emplace_back(std::shared_ptr<RegularShot>
            (new RegularShot(m_sprite.getPosition(), Resources::Objects::RegularShot)));
    }
}

bool Player::isCanShoot()
{
    switch (m_shotType)
    {
    
    case Resources::RegularShot: return (m_shots.size() > 0 ? false : true);
        break;
    default:
        true;
        break;
    }
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

void Player::changeShotType(Resources::Objects shotType)
{
    m_shotType = shotType;
}

int Player::ballSizeToScore(BallSize size)
{
    switch (size)
    {
    case BallSize::Big:    return 1;
    case BallSize::Medium: return 2;
    case BallSize::Small:  return 4;
    default:
        break;
    }
}

void Player::addScore(int score)
{
    m_score += score;
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



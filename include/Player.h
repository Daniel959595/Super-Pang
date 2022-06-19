#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "MoveAble.h"
#include "RegularShot.h"

using ShotsData = std::vector<std::shared_ptr<BaseShot>>;

class Player : public MoveAble
{
public:
	Player();

	virtual void draw(sf::RenderWindow& window)              override;
	virtual void update(sf::Time delta);
	virtual void borderCollision(sf::RectangleShape& border) override;
	virtual const sf::FloatRect getHitBox() const override;

	void         setPos(sf::Vector2f& pos);
	void		 dirFromKey();
	void		 direction(Direction dir);
	void		 handleEvents(sf::Keyboard::Key key);
	void         removeLife();
	bool         isLeftLives();
	void         changeShotType(Resources::Objects shotType);
	int          ballSizeToScore(BallSize size);
	void         addScore(int score);
	void		 addLife();
	void         resetPlayer(Situation& situation);
	void         updateLivesText();
	void         updateScoreText();


	void         activateGift(Resources::Objects giftType);
	ShotsData&   getShots() { return m_shots; }

private:
	void		 setTexts();
	void		 setTextsPos();
	void         setLivesIcon();
	void		 shoot(); 
	bool		 isCanShoot();
	void		 updateShots(sf::Time delta);
	void         resetShotType();
	void         handleSituation(Situation& situation);

private:
	const sf::Font& m_font;

	sf::Text   m_liveText;
	sf::Text   m_scoreText;
	sf::Sprite m_livesIcon;

	int m_lives = DEFAULT_LIFE;
	int m_score = 0;

	ShotType  m_shot = ShotType::Normal;
	ShotsData m_shots;

	Resources::Objects m_shotType;
};
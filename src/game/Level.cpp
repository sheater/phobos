#include <iostream>

#include "Level.h"

Level::Level(
    const std::string &path,
    Renderer *renderer,
    AssetsManager *assetsMgr,
    InputHandler *inputHandler)
    : Scene(renderer, assetsMgr, inputHandler)
{
  m_player = new Player(this);
  Background *background = new Background(this);

  attachNode(m_player);
  attachNode(background);

  m_enemyGenerateTimer = 0.0f;

  // renderCollisionHulls = true;

  m_hud = new Hud(renderer->getWidth(), renderer->getHeight(), getUIManager());

  loadLevel(path);

  // base light
  getRenderer()->addLight(new Light());
}

Level::~Level()
{
  std::cout << "Level::~Level(): begin" << std::endl;

  delete m_hud;

  std::cout << "Level::~Level(): end" << std::endl;
}

void Level::loadLevel(const std::string &path)
{
  XMLDocument doc;
  doc.LoadFile(path.c_str());

  XMLElement *rootEl = doc.RootElement();

  for (
      XMLElement *element = rootEl->FirstChildElement();
      element;
      element = element->NextSiblingElement())
  {
    std::string name = element->Name();

    if (name == "row")
      parseRowElement(element);
  }
}

void Level::parseRowElement(XMLElement *element)
{
  float y = atof(element->Attribute("distance")) + 3.0f;

  for (
      XMLElement *rowEl = element->FirstChildElement();
      rowEl;
      rowEl = rowEl->NextSiblingElement())
  {
    std::string name = rowEl->Name();
    float align = atof(rowEl->Attribute("align"));

    if (name == "enemy") {
      Enemy* enemy = new Enemy(this, glm::vec2(align / 10.0f * 2.5f, y));
      attachNode(enemy);
    }
  }
}

void Level::update(float timeDelta)
{
  Scene::update(timeDelta);

  m_hud->heat = m_player->getWeaponHeat();
  m_hud->score = m_player->getScore();
  m_hud->update(timeDelta);
}

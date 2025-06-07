<<<<<<< HEAD

// Created by chill code on 28/04/2025,
// Last Modified: 09:11 PM 01/06/2025 
// Copyright © 2025 chill code. All rights reserved.

#include <SFML/Graphics.hpp>
#include <windows.h>
=======
>>>>>>> cb672f573b6bcec0f193885a5cc1979d8b8ab6d5
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<climits>
using namespace std;
struct FlashCard{
    string front;
    string back;
    string tag;
    float easyFactor;
    int interval;
    int repetitions;
    string lastDateReview;
<<<<<<< HEAD
    bool isBack = false;
=======
>>>>>>> cb672f573b6bcec0f193885a5cc1979d8b8ab6d5
};
void InitializeDeck(); // khoi tao 1 deck moi hoan toan
vector<FlashCard> LoadDeck(); // tai len bo the da luu
void AddCard(); // them the vao bo the
void DeleteCard();// xoa the 
<<<<<<< HEAD
void EditCard(FlashCard& card, string choice);// chinh sua lai the neu muon
void SM2(FlashCard& card, int quality);// thuat toan lap lai ngat quang
void SaveDeck(vector<FlashCard>& deck);// luu card

using namespace std;
extern sf::Font arialFont;;
enum appState {
  Home = 0,
  Start = 1,
  Setting = 2,
  Create = 3,
  Statistic = 4,
  Display = 5,
  Edit,
};

void initDeck(vector<FlashCard> &Deck);
struct Button {
  sf::RectangleShape rectangleShape;
  sf::Text labelText;
  bool notHover;
  // {100, 149, 237}
  Button(const sf::Vector2f &size, const sf::Vector2f &position,
         const std::string &textString, unsigned int fontSize,
         const sf::Color &color = {100, 149, 237},
         const sf::Color &colorText = sf::Color::White)
      : rectangleShape(size), labelText(arialFont, textString, fontSize),
        notHover(false) {
    rectangleShape.setOrigin(size / 2.f);
    rectangleShape.setPosition(position);
    rectangleShape.setFillColor(color);
    rectangleShape.setOutlineThickness(4.f);
    rectangleShape.setOutlineColor(sf::Color::White);

    sf::FloatRect textBounds = labelText.getLocalBounds();
    labelText.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                         textBounds.position.y + textBounds.size.y / 2.f});
    labelText.setPosition(position);
    labelText.setFillColor(colorText);
  }

  void hovering(const sf::Vector2f &mousePosition, const sf::Color &color,
                const sf::Vector2f &scale) {
    // color {135, 206, 250}
    // scale {1.2f, 1.2f}
    bool isHovered = rectangleShape.getGlobalBounds().contains(mousePosition);
    if (notHover == true) {
      isHovered = false;
    }
    if (isHovered) {
      rectangleShape.setFillColor(color);
      rectangleShape.setScale(scale);
      labelText.setScale(scale);
    } else {
      rectangleShape.setFillColor({100, 149, 237});
      rectangleShape.setScale({1.f, 1.f});
    }
  }

  bool isPressed(const sf::Vector2f &mousePosition) const {
    return rectangleShape.getGlobalBounds().contains(mousePosition) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
  }

  void draw(sf::RenderWindow &renderWindow) const {
    renderWindow.draw(rectangleShape);
    renderWindow.draw(labelText);
  }
};

struct DeckBox {
  vector<FlashCard> deck;
  sf::RectangleShape rectBox;
  sf::Text labelText;
  sf::Text numCard;
  bool notHover;
  // {100, 149, 237}
  DeckBox(const sf::Vector2f &size, const sf::Vector2f &position,
          const sf::String &textString, unsigned int fontSize,
          const sf::Color &color = {100, 149, 237},
          const sf::Color &colorText = sf::Color::White)
      : rectBox(size), labelText(arialFont, textString, fontSize),
        numCard(arialFont, "0", fontSize), notHover(false) {
    numCard.setString(to_string(deck.size()));

    rectBox.setOrigin(size / 2.f);
    rectBox.setPosition(position);
    rectBox.setFillColor(color);
    rectBox.setOutlineThickness(1.f);
    rectBox.setOutlineColor(sf::Color::Black);

    sf::FloatRect textBounds = labelText.getLocalBounds();
    labelText.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                         textBounds.position.y + textBounds.size.y / 2.f});
    labelText.setPosition(position);
    labelText.setFillColor(colorText);

    numCard.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                       textBounds.position.y + textBounds.size.y / 2.f});
    numCard.setPosition({position.x + textBounds.size.x + 30.f, position.y});
    numCard.setFillColor(sf::Color::Red);
  }

  void hovering(const sf::Vector2f &mousePosition, const sf::Color &color,
                const sf::Vector2f &scale) {
    // color {135, 206, 250}
    // scale {1.2f, 1.2f}
    bool isHovered = rectBox.getGlobalBounds().contains(mousePosition);
    if (notHover == true) {
      isHovered = false;
    }
    if (isHovered) {
      rectBox.setFillColor(color);
      rectBox.setScale(scale);
      labelText.setScale(scale);
    } else {
      rectBox.setFillColor({100, 149, 237});
      rectBox.setScale({1.f, 1.f});
    }
  }

  bool isPressed(const sf::Vector2f &mousePosition) const {
    return rectBox.getGlobalBounds().contains(mousePosition) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
  }

  void draw(sf::RenderWindow &renderWindow) const {
    renderWindow.draw(rectBox);
    renderWindow.draw(labelText);
    renderWindow.draw(numCard);
  }
};

struct CardBox {
  vector<FlashCard> deck;
  sf::RectangleShape rectBox;
  sf::Text content;
  sf::Text note;
  bool notHover;
  bool isFront;

  CardBox(const sf::Vector2f &size, const sf::Vector2f &position,
          const std::string &textString, unsigned int fontSize,
          const sf::Color &color = {100, 149, 237},
          const sf::Color &colorText = sf::Color::White)
      : rectBox(size), content(arialFont, textString, fontSize),
        notHover(false), isFront(true), note(arialFont, "", fontSize) {
    rectBox.setOrigin(size / 2.f);
    rectBox.setPosition(position);
    rectBox.setFillColor(color);
    rectBox.setOutlineThickness(4.f);
    rectBox.setOutlineColor(sf::Color::White);

    sf::FloatRect textBounds = content.getLocalBounds();
    content.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                       textBounds.position.y + textBounds.size.y / 2.f});
    content.setPosition(position);
    content.setFillColor(colorText);
  }

  void hovering(const sf::Vector2f &mousePosition, const sf::Color &color,
                const sf::Vector2f &scale) {
    // color {135, 206, 250}
    // scale {1.2f, 1.2f}
    bool isHovered = rectBox.getGlobalBounds().contains(mousePosition);
    if (notHover == true) {
      isHovered = false;
    }
    if (isHovered) {
      rectBox.setFillColor(color);
      rectBox.setScale(scale);
      content.setScale(scale);
    } else {
      rectBox.setFillColor({100, 149, 237});
      rectBox.setScale({1.f, 1.f});
    }
  }

  bool isPressed(const sf::Vector2f &mousePosition) const {
    return rectBox.getGlobalBounds().contains(mousePosition) &&
           sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
  }
  void draw(sf::RenderWindow &renderWindow) const {
    renderWindow.draw(rectBox);
    renderWindow.draw(content);
    renderWindow.draw(note);
  }
};

int ExitMessage();
int UpdateMessage();
int Notice(string s);
void updateState(appState &current);
void render(sf::RenderWindow &window, appState &current);
void gradientBackground(sf::RenderWindow &window);
void HomeEvents(sf::RenderWindow &window, Button HomeButtons[],
                appState &currentState, sf::Vector2f &mousePosition,
                vector<DeckBox> &DeckBoxes);
void StartEvents(sf::RenderWindow &window, Button StartButtons[],
                 appState &currentState, sf::Vector2f &mousePosition,
                 vector<DeckBox> &DeckBoxes);
sf::String getUserInput(sf::RenderWindow &window, const sf::Font &font);
void updateDeck(sf::RenderWindow &window, vector<DeckBox> &Decks);
void toAddNewCard(sf::RenderWindow &window, string &front, string &back,
                  string &tag, bool &added);
int findCard(vector<FlashCard> &deck, string needFind);
int findCardToDelete(vector<FlashCard> &deck, string front, string back, string tag);
void toEditCard(sf::RenderWindow &window, vector<FlashCard> &deck);
void toDeleteCard(sf::RenderWindow &window, vector<FlashCard> &deck, int &orderOfCard);
void FCEvents(sf::RenderWindow &window, Button FCButtons[],
              appState &currentState, sf::Vector2f &mousePosition,
              CardBox &cardBox, int &orderOfCard, int &displayEF);
void HomeRender(sf::RenderWindow &window, appState &currentState,
                vector<DeckBox> &DeckBoxes);
void StartRender(sf::RenderWindow &window, appState &currentState,
                 vector<DeckBox> &DeckBoxes);
void SettingRender(sf::RenderWindow &window, appState &currentState);
void CreateRender(sf::RenderWindow &window, appState &currentState,
                  vector<DeckBox> &DeckBoxes);
void StatisticRender(sf::RenderWindow &window, appState &currentState);
void FlashCardDisplay(sf::RenderWindow &window, appState &currentState,
                      DeckBox &Deck, CardBox &cardDefault);
void handleEvents(sf::RenderWindow &window, appState &currentState,
                  vector<DeckBox> &DeckBoxes, CardBox &cardBox);
=======



void EditCard(FlashCard& card, string choice);// chinh sua lai the neu muon
void SM2(FlashCard& card, int quality);// thuat toan lap lai ngat quang
void SaveDeck(vector<FlashCard>& deck);// luu card
>>>>>>> cb672f573b6bcec0f193885a5cc1979d8b8ab6d5

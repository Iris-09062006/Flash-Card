
// Created by chill code on 28/04/2025,
// Last Modified: 09:11 PM 01/06/2025 
// Copyright © 2025 chill code. All rights reserved.

#include "../include/FlashCard.h"

int main() {
  // create window
  sf::RenderWindow window(sf::VideoMode({800, 600}), "FlashCard");
  appState currentState = appState::Home;
  vector<DeckBox> DeckBoxes;
  sf::Vector2f buttonSize(window.getSize().x * 0.6f,
                          window.getSize().y * 0.05f);
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
  DeckBox deck0(buttonSize,
                sf::Vector2f(windowSize.x / 2.f,
                             windowSize.y / 4.115 +
                                 window.getSize().y * 0.06f *
                                     static_cast<float>(DeckBoxes.size()) -
                                 10.f),
                "DEFAULT", 20);
  DeckBoxes.push_back(deck0);
  HomeRender(window, currentState, DeckBoxes);

  // create shape of button: rectangle
  sf::RectangleShape rect({200.f, 100.f});
  rect.setOrigin(rect.getGeometricCenter());
  rect.setPosition({300.f, 300.f});
  rect.setFillColor(sf::Color(128, 128, 128));

  // state of mouse button
  bool isPressed = false;

  CardBox cardBox = {
      sf::Vector2f(window.getSize().x * 0.65f, window.getSize().y * 0.55f),
      sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f - 60.f),
      "", 24};

  // Loop to remain the window
  while (window.isOpen()) {
    // handle events
    handleEvents(window, currentState, DeckBoxes, cardBox);
    // update state of app
    updateState(currentState);
    // render appropiate with state
    render(window, currentState);
  }
  return 0;
}

// Created by chill code on 28/04/2025,
// Last Modified: 09:11 PM 01/06/2025 
// Copyright © 2025 chill code. All rights reserved.

#include "../include/FlashCard.h"

int whatDeck = 1;
sf::Font arialFont("C:/Windows/Fonts/arial.ttf");
void initDeck(vector<FlashCard> &Deck) {
  for (int i = 0; i < 10; i++) {
    FlashCard card = {"nice", "Qua da", "Feeling in da house", 0,
                      0,      0,        "01/01/2000",          false};
    Deck.push_back(card);
  }
}

int ExitMessage() {
  int result = MessageBoxA(NULL, "Do you want to exit the program?", "Notice",
                           MB_YESNO | MB_ICONQUESTION);
  return result;
}

int UpdateMessage() {
  int result = MessageBoxA(
      NULL, "This feature is temporarily unavailable. Please come back later!",
      "Notice", MB_OKCANCEL | MB_ICONINFORMATION);
  return result;
}

int Notice(string s) {
  int result =
      MessageBoxA(NULL, s.c_str(), "Notice", MB_OKCANCEL | MB_ICONQUESTION);
  return result;
}

void updateState(appState &current) {}

void render(sf::RenderWindow &window, appState &current) {}

void gradientBackground(sf::RenderWindow &window) {
  sf::VertexArray gradientBackground(sf::PrimitiveType::TriangleFan, 4);
  // Top - Left
  gradientBackground[0].position = {0.f, 0.f};
  gradientBackground[0].color = {135, 206, 235};
  // Top - Right
  gradientBackground[1].position = {static_cast<float>(window.getSize().x),
                                    0.f};
  gradientBackground[1].color = {135, 206, 235};
  // Bottom - Left
  gradientBackground[2].position = {static_cast<float>(window.getSize().x),
                                    static_cast<float>(window.getSize().y)};
  gradientBackground[2].color = {240, 248, 255};
  // Bottom - Right
  gradientBackground[3].position = {0.f,
                                    static_cast<float>(window.getSize().y)};
  gradientBackground[3].color = {240, 248, 255};
  window.draw(gradientBackground);
}

void HomeEvents(sf::RenderWindow &window, Button HomeButtons[],
                appState &currentState, sf::Vector2f &mousePosition,
                vector<DeckBox> &DeckBoxes) {
  while (std::optional event = window.pollEvent()) {
    // when button close is clicked
    if (event->is<sf::Event::Closed>()) {
      // close window and exit program
      window.close();
    }
    // when window is resized
    else if (event->is<sf::Event::Resized>()) {
      // update view
      sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
      window.setView(view);
    }
    // when button is pressed
    if (auto *mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
      // Left button mouse
      if (mouse->button == sf::Mouse::Button::Left) {
        for (int i = 0; i < 4; i++) {
          if (HomeButtons[i].isPressed(mousePosition)) {
            if (i == 0)
              currentState = appState::Start;
            else if (i == 1) {
              currentState = appState::Setting;
            } else if (i == 2) {
              int notice = Notice("Do you want to load default decks!");
              if (notice == 1) {
                int notice1 = Notice("Loaded successfully!");
                std::vector<FlashCard> deck = LoadDeck();
                DeckBoxes[0].deck = deck;

              } else if (notice == 2) {
                int notice1 = Notice("Loaded failed!");
              }
            } else if (i == 3) {
              int result = ExitMessage();
              if (result == IDYES) {
                window.close();
              }
            }
          }
        }
      }
    }
  }
}

void StartEvents(sf::RenderWindow &window, Button StartButtons[],
                 appState &currentState, sf::Vector2f &mousePosition,
                 vector<DeckBox> &DeckBoxes) {
  while (std::optional event = window.pollEvent()) {
    // when button close is clicked
    if (event->is<sf::Event::Closed>()) {
      // close window and exit program
      window.close();
    }
    // when window is resized
    else if (event->is<sf::Event::Resized>()) {
      // update view
      sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
      window.setView(view);
    }
    // when button is pressed
    else if (auto *mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
      // Left button mouse
      if (mouse->button == sf::Mouse::Button::Left) {
        for (int i = 0; i < 4; i++) {
          if (StartButtons[i].isPressed(mousePosition)) {
            if (i == 1) {
              currentState = appState::Create;
            } else if (i == 2)
              currentState = appState::Statistic;
            else if (i == 3)
              currentState = appState::Home;
          }
        }
      }
      for (int i = 0; i < DeckBoxes.size(); i++) {
        if (DeckBoxes[i].isPressed(mousePosition) == true) {
          currentState = appState::Display;
          whatDeck = i;
          std::cout << whatDeck << "\n";
        }
      }
    }
  }
}

sf::String getUserInput(sf::RenderWindow &window, const sf::Font &font) {
  sf::String input;
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
  sf::RectangleShape dialogBg({600.f, 200.f});
  dialogBg.setFillColor({200, 200, 200});
  float dx = (windowSize.x) / 2.f;
  float dy = (windowSize.y) / 2.f - 150.f;
  dialogBg.setOrigin({dialogBg.getSize().x / 2.f, dialogBg.getSize().y / 2.f});
  dialogBg.setPosition({dx, dy});

  sf::Text prompt(font);
  prompt.setString("Enter a new deck:");
  prompt.setCharacterSize(20);
  prompt.setFillColor(sf::Color::Black);
  prompt.setOrigin({prompt.getGlobalBounds().size.x / 2.f,
                    prompt.getGlobalBounds().size.y / 2.f});
  prompt.setPosition({dx, dy - dialogBg.getSize().y / 2.f + 30.f});
  prompt.setStyle(sf::Text::Bold);

  sf::RectangleShape inputBox({480.f, 40.f});
  inputBox.setOrigin({inputBox.getSize().x / 2.f, inputBox.getSize().y / 2.f});
  inputBox.setFillColor(sf::Color::White);
  inputBox.setOutlineColor(sf::Color::Black);
  inputBox.setOutlineThickness(1.f);
  inputBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 30.f});

  sf::Text inputText(font);
  inputText.setOrigin({inputText.getGlobalBounds().size.x / 2.f,
                       inputText.getGlobalBounds().size.y / 2.f});
  inputText.setString("");
  inputText.setCharacterSize(20);
  inputText.setFillColor(sf::Color::Black);
  inputText.setPosition({dx - dialogBg.getSize().x / 2.f + 70.f,
                         dy - dialogBg.getSize().y / 4.f + 20.f});

  sf::Text placeholderText(font);
  placeholderText.setString("New deck...");
  placeholderText.setCharacterSize(20);
  placeholderText.setFillColor({128, 128, 128});
  placeholderText.setPosition({dx - dialogBg.getSize().x / 2.f + 70.f,
                               dy - dialogBg.getSize().y / 4.f + 20.f});

  sf::RectangleShape okButton({80.f, 30.f});
  okButton.setFillColor({0, 128, 0});
  okButton.setOrigin({okButton.getSize().x / 2.f, okButton.getSize().y / 2.f});
  okButton.setPosition({dx, dy + 60.f});

  sf::Text okText(font);
  okText.setOrigin({okText.getGlobalBounds().size.x / 2.f,
                    okText.getGlobalBounds().size.y / 2.f});
  okText.setString("Ok");
  okText.setCharacterSize(20);
  okText.setFillColor(sf::Color::White);
  okText.setPosition({dx - 10.f, dy + 50.f});

  while (window.isOpen()) {
    while (auto opt = window.pollEvent()) {
      const auto &event = *opt;
      if (event.is<sf::Event::Closed>()) {
        window.close();
        return input;
      } else if (opt->is<sf::Event::Resized>()) {
        // update view
        sf::View view(
            sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
      if (auto *m = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (m->button == sf::Mouse::Button::Left) {
          auto mp = window.mapPixelToCoords({m->position.x, m->position.y});
          if (okButton.getGlobalBounds().contains(mp))
            return input;
        }
      }
      if (auto *k = event.getIf<sf::Event::KeyPressed>()) {
        if (k->code == sf::Keyboard::Key::Enter)
          return input;
      }
      if (auto *t = event.getIf<sf::Event::TextEntered>()) {
        auto u = t->unicode;
        if (u == 8 && !input.isEmpty())
          input.erase(input.getSize() - 1);
        else if (u >= 32 && u < 128)
          input += u;
        inputText.setString(input);
      }
    }

    window.draw(dialogBg);
    window.draw(prompt);
    window.draw(inputBox);
    if (input.isEmpty())
      window.draw(placeholderText);
    else
      window.draw(inputText);
    window.draw(okButton);
    window.draw(okText);
    window.display();
  }
  return input;
}

void updateDeck(sf::RenderWindow &window, vector<DeckBox> &Decks) {
  sf::Vector2f buttonSize(window.getSize().x * 0.6f,
                          window.getSize().y * 0.05f);
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);

  for (int i = 0; i < Decks.size(); i++) {
    sf::Vector2f position(windowSize.x / 2.f, windowSize.y / 4.115 +
                                                  window.getSize().y * 0.06f *
                                                      static_cast<float>(i) -
                                                  10.f);
    Decks[i].rectBox.setSize(buttonSize);
    Decks[i].numCard.setString(to_string(Decks[i].deck.size()));

    Decks[i].rectBox.setOrigin(buttonSize / 2.f);
    Decks[i].rectBox.setPosition(position);

    sf::FloatRect textBounds = Decks[i].labelText.getLocalBounds();
    Decks[i].labelText.setOrigin(
        {textBounds.position.x + textBounds.size.x / 2.f,
         textBounds.position.y + textBounds.size.y / 2.f});
    Decks[i].labelText.setPosition(position);

    Decks[i].numCard.setOrigin(
        {textBounds.position.x + textBounds.size.x / 2.f,
         textBounds.position.y + textBounds.size.y / 2.f});
    Decks[i].numCard.setPosition(
        {position.x + textBounds.size.x * 1.2f, position.y});
  }
}

void toAddNewCard(sf::RenderWindow &window, string &front, string &back,
                  string &tag, bool &added) {
  sf::String inputFront;
  sf::String inputBack;
  sf::String inputTag;
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);

  sf::RectangleShape dialogBg(
      sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f));
  dialogBg.setFillColor({200, 200, 200});
  float dx = (windowSize.x) * 0.5f;
  float dy = (windowSize.y) * 0.5f;
  dialogBg.setOrigin({dialogBg.getSize().x / 2.f, dialogBg.getSize().y / 2.f});
  dialogBg.setPosition({dx, dy});

  sf::Text prompt(arialFont);
  prompt.setString("GET CARD DATA");
  prompt.setCharacterSize(30);
  prompt.setFillColor(sf::Color::Black);
  prompt.setOrigin({prompt.getGlobalBounds().size.x * 0.5f,
                    prompt.getGlobalBounds().size.y * 0.5f});
  prompt.setPosition({dx, dy - dialogBg.getSize().y * 0.5f + 40.f});
  prompt.setStyle(sf::Text::Bold);
  // Front box
  sf::RectangleShape frontBox({600.f, 50.f});
  frontBox.setOrigin(
      {frontBox.getSize().x / 2.f - 65.f, frontBox.getSize().y / 2.f});
  frontBox.setFillColor(sf::Color::White);
  frontBox.setOutlineColor(sf::Color::Black);
  frontBox.setOutlineThickness(1.f);
  frontBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f - 100.f});
  // Back box
  sf::RectangleShape backBox({600.f, 50.f});
  backBox.setOrigin(
      {backBox.getSize().x / 2.f - 65.f, backBox.getSize().y / 2.f});
  backBox.setFillColor(sf::Color::White);
  backBox.setOutlineColor(sf::Color::Black);
  backBox.setOutlineThickness(1.f);
  backBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f});
  // Tag box
  sf::RectangleShape tagBox({600.f, 50.f});
  tagBox.setOrigin({tagBox.getSize().x / 2.f - 65.f, tagBox.getSize().y / 2.f});
  tagBox.setFillColor(sf::Color::White);
  tagBox.setOutlineColor(sf::Color::Black);
  tagBox.setOutlineThickness(1.f);
  tagBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f + 100.f});

  // Front input text
  sf::Text frontText(arialFont);
  frontText.setOrigin({frontText.getGlobalBounds().size.x / 2.f,
                       frontText.getGlobalBounds().size.y / 2.f});
  frontText.setString("");
  frontText.setCharacterSize(20);
  frontText.setFillColor(sf::Color::Black);
  frontText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                         dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // Back input text
  sf::Text backText(arialFont);
  backText.setOrigin({backText.getGlobalBounds().size.x / 2.f,
                      backText.getGlobalBounds().size.y / 2.f});
  backText.setString("");
  backText.setCharacterSize(20);
  backText.setFillColor(sf::Color::Black);
  backText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                        dy - dialogBg.getSize().y / 4.f + 150.f});
  // Tag input text
  sf::Text tagText(arialFont);
  tagText.setOrigin({tagText.getGlobalBounds().size.x / 2.f,
                     tagText.getGlobalBounds().size.y / 2.f});
  tagText.setString("");
  tagText.setCharacterSize(20);
  tagText.setFillColor(sf::Color::Black);
  tagText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                       dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});
  // PH front
  sf::Text frontPH(arialFont);
  frontPH.setString("Front text...");
  frontPH.setCharacterSize(20);
  frontPH.setFillColor({128, 128, 128});
  frontPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                       dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // PH back
  sf::Text backPH(arialFont);
  backPH.setString("Back text...");
  backPH.setCharacterSize(20);
  backPH.setFillColor({128, 128, 128});
  backPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                      dy - dialogBg.getSize().y / 4.f + 150.f});
  // PH tag
  sf::Text tagPH(arialFont);
  tagPH.setString("Tag text...");
  tagPH.setCharacterSize(20);
  tagPH.setFillColor({128, 128, 128});
  tagPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                     dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});
  // Button ok
  sf::RectangleShape okButton({80.f, 30.f});
  okButton.setFillColor({0, 128, 0});
  okButton.setOrigin({okButton.getSize().x / 2.f, okButton.getSize().y / 2.f});
  okButton.setPosition({dx, dy + 220.f});

  sf::Text okText(arialFont);
  okText.setOrigin({okText.getGlobalBounds().size.x / 2.f,
                    okText.getGlobalBounds().size.y / 2.f});
  okText.setString("Ok");
  okText.setCharacterSize(20);
  okText.setFillColor(sf::Color::White);
  okText.setPosition({dx - 10, dy + 205.f});
  // Button front
  sf::RectangleShape frontButton({80.f, 30.f});
  frontButton.setFillColor({0, 128, 0});
  frontButton.setOrigin(
      {frontButton.getSize().x / 2.f, frontButton.getSize().y / 2.f});
  frontButton.setPosition(
      {dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
       dy - dialogBg.getSize().y / 4.f + 150.f - 100.f + 10.f});

  sf::Text frontBTText(arialFont);
  frontBTText.setOrigin({frontBTText.getGlobalBounds().size.x / 2.f,
                         frontBTText.getGlobalBounds().size.y / 2.f});
  frontBTText.setString("Front");
  frontBTText.setCharacterSize(20);
  frontBTText.setFillColor(sf::Color::Black);
  frontBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                           dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // Button back
  sf::RectangleShape backButton({80.f, 30.f});
  backButton.setFillColor({0, 128, 0});
  backButton.setOrigin(
      {backButton.getSize().x / 2.f, backButton.getSize().y / 2.f});
  backButton.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
                          dy - dialogBg.getSize().y / 4.f + 150.f + 10.f});

  sf::Text backBTText(arialFont);
  backBTText.setOrigin({backBTText.getGlobalBounds().size.x / 2.f,
                        backBTText.getGlobalBounds().size.y / 2.f});
  backBTText.setString("Back");
  backBTText.setCharacterSize(20);
  backBTText.setFillColor(sf::Color::Black);
  backBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                          dy - dialogBg.getSize().y / 4.f + 150.f});
  // Button tag
  sf::RectangleShape tagButton({80.f, 30.f});
  tagButton.setFillColor({0, 128, 0});
  tagButton.setOrigin(
      {tagButton.getSize().x / 2.f, tagButton.getSize().y / 2.f});
  tagButton.setPosition(
      {dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
       dy - dialogBg.getSize().y / 4.f + 150.f + 100.f + 10.f});

  sf::Text tagBTText(arialFont);
  tagBTText.setOrigin({tagBTText.getGlobalBounds().size.x / 2.f,
                       tagBTText.getGlobalBounds().size.y / 2.f});
  tagBTText.setString("Tag");
  tagBTText.setCharacterSize(20);
  tagBTText.setFillColor(sf::Color::Black);
  tagBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                         dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});

  dialogBg.setScale({1.1f, 1.1f});
  int currentInput = 0;
  while (window.isOpen()) {
    while (auto opt = window.pollEvent()) {
      const auto &event = *opt;
      if (event.is<sf::Event::Closed>()) {
        window.close();
      } else if (opt->is<sf::Event::Resized>()) {
        sf::View view(
            sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
      if (auto *m = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (m->button == sf::Mouse::Button::Left) {
          auto mp = window.mapPixelToCoords({m->position.x, m->position.y});
          if (okButton.getGlobalBounds().contains(mp)) {
            front = inputFront.toAnsiString();
            back = inputBack.toAnsiString();
            tag = inputTag.toAnsiString();
            if (front == "" && back == "") {
              int notice = Notice("Invalid card!");
              added = false;
              return;
            } else {
              int notice = Notice("Add successfully!");
              added = true;
              return;
            }
          }
          if (frontButton.getGlobalBounds().contains(mp)) {
            currentInput = 1;
          } else if (backButton.getGlobalBounds().contains(mp)) {
            currentInput = 2;
          } else if (tagButton.getGlobalBounds().contains(mp)) {
            currentInput = 3;
          } else {
            currentInput = 0;
          }
        }
      }
      if (auto *k = event.getIf<sf::Event::KeyPressed>()) {
        if (k->code == sf::Keyboard::Key::Enter) {
          front = inputFront.toAnsiString();
          back = inputBack.toAnsiString();
          tag = inputTag.toAnsiString();
          if (front == "" && back == "") {
            int notice = Notice("Invalid card!");
            added = false;
            return;
          } else {
            int notice = Notice("Add successfully!");
            added = true;
            return;
          }
        }
      }
      if (auto *t = event.getIf<sf::Event::TextEntered>()) {
        auto u = t->unicode;
        if (u == 8) {
          if (currentInput == 1 && !inputFront.isEmpty())
            inputFront.erase(inputFront.getSize() - 1);
          else if (currentInput == 2 && !inputBack.isEmpty())
            inputBack.erase(inputBack.getSize() - 1);
          else if (currentInput == 3 && !inputTag.isEmpty())
            inputTag.erase(inputTag.getSize() - 1);
        } else if (u >= 32 && u < 128) {
          if (currentInput == 1)
            inputFront += u;
          else if (currentInput == 2)
            inputBack += u;
          else if (currentInput == 3)
            inputTag += u;
        }

        frontText.setString(inputFront);
        backText.setString(inputBack);
        tagText.setString(inputTag);
      }
    }

    window.draw(dialogBg);
    window.draw(prompt);
    window.draw(frontBox);
    window.draw(backBox);
    window.draw(tagBox);
    if (inputFront.isEmpty()) {
      window.draw(frontPH);
    } else {
      window.draw(frontText);
    }
    if (inputBack.isEmpty()) {
      window.draw(backPH);
    } else {
      window.draw(backText);
    }
    if (inputTag.isEmpty()) {
      window.draw(tagPH);
    } else {
      window.draw(tagText);
    }
    window.draw(okButton);
    window.draw(okText);
    window.draw(frontButton);
    window.draw(frontBTText);
    window.draw(backButton);
    window.draw(backBTText);
    window.draw(tagButton);
    window.draw(tagBTText);
    window.display();
  }
}

int findCard(vector<FlashCard> &deck, string needFind) {
  int pos = -1;
  for (int i = 0; i < deck.size(); i++) {
    if (deck[i].front == needFind) {
      pos = i;
      break;
    } else if (deck[i].back == needFind) {
      pos = i;
      break;
    } else if (deck[i].tag == needFind) {
      pos = i;
      break;
    }
  }
  return pos;
}

int findCardToDelete(vector<FlashCard> &deck, string front, string back,
                     string tag) {
  int pos = -1;
  for (int i = 0; i < deck.size(); i++) {
    if (deck[i].front == front && deck[i].back == back && deck[i].tag == tag) {
      pos = i;
      break;
    }
  }
  return pos;
}

void toEditCard(sf::RenderWindow &window, vector<FlashCard> &deck) {
  sf::String inputFront;
  sf::String inputBack;
  sf::String inputTag;
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);

  sf::RectangleShape dialogBg(
      sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f));
  dialogBg.setFillColor({200, 200, 200});
  float dx = (windowSize.x) * 0.5f;
  float dy = (windowSize.y) * 0.5f;
  dialogBg.setOrigin({dialogBg.getSize().x / 2.f, dialogBg.getSize().y / 2.f});
  dialogBg.setPosition({dx, dy});

  sf::Text prompt(arialFont);
  prompt.setString("EDIT CARD'S DATA");
  prompt.setCharacterSize(30);
  prompt.setFillColor(sf::Color::Black);
  prompt.setOrigin({prompt.getGlobalBounds().size.x * 0.5f,
                    prompt.getGlobalBounds().size.y * 0.5f});
  prompt.setPosition({dx, dy - dialogBg.getSize().y * 0.5f + 40.f});
  prompt.setStyle(sf::Text::Bold);
  // Front box
  sf::RectangleShape frontBox({600.f, 50.f});
  frontBox.setOrigin(
      {frontBox.getSize().x / 2.f - 65.f, frontBox.getSize().y / 2.f});
  frontBox.setFillColor(sf::Color::White);
  frontBox.setOutlineColor(sf::Color::Black);
  frontBox.setOutlineThickness(1.f);
  frontBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f - 100.f});
  // Back box
  sf::RectangleShape backBox({600.f, 50.f});
  backBox.setOrigin(
      {backBox.getSize().x / 2.f - 65.f, backBox.getSize().y / 2.f});
  backBox.setFillColor(sf::Color::White);
  backBox.setOutlineColor(sf::Color::Black);
  backBox.setOutlineThickness(1.f);
  backBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f});
  // Tag box
  sf::RectangleShape tagBox({600.f, 50.f});
  tagBox.setOrigin({tagBox.getSize().x / 2.f - 65.f, tagBox.getSize().y / 2.f});
  tagBox.setFillColor(sf::Color::White);
  tagBox.setOutlineColor(sf::Color::Black);
  tagBox.setOutlineThickness(1.f);
  tagBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f + 100.f});

  // Front input text
  sf::Text frontText(arialFont);
  frontText.setOrigin({frontText.getGlobalBounds().size.x / 2.f,
                       frontText.getGlobalBounds().size.y / 2.f});
  frontText.setString("");
  frontText.setCharacterSize(20);
  frontText.setFillColor(sf::Color::Black);
  frontText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                         dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // Back input text
  sf::Text backText(arialFont);
  backText.setOrigin({backText.getGlobalBounds().size.x / 2.f,
                      backText.getGlobalBounds().size.y / 2.f});
  backText.setString("");
  backText.setCharacterSize(20);
  backText.setFillColor(sf::Color::Black);
  backText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                        dy - dialogBg.getSize().y / 4.f + 150.f});
  // Tag input text
  sf::Text tagText(arialFont);
  tagText.setOrigin({tagText.getGlobalBounds().size.x / 2.f,
                     tagText.getGlobalBounds().size.y / 2.f});
  tagText.setString("");
  tagText.setCharacterSize(20);
  tagText.setFillColor(sf::Color::Black);
  tagText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                       dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});
  // PH front
  sf::Text frontPH(arialFont);
  frontPH.setString("Front text...");
  frontPH.setCharacterSize(20);
  frontPH.setFillColor({128, 128, 128});
  frontPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                       dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // PH back
  sf::Text backPH(arialFont);
  backPH.setString("Back text...");
  backPH.setCharacterSize(20);
  backPH.setFillColor({128, 128, 128});
  backPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                      dy - dialogBg.getSize().y / 4.f + 150.f});
  // PH tag
  sf::Text tagPH(arialFont);
  tagPH.setString("Tag text...");
  tagPH.setCharacterSize(20);
  tagPH.setFillColor({128, 128, 128});
  tagPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                     dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});
  // Button ok
  sf::RectangleShape okButton({80.f, 30.f});
  okButton.setFillColor({0, 128, 0});
  okButton.setOrigin({okButton.getSize().x / 2.f, okButton.getSize().y / 2.f});
  okButton.setPosition({dx, dy + 220.f});

  sf::Text okText(arialFont);
  okText.setOrigin({okText.getGlobalBounds().size.x / 2.f,
                    okText.getGlobalBounds().size.y / 2.f});
  okText.setString("Ok");
  okText.setCharacterSize(20);
  okText.setFillColor(sf::Color::White);
  okText.setPosition({dx - 10, dy + 205.f});
  // Button front
  sf::RectangleShape frontButton({80.f, 30.f});
  frontButton.setFillColor({0, 128, 0});
  frontButton.setOrigin(
      {frontButton.getSize().x / 2.f, frontButton.getSize().y / 2.f});
  frontButton.setPosition(
      {dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
       dy - dialogBg.getSize().y / 4.f + 150.f - 100.f + 10.f});

  sf::Text frontBTText(arialFont);
  frontBTText.setOrigin({frontBTText.getGlobalBounds().size.x / 2.f,
                         frontBTText.getGlobalBounds().size.y / 2.f});
  frontBTText.setString("Front");
  frontBTText.setCharacterSize(20);
  frontBTText.setFillColor(sf::Color::Black);
  frontBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                           dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // Button back
  sf::RectangleShape backButton({80.f, 30.f});
  backButton.setFillColor({0, 128, 0});
  backButton.setOrigin(
      {backButton.getSize().x / 2.f, backButton.getSize().y / 2.f});
  backButton.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
                          dy - dialogBg.getSize().y / 4.f + 150.f + 10.f});

  sf::Text backBTText(arialFont);
  backBTText.setOrigin({backBTText.getGlobalBounds().size.x / 2.f,
                        backBTText.getGlobalBounds().size.y / 2.f});
  backBTText.setString("Back");
  backBTText.setCharacterSize(20);
  backBTText.setFillColor(sf::Color::Black);
  backBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                          dy - dialogBg.getSize().y / 4.f + 150.f});
  // Button tag
  sf::RectangleShape tagButton({80.f, 30.f});
  tagButton.setFillColor({0, 128, 0});
  tagButton.setOrigin(
      {tagButton.getSize().x / 2.f, tagButton.getSize().y / 2.f});
  tagButton.setPosition(
      {dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
       dy - dialogBg.getSize().y / 4.f + 150.f + 100.f + 10.f});

  sf::Text tagBTText(arialFont);
  tagBTText.setOrigin({tagBTText.getGlobalBounds().size.x / 2.f,
                       tagBTText.getGlobalBounds().size.y / 2.f});
  tagBTText.setString("Tag");
  tagBTText.setCharacterSize(20);
  tagBTText.setFillColor(sf::Color::Black);
  tagBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                         dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});

  dialogBg.setScale({1.1f, 1.1f});
  int currentInput = 0;
  while (window.isOpen()) {
    while (auto opt = window.pollEvent()) {
      const auto &event = *opt;
      if (event.is<sf::Event::Closed>()) {
        window.close();
      } else if (opt->is<sf::Event::Resized>()) {
        sf::View view(
            sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
      if (auto *m = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (m->button == sf::Mouse::Button::Left) {
          auto mp = window.mapPixelToCoords({m->position.x, m->position.y});
          if (okButton.getGlobalBounds().contains(mp)) {
            string front = inputFront.toAnsiString();
            string back = inputBack.toAnsiString();
            string tag = inputTag.toAnsiString();
            // if (front == "" && back == "") {
            //   int notice = Notice("Invalid card!");
            //   edited = false;
            //   return;
            // } else {
            //   int notice = Notice("Add successfully!");
            //   edited = true;
            //   return;
            // }
            int EditPos = findCard(deck, front);
            if (EditPos == -1)
              EditPos = findCard(deck, back);
            if (EditPos == -1)
              EditPos = findCard(deck, tag);
            if (EditPos == -1) {
              // thong bao khoNG tim thaY
              int notice = Notice("Invalid card!\nEdit failed");
              return;
            } else {
              // Edit card
              // thong bao da sua
              deck[EditPos].front = front;
              deck[EditPos].back = back;
              deck[EditPos].tag = tag;
              int notice = Notice("Edit successfully!");
              return;
            }
          }
          if (frontButton.getGlobalBounds().contains(mp)) {
            currentInput = 1;
          } else if (backButton.getGlobalBounds().contains(mp)) {
            currentInput = 2;
          } else if (tagButton.getGlobalBounds().contains(mp)) {
            currentInput = 3;
          } else {
            currentInput = 0;
          }
        }
      }
      if (auto *k = event.getIf<sf::Event::KeyPressed>()) {
        if (k->code == sf::Keyboard::Key::Enter) {
          string front = inputFront.toAnsiString();
          string back = inputBack.toAnsiString();
          string tag = inputTag.toAnsiString();
          int EditPos = findCard(deck, front);
          if (EditPos == -1)
            EditPos = findCard(deck, back);
          if (EditPos == -1)
            EditPos = findCard(deck, tag);
          if (EditPos == -1) {
            // thong bao khoNG tim thaY
            int notice = Notice("Invalid card!\nEdit failed");
            return;
          } else {
            // Edit card
            // thong bao da sua
            deck[EditPos].front = front;
            deck[EditPos].back = back;
            deck[EditPos].tag = tag;
            int notice = Notice("Edit successfully!");
            return;
          }
        }
      }
      if (auto *t = event.getIf<sf::Event::TextEntered>()) {
        auto u = t->unicode;
        if (u == 8) {
          if (currentInput == 1 && !inputFront.isEmpty())
            inputFront.erase(inputFront.getSize() - 1);
          else if (currentInput == 2 && !inputBack.isEmpty())
            inputBack.erase(inputBack.getSize() - 1);
          else if (currentInput == 3 && !inputTag.isEmpty())
            inputTag.erase(inputTag.getSize() - 1);
        } else if (u >= 32 && u < 128) {
          if (currentInput == 1)
            inputFront += u;
          else if (currentInput == 2)
            inputBack += u;
          else if (currentInput == 3)
            inputTag += u;
        }

        frontText.setString(inputFront);
        backText.setString(inputBack);
        tagText.setString(inputTag);
      }
    }

    window.draw(dialogBg);
    window.draw(prompt);
    window.draw(frontBox);
    window.draw(backBox);
    window.draw(tagBox);
    if (inputFront.isEmpty()) {
      window.draw(frontPH);
    } else {
      window.draw(frontText);
    }
    if (inputBack.isEmpty()) {
      window.draw(backPH);
    } else {
      window.draw(backText);
    }
    if (inputTag.isEmpty()) {
      window.draw(tagPH);
    } else {
      window.draw(tagText);
    }
    window.draw(okButton);
    window.draw(okText);
    window.draw(frontButton);
    window.draw(frontBTText);
    window.draw(backButton);
    window.draw(backBTText);
    window.draw(tagButton);
    window.draw(tagBTText);
    window.display();
  }
}

void toDeleteCard(sf::RenderWindow &window, vector<FlashCard> &deck,
                  int &orderOfCard) {
  sf::String inputFront;
  sf::String inputBack;
  sf::String inputTag;
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);

  sf::RectangleShape dialogBg(
      sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f));
  dialogBg.setFillColor({200, 200, 200});
  float dx = (windowSize.x) * 0.5f;
  float dy = (windowSize.y) * 0.5f;
  dialogBg.setOrigin({dialogBg.getSize().x / 2.f, dialogBg.getSize().y / 2.f});
  dialogBg.setPosition({dx, dy});

  sf::Text prompt(arialFont);
  prompt.setString("DELETE CARD");
  prompt.setCharacterSize(30);
  prompt.setFillColor(sf::Color::Black);
  prompt.setOrigin({prompt.getGlobalBounds().size.x * 0.5f,
                    prompt.getGlobalBounds().size.y * 0.5f});
  prompt.setPosition({dx, dy - dialogBg.getSize().y * 0.5f + 40.f});
  prompt.setStyle(sf::Text::Bold);
  // Front box
  sf::RectangleShape frontBox({600.f, 50.f});
  frontBox.setOrigin(
      {frontBox.getSize().x / 2.f - 65.f, frontBox.getSize().y / 2.f});
  frontBox.setFillColor(sf::Color::White);
  frontBox.setOutlineColor(sf::Color::Black);
  frontBox.setOutlineThickness(1.f);
  frontBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f - 100.f});
  // Back box
  sf::RectangleShape backBox({600.f, 50.f});
  backBox.setOrigin(
      {backBox.getSize().x / 2.f - 65.f, backBox.getSize().y / 2.f});
  backBox.setFillColor(sf::Color::White);
  backBox.setOutlineColor(sf::Color::Black);
  backBox.setOutlineThickness(1.f);
  backBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f});
  // Tag box
  sf::RectangleShape tagBox({600.f, 50.f});
  tagBox.setOrigin({tagBox.getSize().x / 2.f - 65.f, tagBox.getSize().y / 2.f});
  tagBox.setFillColor(sf::Color::White);
  tagBox.setOutlineColor(sf::Color::Black);
  tagBox.setOutlineThickness(1.f);
  tagBox.setPosition({dx, dy - dialogBg.getSize().y / 4.f + 160.f + 100.f});

  // Front input text
  sf::Text frontText(arialFont);
  frontText.setOrigin({frontText.getGlobalBounds().size.x / 2.f,
                       frontText.getGlobalBounds().size.y / 2.f});
  frontText.setString("");
  frontText.setCharacterSize(20);
  frontText.setFillColor(sf::Color::Black);
  frontText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                         dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // Back input text
  sf::Text backText(arialFont);
  backText.setOrigin({backText.getGlobalBounds().size.x / 2.f,
                      backText.getGlobalBounds().size.y / 2.f});
  backText.setString("");
  backText.setCharacterSize(20);
  backText.setFillColor(sf::Color::Black);
  backText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                        dy - dialogBg.getSize().y / 4.f + 150.f});
  // Tag input text
  sf::Text tagText(arialFont);
  tagText.setOrigin({tagText.getGlobalBounds().size.x / 2.f,
                     tagText.getGlobalBounds().size.y / 2.f});
  tagText.setString("");
  tagText.setCharacterSize(20);
  tagText.setFillColor(sf::Color::Black);
  tagText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                       dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});
  // PH front
  sf::Text frontPH(arialFont);
  frontPH.setString("Front text...");
  frontPH.setCharacterSize(20);
  frontPH.setFillColor({128, 128, 128});
  frontPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                       dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // PH back
  sf::Text backPH(arialFont);
  backPH.setString("Back text...");
  backPH.setCharacterSize(20);
  backPH.setFillColor({128, 128, 128});
  backPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                      dy - dialogBg.getSize().y / 4.f + 150.f});
  // PH tag
  sf::Text tagPH(arialFont);
  tagPH.setString("Tag text...");
  tagPH.setCharacterSize(20);
  tagPH.setFillColor({128, 128, 128});
  tagPH.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f,
                     dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});
  // Button ok
  sf::RectangleShape okButton({80.f, 30.f});
  okButton.setFillColor({0, 128, 0});
  okButton.setOrigin({okButton.getSize().x / 2.f, okButton.getSize().y / 2.f});
  okButton.setPosition({dx, dy + 220.f});

  sf::Text okText(arialFont);
  okText.setOrigin({okText.getGlobalBounds().size.x / 2.f,
                    okText.getGlobalBounds().size.y / 2.f});
  okText.setString("Ok");
  okText.setCharacterSize(20);
  okText.setFillColor(sf::Color::White);
  okText.setPosition({dx - 10, dy + 205.f});
  // Button front
  sf::RectangleShape frontButton({80.f, 30.f});
  frontButton.setFillColor({0, 128, 0});
  frontButton.setOrigin(
      {frontButton.getSize().x / 2.f, frontButton.getSize().y / 2.f});
  frontButton.setPosition(
      {dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
       dy - dialogBg.getSize().y / 4.f + 150.f - 100.f + 10.f});

  sf::Text frontBTText(arialFont);
  frontBTText.setOrigin({frontBTText.getGlobalBounds().size.x / 2.f,
                         frontBTText.getGlobalBounds().size.y / 2.f});
  frontBTText.setString("Front");
  frontBTText.setCharacterSize(20);
  frontBTText.setFillColor(sf::Color::Black);
  frontBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                           dy - dialogBg.getSize().y / 4.f + 150.f - 100.f});
  // Button back
  sf::RectangleShape backButton({80.f, 30.f});
  backButton.setFillColor({0, 128, 0});
  backButton.setOrigin(
      {backButton.getSize().x / 2.f, backButton.getSize().y / 2.f});
  backButton.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
                          dy - dialogBg.getSize().y / 4.f + 150.f + 10.f});

  sf::Text backBTText(arialFont);
  backBTText.setOrigin({backBTText.getGlobalBounds().size.x / 2.f,
                        backBTText.getGlobalBounds().size.y / 2.f});
  backBTText.setString("Back");
  backBTText.setCharacterSize(20);
  backBTText.setFillColor(sf::Color::Black);
  backBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                          dy - dialogBg.getSize().y / 4.f + 150.f});
  // Button tag
  sf::RectangleShape tagButton({80.f, 30.f});
  tagButton.setFillColor({0, 128, 0});
  tagButton.setOrigin(
      {tagButton.getSize().x / 2.f, tagButton.getSize().y / 2.f});
  tagButton.setPosition(
      {dx - dialogBg.getSize().x / 2.f + 250.f - 65.f,
       dy - dialogBg.getSize().y / 4.f + 150.f + 100.f + 10.f});

  sf::Text tagBTText(arialFont);
  tagBTText.setOrigin({tagBTText.getGlobalBounds().size.x / 2.f,
                       tagBTText.getGlobalBounds().size.y / 2.f});
  tagBTText.setString("Tag");
  tagBTText.setCharacterSize(20);
  tagBTText.setFillColor(sf::Color::Black);
  tagBTText.setPosition({dx - dialogBg.getSize().x / 2.f + 250.f - 85.f,
                         dy - dialogBg.getSize().y / 4.f + 150.f + 100.f});

  dialogBg.setScale({1.1f, 1.1f});
  int currentInput = 0;
  while (window.isOpen()) {
    while (auto opt = window.pollEvent()) {
      const auto &event = *opt;
      if (event.is<sf::Event::Closed>()) {
        window.close();
      } else if (opt->is<sf::Event::Resized>()) {
        sf::View view(
            sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
        window.setView(view);
      }
      if (auto *m = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (m->button == sf::Mouse::Button::Left) {
          auto mp = window.mapPixelToCoords({m->position.x, m->position.y});
          if (okButton.getGlobalBounds().contains(mp)) {
            string front = inputFront.toAnsiString();
            string back = inputBack.toAnsiString();
            string tag = inputTag.toAnsiString();

            int DeletePos = findCard(deck, front);
            if (DeletePos == -1)
              DeletePos = findCard(deck, back);
            if (DeletePos == -1)
              DeletePos = findCard(deck, tag);
            if (DeletePos == -1) {
              // thong bao khoNG tim thaY
              int notice = Notice("Invalid card!\nDelete failed");
              return;
            } else {
              // Edit card
              // thong bao da xoa
              deck.erase(deck.begin() + DeletePos);
              if (deck.size() <= orderOfCard)
                orderOfCard = 0;
              int notice = Notice("Delete successfully!");
              return;
            }
          }
          if (frontButton.getGlobalBounds().contains(mp)) {
            currentInput = 1;
          } else if (backButton.getGlobalBounds().contains(mp)) {
            currentInput = 2;
          } else if (tagButton.getGlobalBounds().contains(mp)) {
            currentInput = 3;
          } else {
            currentInput = 0;
          }
        }
      }
      if (auto *k = event.getIf<sf::Event::KeyPressed>()) {
        if (k->code == sf::Keyboard::Key::Enter) {
          string front = inputFront.toAnsiString();
          string back = inputBack.toAnsiString();
          string tag = inputTag.toAnsiString();

          int DeletePos = findCard(deck, front);
          if (DeletePos == -1)
            DeletePos = findCard(deck, back);
          if (DeletePos == -1)
            DeletePos = findCard(deck, tag);
          if (DeletePos == -1) {
            // thong bao khoNG tim thaY
            int notice = Notice("Invalid card!\nDelete failed");
            return;
          } else {
            // Edit card
            // thong bao da xoa
            deck.erase(deck.begin() + DeletePos);
            if (deck.size() <= orderOfCard)
              orderOfCard = 0;
            int notice = Notice("Delete successfully!");
            return;
          }
        }
      }
      if (auto *t = event.getIf<sf::Event::TextEntered>()) {
        auto u = t->unicode;
        if (u == 8) {
          if (currentInput == 1 && !inputFront.isEmpty())
            inputFront.erase(inputFront.getSize() - 1);
          else if (currentInput == 2 && !inputBack.isEmpty())
            inputBack.erase(inputBack.getSize() - 1);
          else if (currentInput == 3 && !inputTag.isEmpty())
            inputTag.erase(inputTag.getSize() - 1);
        } else if (u >= 32 && u < 128) {
          if (currentInput == 1)
            inputFront += u;
          else if (currentInput == 2)
            inputBack += u;
          else if (currentInput == 3)
            inputTag += u;
        }

        frontText.setString(inputFront);
        backText.setString(inputBack);
        tagText.setString(inputTag);
      }
    }

    window.draw(dialogBg);
    window.draw(prompt);
    window.draw(frontBox);
    window.draw(backBox);
    window.draw(tagBox);
    if (inputFront.isEmpty()) {
      window.draw(frontPH);
    } else {
      window.draw(frontText);
    }
    if (inputBack.isEmpty()) {
      window.draw(backPH);
    } else {
      window.draw(backText);
    }
    if (inputTag.isEmpty()) {
      window.draw(tagPH);
    } else {
      window.draw(tagText);
    }
    window.draw(okButton);
    window.draw(okText);
    window.draw(frontButton);
    window.draw(frontBTText);
    window.draw(backButton);
    window.draw(backBTText);
    window.draw(tagButton);
    window.draw(tagBTText);
    window.display();
  }
}

void FCEvents(sf::RenderWindow &window, Button FCButtons[],
              appState &currentState, sf::Vector2f &mousePosition,
              CardBox &cardBox, int &orderOfCard, int &displayEF) {
  while (std::optional event = window.pollEvent()) {
    // when button close is clicked
    if (event->is<sf::Event::Closed>()) {
      // close window and exit program
      window.close();
    }
    // when window is resized
    else if (event->is<sf::Event::Resized>()) {
      // update view

      sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
      window.setView(view);
    }
    // when button is pressed
    else if (auto *mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
      // Left button mouse
      // if (mouse->button == sf::Mouse::Button::Left) {

      // }
      for (int i = 0; i <= 12; i++) {
        if (FCButtons[i].isPressed(mousePosition)) {
          if (i == 9) {
            currentState = appState::Start;
          }
          if (i == 0) { // add
            FlashCard card;
            bool added = false;
            toAddNewCard(window, card.front, card.back, card.tag, added);
            if (added == true) {
              cardBox.deck.push_back(card);
            }
          } else if (i == 1) { // edit
            toEditCard(window, cardBox.deck);
          } else if (i == 2) { // delete
            toDeleteCard(window, cardBox.deck, orderOfCard);
          } else if (i == 3) { // <
            if (orderOfCard > 0) {
              orderOfCard--;
              displayEF = cardBox.deck[orderOfCard].easyFactor;
            }
          } else if (i == 4) { // >
            if (orderOfCard < cardBox.deck.size() - 1) {
              orderOfCard++;
              displayEF = cardBox.deck[orderOfCard].easyFactor;
            }
          } else if (i == 5) { // Easy
            if (displayEF <= 0) {
              cardBox.deck[orderOfCard].easyFactor = 1;
              displayEF = 1;
            } else {
              cardBox.deck[orderOfCard].easyFactor = 0;
              displayEF = -1;
            }
          } else if (i == 6) { // Normal
            if (displayEF <= 0) {
              cardBox.deck[orderOfCard].easyFactor = 2;
              displayEF = 2;
            } else {
              cardBox.deck[orderOfCard].easyFactor = 0;
              displayEF = -1;
            }
          } else if (i == 7) { // Hard
            if (displayEF <= 0) {
              cardBox.deck[orderOfCard].easyFactor = 3;
              displayEF = 3;
            } else {
              cardBox.deck[orderOfCard].easyFactor = 0;
              displayEF = -1;
            }
          } else if (i == 8) { // Insane
            if (displayEF <= 0) {
              cardBox.deck[orderOfCard].easyFactor = 4;
              displayEF = 4;
            } else {
              cardBox.deck[orderOfCard].easyFactor = 0;
              displayEF = -1;
            }
          } else if (i == 11) {
            int notice = Notice("Delete this card!\n");
            if (notice == 1) {
              int DeletePos = findCardToDelete(cardBox.deck,
                                               cardBox.deck[orderOfCard].front,
                                               cardBox.deck[orderOfCard].back,
                                               cardBox.deck[orderOfCard].tag);
              if (DeletePos != -1) {
                cardBox.deck.erase(cardBox.deck.begin() + DeletePos);
                if (cardBox.deck.size() <= orderOfCard)
                  orderOfCard = 0;
                int not1 = Notice("Deleted!");
              } else
                int not1 = Notice("Card not found!");
            } else if (notice == 2) {
              int notice = Notice("Delete failed!");
            }
          } else if (i == 12) {
            int notice = Notice("Save this card to json file!\n");
            if (notice == 1) {
              // Save
              int notice1 = Notice("Saved successfully!\n");
            } else if (notice == 2) {
              int notice1 = Notice("Save failed!\n");
            }
          }
        }
      }
    } else if (auto *mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
      if (FCButtons[10].rectangleShape.getGlobalBounds().contains(
              mousePosition) &&
          mouse->button == sf::Mouse::Button::Left) {
        cardBox.deck[orderOfCard].isBack = !cardBox.deck[orderOfCard].isBack;
      }
    }
  }
}
// Home render
void HomeRender(sf::RenderWindow &window, appState &currentState,
                vector<DeckBox> &DeckBoxes) {

  sf::Vector2f buttonSize(window.getSize().x * 0.4f,
                          window.getSize().y * 0.15f);
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
  sf::Vector2f mousePosition =
      window.mapPixelToCoords(sf::Mouse::getPosition(window));

  Button HomeButtons[] = {
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f,
                          windowSize.y / 2.f - buttonSize.y * 1.5f - 40.f),
             "START", 36),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f,
                          windowSize.y / 2.f - buttonSize.y * 0.5f - 20.f),
             "SETTING", 36),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f,
                          windowSize.y / 2.f + buttonSize.y * 0.5f),
             "LOAD", 36),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f,
                          windowSize.y / 2.f + buttonSize.y * 1.5f + 20.f),
             "QUIT", 36)};

  for (auto &button : HomeButtons) {
    button.hovering(mousePosition, {135, 206, 250}, {1.2f, 1.2f});
  }

  // Display Home Render
  window.clear();
  gradientBackground(window);
  for (auto &button : HomeButtons) {
    button.draw(window);
  }
  // Home Events
  HomeEvents(window, HomeButtons, currentState, mousePosition, DeckBoxes);

  window.display();
}
// Start render
void StartRender(sf::RenderWindow &window, appState &currentState,
                 vector<DeckBox> &DeckBoxes) {
  sf::Vector2f buttonSize(window.getSize().x * 0.18f,
                          window.getSize().y * 0.1f);
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
  sf::Vector2f mousePosition =
      window.mapPixelToCoords(sf::Mouse::getPosition(window));
  string mode;
  if (DeckBoxes.size() == 0)
    mode = "CREATE A DECK NOW";
  else
    mode = "ALL YOUR DECK HERE";
  Button StartButtons[] = {
      // windowSize.x / 2.f, windowSize.y / 5.f
      Button(sf::Vector2f(windowSize.x * 0.8f, windowSize.y),
             sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f), mode, 40,
             {245, 248, 252}, {0, 0, 0}),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f - buttonSize.x - 20.f,
                          windowSize.y / 2.f + windowSize.y / 3.f + 30.f),
             "CREATE", 24),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f,
                          windowSize.y / 2.f + windowSize.y / 3.f + 30.f),
             "REVIEW", 24),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f + buttonSize.x + 20.f,
                          windowSize.y / 2.f + windowSize.y / 3.f + 30.f),
             "HOME", 24)};
  // Edit Board (StartButtons[0])
  StartButtons[0].notHover = true;
  sf::Vector2f mainPosition = StartButtons[0].labelText.getPosition();
  StartButtons[0].labelText.setPosition({mainPosition.x, mainPosition.y / 4});
  StartButtons[0].labelText.setStyle(sf::Text::Bold);

  for (auto &button : StartButtons) {
    button.hovering(mousePosition, {135, 206, 250}, {1.1f, 1.1f});
  }
  for (auto &deck : DeckBoxes) {
    deck.hovering(mousePosition, {135, 206, 250}, {1.1f, 1.1f});
  }
  window.clear();
  gradientBackground(window);
  for (auto &button : StartButtons) {
    button.draw(window);
  }

  for (auto &deck : DeckBoxes) {
    deck.draw(window);
  }
  updateDeck(window, DeckBoxes);

  // Start Events
  StartEvents(window, StartButtons, currentState, mousePosition, DeckBoxes);
  window.display();
}
// Setting render
void SettingRender(sf::RenderWindow &window, appState &currentState) {
  int result = UpdateMessage();
  if (result == IDOK || result == IDCANCEL) {
    currentState = appState::Home;
  }
}
// Create render
void CreateRender(sf::RenderWindow &window, appState &currentState,
                  vector<DeckBox> &DeckBoxes) {
  sf::String res = getUserInput(window, arialFont);
  currentState = appState::Start;
  if (DeckBoxes.size() == 10) {
    int notice = Notice("You've reached the maximum number of decks.");
    return;
  }
  if (res == "") {
    int notice = Notice("Invalid deck!");
    return;
  }
  sf::Vector2f buttonSize(window.getSize().x * 0.6f,
                          window.getSize().y * 0.05f);
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
  DeckBox deck1(buttonSize,
                sf::Vector2f(windowSize.x / 2.f,
                             windowSize.y / 4.115 +
                                 window.getSize().y * 0.06f *
                                     static_cast<float>(DeckBoxes.size()) -
                                 10.f),
                res, 20);
  DeckBoxes.push_back(deck1);
}
// Statistic render
void StatisticRender(sf::RenderWindow &window, appState &currentState) {
  int result = UpdateMessage();
  if (result == IDOK || result == IDCANCEL) {
    currentState = appState::Start;
  }
}
// Flashcard display
void FlashCardDisplay(sf::RenderWindow &window, appState &currentState,
                      DeckBox &Deck, CardBox &cardDefault) {
  sf::Vector2f buttonSize(window.getSize().x * 0.18f,
                          window.getSize().y * 0.1f);
  sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
  sf::Vector2f mousePosition =
      window.mapPixelToCoords(sf::Mouse::getPosition(window));

  Button FCButtons[] = {
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f - buttonSize.x - 20.f,
                          windowSize.y / 2.f + windowSize.y / 3.f + 30.f),
             "ADD", 24),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f,
                          windowSize.y / 2.f + windowSize.y / 3.f + 30.f),
             "EDIT", 24),
      Button(buttonSize,
             sf::Vector2f(windowSize.x / 2.f + buttonSize.x + 20.f,
                          windowSize.y / 2.f + windowSize.y / 3.f + 30.f),
             "DELETE", 24),
      Button(
          sf::Vector2f(window.getSize().x * 0.05f, window.getSize().y * 0.15f),
          sf::Vector2f(windowSize.x / 2.f - windowSize.x * 0.375f,
                       windowSize.y / 2.f - 60.f),
          "<", 30),
      Button(
          sf::Vector2f(window.getSize().x * 0.05f, window.getSize().y * 0.15f),
          sf::Vector2f(windowSize.x / 2.f + windowSize.x * 0.375f,
                       windowSize.y / 2.f - 60.f),
          ">", 30),
      Button(
          sf::Vector2f(window.getSize().x * 0.075f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x / 2.f - buttonSize.x * 0.75f,
                       windowSize.y * 0.65f),
          "EASY", 30),
      Button(
          sf::Vector2f(window.getSize().x * 0.075f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x / 2.f - buttonSize.x * 0.25f,
                       windowSize.y * 0.65f),
          "NORMAL", 30),
      Button(
          sf::Vector2f(window.getSize().x * 0.075f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x / 2.f + buttonSize.x * 0.25f,
                       windowSize.y * 0.65f),
          "HARD", 30),
      Button(
          sf::Vector2f(window.getSize().x * 0.075f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x / 2.f + buttonSize.x * 0.75f,
                       windowSize.y * 0.65f),
          "INSANE", 30),
      Button(
          sf::Vector2f(window.getSize().x * 0.05f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x * 0.075f, windowSize.y * 0.875f), "START",
          24),
      Button(
          sf::Vector2f(window.getSize().x * 0.05f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x * 0.25f, windowSize.y * 0.25f), "FLIP", 24),
      Button(
          sf::Vector2f(window.getSize().x * 0.05f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x * 0.25f, windowSize.y * 0.5f), "DEL", 24),
      Button(
          sf::Vector2f(window.getSize().x * 0.05f, window.getSize().y * 0.05f),
          sf::Vector2f(windowSize.x * 0.25f, windowSize.y * 0.75f), "SAVE",
          24)};

  string nameDeck = Deck.labelText.getString().toAnsiString();
  // Title deck to show name and number of card in deck, no changes with the
  // origin deckBox (in Start Mode)
  DeckBox TitleDeck(
      sf::Vector2f(window.getSize().x * 0.6f, window.getSize().y * 0.05f),
      sf::Vector2f(windowSize.x / 2.f, windowSize.y * 0.1f), nameDeck, 30,
      sf::Color(255, 255, 255, 0), sf::Color::Black);
  TitleDeck.labelText.setStyle(sf::Text::Bold);
  TitleDeck.rectBox.setOutlineThickness(0);

  CardBox cardBox = cardDefault;
  cardBox.deck = Deck.deck;
  cardBox.rectBox.setOrigin(
      sf::Vector2f(window.getSize().x * 0.325f, window.getSize().y * 0.275f));
  cardBox.rectBox.setSize(
      sf::Vector2f(window.getSize().x * 0.65f, window.getSize().y * 0.55f));
  cardBox.rectBox.setPosition(
      sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f - 60.f));
  sf::FloatRect textBounds1 = cardBox.content.getLocalBounds();
  cardBox.content.setOrigin(
      {textBounds1.position.x + textBounds1.size.x / 2.f,
       textBounds1.position.y + textBounds1.size.y / 2.f});
  cardBox.content.setPosition(
      sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f - 120.f));
  cardBox.content.setFillColor(sf::Color::Black);

  sf::FloatRect textBounds = cardBox.note.getLocalBounds();
  cardBox.note.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                          textBounds.position.y + textBounds.size.y / 2.f});
  cardBox.note.setPosition(
      sf::Vector2f(windowSize.x * 0.8f - 20.f, windowSize.y / 3.f - 100.f));
  cardBox.note.setFillColor(sf::Color::Black);
  cardBox.note.setCharacterSize(30);
  cardBox.note.setStyle(sf::Text::Bold);

  for (auto &button : FCButtons) {
    button.hovering(mousePosition, {135, 206, 250}, {1.1f, 1.1f});
  }

  static int orderOfCard = 0;
  static int displayEF = -1;
  sf::Text stateFlip(arialFont);
  stateFlip.setOrigin({stateFlip.getGlobalBounds().size.x * 0.5f,
                       stateFlip.getGlobalBounds().size.y * 0.5f});
  stateFlip.setFillColor(sf::Color::Black);
  stateFlip.setStyle(sf::Text::Bold);
  stateFlip.setCharacterSize(24);
  stateFlip.setPosition(
      sf::Vector2f(window.getSize().x * 0.3, windowSize.y * 0.25f));

  TitleDeck.deck = cardBox.deck;
  // Deck.deck = cardBox.deck;
  string numDeck = to_string(cardBox.deck.size());
  TitleDeck.numCard.setString(numDeck);
  Deck.numCard.setString(numDeck);
  cardBox.note.setString(to_string(orderOfCard + 1));

  window.clear();
  gradientBackground(window);

  if (cardBox.deck.size() == 0) {
    cardBox.content.setString("No card existed!\nPlease add a card now!");
    for (int i = 0; i <= 12; i++) {
      if (i == 0 || i == 1 || i == 2 || i == 9) {
        FCButtons[i].draw(window);
      }
    }
    window.draw(cardBox.content);
  } else {
    if (cardBox.deck[orderOfCard].isBack == false) {
      stateFlip.setString("FRONT");
      cardBox.content.setString(cardBox.deck[orderOfCard].front);
    } else {
      stateFlip.setString("BACK");
      cardBox.content.setString(cardBox.deck[orderOfCard].back);
    }
    cardBox.content.setCharacterSize(30);
    cardBox.content.setStyle(sf::Text::Bold);

    cardBox.draw(window);
    for (int i = 0; i <= 12; i++) {
      if (i != 5 && i != 6 && i != 7 && i != 8) {
        FCButtons[i].draw(window);
      }
      if (displayEF <= 0) {
        FCButtons[i].draw(window);
      } else {
        if (i == displayEF + 4) {
          FCButtons[i].rectangleShape.setFillColor(sf::Color::Black);
          FCButtons[i].draw(window);
        }
      }
    }
  }
  TitleDeck.draw(window);
  window.draw(stateFlip);

  // Events
  FCEvents(window, FCButtons, currentState, mousePosition, cardBox, orderOfCard,
           displayEF);

  Deck.deck = cardBox.deck;
  cardDefault = cardBox;
  window.display();
}
// handle event appropriate with state
void handleEvents(sf::RenderWindow &window, appState &currentState,
                  vector<DeckBox> &DeckBoxes, CardBox &cardBox) {
  int result = 0;
  bool isFront = true;
  switch (currentState) {
  case appState::Home:
    HomeRender(window, currentState, DeckBoxes);
    break;
  case appState::Start:
    StartRender(window, currentState, DeckBoxes);
    break;
  case appState::Setting:
    SettingRender(window, currentState);
    break;
  case appState::Create:
    CreateRender(window, currentState, DeckBoxes);
    break;
  case appState::Statistic:
    StatisticRender(window, currentState);
    break;
  case appState::Display:
    FlashCardDisplay(window, currentState, DeckBoxes[whatDeck], cardBox);
    break;
  default:
    HomeRender(window, currentState, DeckBoxes);
    break;
  }
}

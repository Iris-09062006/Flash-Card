<<<<<<< HEAD

// Created by chill code on 28/04/2025,
// Last Modified: 09:11 PM 01/06/2025 
// Copyright © 2025 chill code. All rights reserved.

#include "../include/FlashCard.h"
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;
void toJson(json &j, FlashCard card) {
  j = {{"front", card.front},
       {"back", card.back},
       {"tag", card.tag},
       {"easyFactor", card.easyFactor},
       {"interval", card.interval},
       {"repetitions", card.repetitions},
       {"lastDateReview", card.lastDateReview}};
}

void fromJson(json j, FlashCard &card) {
  card.front = j.at("front");
  card.back = j.at("back");
  card.tag = j.at("tag");
  card.easyFactor = j.at("easyFactor");
  card.interval = j.at("interval");
  card.repetitions = j.at("repetitions");
  card.lastDateReview = j.at("lastDateReview");
  card.isBack = false;
}

vector<FlashCard> LoadDeck() {
  vector<FlashCard> deck;
  ifstream inFile;
  inFile.open("data/FlashCard.json");
  if (!inFile.is_open()) {
    cout << "Khong mo duoc file!\n";
    return deck;
  }
  json j;
  inFile >> j;
  FlashCard card;
  std::cout << j.size();
  for (int i = 0; i < j.size(); i++) {
    fromJson(j[i], card);
    deck.push_back(card);
  }

  inFile.close();
  return deck;
}

void SaveDeck(vector<FlashCard> &deck) {
  ofstream outFile("../data/FlashCard.json");
  json j = json::array();
  for (const auto card : deck) {
    json item;
    toJson(item, card);
    j.push_back(item);
  }
  outFile << j.dump(4);
  outFile.close();
}

void AddCard() {
  vector<FlashCard> deck = LoadDeck();
  FlashCard card;
  cout << "Nhập mặt trước: ";
  getline(cin, card.front);
  cout << "Nhập mặt sau: ";
  getline(cin, card.back);
  cout << "Nhập tag: ";
  getline(cin, card.tag);

  card.easyFactor = 2.5;
  card.interval = 1;
  card.repetitions = 0;

  deck.push_back(card);
  SaveDeck(deck);
}

void DeleteCard() {
  vector<FlashCard> deck = LoadDeck();
  string keyword;
  cout << "Nhập nội dung mặt trước cần xóa: ";
  getline(cin, keyword);
  bool found = false;
  for (int i = 0; i < deck.size(); i++) {
    if (deck[i].front == keyword) {
      deck.erase(deck.begin() + i);
      found = true;
      break;
    }
  }
  SaveDeck(deck);
  if (found) {
    cout << "Đã xóa thẻ: " << keyword << endl;
  } else {
    cout << "Không tìm thấy thẻ cần xóa.\n";
  }
}
// chinh sua lai the neu muon
void EditCard(FlashCard &card, string choice) {
  if (choice == "front") {
    getline(cin, card.front);
  } else if (choice == "back") {
    getline(cin, card.back);
  }
}

// thuat toan lap lai ngan quang
void SM2(FlashCard &card, int quality) {
  // xu ly EF
  if (card.easyFactor < 1.3) {
    card.easyFactor = 1.3;
  } else {
    card.easyFactor =
        card.easyFactor + (0.1 - (5 - quality) * (0.08 + (5 - quality) * 0.02));
  }
  // xu ly ngay lap lai
  if (card.repetitions == 0) {
    card.interval = 1;
  } else if (card.repetitions == 1) {
    card.interval = 6;
  } else {
    card.interval = card.interval * card.easyFactor;
    card.interval = min(card.interval, 365);
  }
  // xu ly so lan lap lai
  if (quality > 3) {
    card.repetitions += 1;
  } else {
    card.repetitions = 0;
    card.interval = 1;
  }
}
=======
#include "../include/CardTree.h"
#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;
void toJson(json& j, FlashCard card) {
    j = {
        {"front", card.front},
        {"back", card.back},
        {"tag", card.tag},
        {"easyFactor", card.easyFactor},
        {"interval", card.interval},
        {"repetitions", card.repetitions},
        {"lastDateReview", card.lastDateReview}
    };
}

void fromJson(json j, FlashCard& card) {
    card.front = j.at("front");
    card.back = j.at("back");
    card.tag = j.at("tag");
    card.easyFactor = j.at("easyFactor");
    card.interval = j.at("interval");
    card.repetitions = j.at("repetitions");
    card.lastDateReview = j.at("lastDateReview");
}

vector <FlashCard> LoadDeck() {
    vector <FlashCard> deck;
    ifstream inFile("../data/FlashCard.json");
    if (!inFile.is_open()) {
        cout << "Khong mo duoc file!\n";
    }
    json j;
    inFile >> j;
    for (int i = 0; i < j.size(); i++) {
        FlashCard card;
        fromJson(j[i], card);
        deck.push_back(card);
    }
    return deck;
    inFile.close();
}
void SaveDeck(vector<FlashCard> &deck) {
    ofstream outFile("../data/FlashCard.json");
    json j = json::array();
    for (const auto card : deck) {
        json item;
        toJson(item, card);
        j.push_back(item);
    }
    outFile << j.dump(4);
    outFile.close();
}
void AddCard() {
    vector<FlashCard> deck = LoadDeck();
    FlashCard card;
    cout << "Nhập mặt trước: ";
    getline(cin, card.front);
    cout << "Nhập mặt sau: ";
    getline(cin, card.back);
    cout << "Nhập tag: ";
    getline(cin, card.tag);

    card.easyFactor = 2.5;
    card.interval = 1;
    card.repetitions = 0;

    deck.push_back(card);
    SaveDeck(deck);
}
// tim kiem + delete
void DeleteCard() {
    vector<FlashCard> deck = LoadDeck();
    string keyword;
    cout << "Nhập nội dung mặt trước cần xóa: ";
    getline(cin, keyword);
    bool found = false;
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].front == keyword) {
            deck.erase(deck.begin()+i);
            found = true;
            break;
        }
    }
    SaveDeck(deck);
    if(found) {
        cout << "Đã xóa thẻ: " << keyword << endl;
    }
    else {
        cout << "Không tìm thấy thẻ cần xóa.\n";
    }
}
// chinh sua lai the neu muon
void EditCard(FlashCard& card, string choice){
    if(choice == "front"){
        getline(cin,card.front);
    }
    else if(choice == "back"){
        getline(cin,card.back);
    }    
}

int getHeight(CardNode *&node){
    if(node == NULL) return 0;
    return 1 + max(getHeight(node->pLeft), getHeight(node->pRight));
}
int balanceFactor(CardNode *&node){
    return getHeight(node->pLeft) - getHeight(node->pRight);
}
CardNode *findMin(CardNode *node){
    if(node == NULL) return node;
    return findMin(node->pLeft);
}
CardNode *leftRotation(CardNode *node){
    CardNode* alternode = node->pRight;
    CardNode* tmpnode = alternode->pLeft;
    alternode->pLeft = node;
    node->pRight = tmpnode;
    return alternode; 
}
CardNode *rightRotation(CardNode *node){
    CardNode* alternode = node->pLeft;
    CardNode* tmpnode = alternode->pRight;
    alternode->pRight = node;
    node->pLeft =   tmpnode;
    return alternode;
}
CardNode *searchCard(CardNode* node, FlashCard &value){
    if(node == NULL) return NULL;
    if(node->fl.front > value.front){
        searchCard(node->pLeft, value);
    }
    else if(node->fl.front < value.front){
        searchCard(node->pRight, value);
    }
    else{
        return node;
    }
}
CardNode *insertCard(CardNode* node, FlashCard &value){
    if(node == NULL) return new CardNode(value);
    if(node->fl.front > value.front){
        node->pLeft = insertCard(node->pLeft, value);
    }
    else if(node->fl.front < value.front){
        node->pRight = insertCard(node->pRight, value);
    }
    int balance = balanceFactor(node);
    if(balance > 1 && node->pLeft->fl.front > value.front){
        return rightRotation(node);
    }
    else if(balance > 1 && node->pLeft->fl.front < value.front){
        node->pLeft = leftRotation(node->pLeft);
        return rightRotation(node);
    }
    else if(balance < -1 && node->pRight->fl.front < value.front){
        return leftRotation(node);
    }
    else if(balance < -1 && node->pRight->fl.front > value.front){
        node->pRight = rightRotation(node->pRight);
        return leftRotation(node);
    }
    return node;
}
CardNode *deleteCard(CardNode* node, FlashCard &value) {
    if (node == NULL) return node;

    if (node->fl.front > value.front) {
        node->pLeft = deleteCard(node->pLeft, value);
    } else if (node->fl.front < value.front) {
        node->pRight = deleteCard(node->pRight, value);
    } else {
        if (node->pLeft == NULL) {
            CardNode* tmp = node->pRight;
            delete node;
            return tmp;
        } else if (node->pRight == NULL) {
            CardNode* tmp = node->pLeft;
            delete node;
            return tmp;
        } else {
            CardNode* tmp = findMin(node->pRight);
            node->fl = tmp->fl;
            node->pRight = deleteCard(node->pRight, tmp->fl);
        }
    }

    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->pLeft) >= 0) {
        return rightRotation(node);
    } else if (balance > 1 && balanceFactor(node->pLeft) < 0) {
        node->pLeft = leftRotation(node->pLeft);
        return rightRotation(node);
    } else if (balance < -1 && balanceFactor(node->pRight) <= 0) {
        return leftRotation(node);
    } else if (balance < -1 && balanceFactor(node->pRight) > 0) {
        node->pRight = rightRotation(node->pRight);
        return leftRotation(node);
    }

    return node;
}
//thuat toan lap lai ngan quang
void SM2(FlashCard& card, int quality){
    // xu ly EF
    if(card.easyFactor < 1.3){
        card.easyFactor = 1.3;
    }
    else{ 
    card.easyFactor = card.easyFactor + (0.1 - (5 - quality)*(0.08 + (5 - quality) * 0.02));
    }
    // xu ly ngay lap lai
    if(card.repetitions == 0){
        card.interval = 1;
    }
    else if(card.repetitions == 1){
        card.interval = 6;
    }
    else{
        card.interval = card.interval * card.easyFactor;
        card.interval = min(card.interval, 365);
    }
    // xu ly so lan lap lai
    if(quality > 3){
        card.repetitions += 1;
    }
    else{
        card.repetitions = 0;
        card.interval = 1;
    }
} 
int main() {
    CardTree tree;
    int choice;
    do {
        cout << "CardTree Menu:\n";
        cout << "1. Insert a card\n";
        cout << "2. Delete a card\n";
        cout << "3. Search for a card\n";
        cout << "4. Display tree height\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1: {
                FlashCard card;
                cout << "Enter front: ";
                getline(cin, card.front);
                cout << "Enter back: ";
                getline(cin, card.back);
                cout << "Enter tag: ";
                getline(cin, card.tag);
                card.easyFactor = 2.5;
                card.interval = 1;
                card.repetitions = 0;
                tree.root = insertCard(tree.root, card);
                cout << "Card inserted successfully.\n";
                break;
            }
            case 2: {
                string front;
                cout << "Enter the front of the card to delete: ";
                getline(cin, front);
                FlashCard cardToDelete;
                cardToDelete.front = front;
                tree.root = deleteCard(tree.root, cardToDelete);
                cout << "Card deleted successfully (if it existed).\n";
                break;
            }
            case 3: {
                string front;
                cout << "Enter the front of the card to search: ";
                getline(cin, front);
                FlashCard cardToSearch;
                cardToSearch.front = front;
                CardNode* result = searchCard(tree.root, cardToSearch);
                if (result) {
                    cout << "Card found:\n";
                    cout << "Front: " << result->fl.front << "\n";
                    cout << "Back: " << result->fl.back << "\n";
                    cout << "Tag: " << result->fl.tag << "\n";
                } else {
                    cout << "Card not found.\n";
                }
                break;
            }
            case 4: {
                int height = getHeight(tree.root);
                cout << "Tree height: " << height << "\n";
                break;
            }
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
// sort
// search and delete
// show time to review 
// init
// uu tien theo do kho 
// neu rate la 1 thi cho tra loi lai lan nua
//g++ FlashCard.cpp -o FlashCard -I../include
>>>>>>> cb672f573b6bcec0f193885a5cc1979d8b8ab6d5

#include "../include/FlashCard.h"
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
    int choice;
    do {
        cout << "FlashCard Menu:\n";
        cout << "1. Add a new card\n";
        cout << "2. Delete a card\n";
        cout << "3. Edit a card\n";
        cout << "4. Review cards\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1:
                AddCard();
                break;
            case 2:
                DeleteCard();
                break;
            case 3: {
                vector<FlashCard> deck = LoadDeck();
                string keyword;
                cout << "Enter the front of the card to edit: ";
                getline(cin, keyword);
                bool found = false;
                for (auto& card : deck) {
                    if (card.front == keyword) {
                        found = true;
                        string field;
                        cout << "Enter the field to edit (front/back): ";
                        cin >> field;
                        cin.ignore(); // Clear the input buffer
                        EditCard(card, field);
                        SaveDeck(deck);
                        cout << "Card updated successfully.\n";
                        break;
                    }
                }
                if (!found) {
                    cout << "Card not found.\n";
                }
                break;
            }
            case 4: {
                vector<FlashCard> deck = LoadDeck();
                for (auto& card : deck) {
                    cout << "Front: " << card.front << "\n";
                    cout << "Back: " << card.back << "\n";
                    cout << "Rate your recall (0-5): ";
                    int quality;
                    cin >> quality;
                    cin.ignore(); // Clear the input buffer
                    SM2(card, quality);
                }
                SaveDeck(deck);
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
//g++ FlashCard.cpp -o FlashCard -I../include
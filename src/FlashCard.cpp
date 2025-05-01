#include "../include/FlashCard.h"
#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

// chinh sua lai the neu muon
void EditCard(FlashCard& card, string choice){
    if(choice == "front"){
        cin >> card.front;
    }
    else if(choice == "back"){
        cin >> card.back;
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
    if(card.repitions == 0){
        card.interval = 1;
    }
    else if(card.repitions == 1){
        card.interval = 6;
    }
    else{
        card.interval = card.interval * card.easyFactor;
        card.interval = min(card.interval, 365);
    }
    // xu ly so lan lap lai
    if(quality > 3){
        card.repitions += 1;
    }
    else{
        card.repitions = 0;
        card.interval = 1;
    }
}
// luu card
void SaveDeck(vector<FlashCard>& deck){
    ofstream Fout("FlashCard.json");
    json j;
    for(auto &card : deck){
        json json_card;
        json_card["front"] = card.front;
        json_card["back"] = card.back;
        json_card["tag"] = card.tag;
        json_card["easyFactor"] = card.easyFactor;
        json_card["interval"] = card.interval;
        json_card["repitions"] = card.repitions;
        json_card["lastDateReview"] = card.lastDateReview;
        j.push_back(json_card);
    }
    Fout<<j.dump(4);
    Fout.close();
}

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
};
void InitializeDeck(); // khoi tao 1 deck moi hoan toan
vector<FlashCard> LoadDeck(); // tai len bo the da luu
void AddCard(); // them the vao bo the
void DeleteCard();// xoa the 




void EditCard(FlashCard& card, string choice);// chinh sua lai the neu muon
void SM2(FlashCard& card, int quality);// thuat toan lap lai ngat quang
void SaveDeck(vector<FlashCard>& deck);// luu card
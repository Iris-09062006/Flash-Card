#include "FlashCard.h"
class CardNode{
    public:
    FlashCard fl;
    CardNode *pLeft;
    CardNode *pRight;
    CardNode(){
        pLeft = NULL;
        pRight = NULL;
    }
    CardNode(FlashCard &c) : fl(c), pLeft(NULL), pRight(NULL){}
    CardNode(CardNode& n) :fl(n.fl), pLeft(NULL), pRight(NULL){
        if(pLeft){
            pLeft = new CardNode(*n.pLeft);
        }
        if(pRight){
            pRight = new CardNode(*n.pRight);
        }
    }
    ~CardNode(){
        cout << "delete Card" << endl;
        delete pLeft;
        delete pRight;
    }
};
class CardTree : public CardNode {
    private:
    int balanceFactor(CardNode* &node);
    int getHeight(CardNode* &node);
    CardNode *leftRotation(CardNode* node);
    CardNode *rightRotation(CardNode* node);
    CardNode *findMin(CardNode* node);
    public:
    CardNode* root = NULL;
    CardNode *insertCard(CardNode* node, FlashCard &value);
    CardNode *deleteCard(CardNode* node, FlashCard &value);
    CardNode *searchCard(CardNode* node, FlashCard &value) const;
};

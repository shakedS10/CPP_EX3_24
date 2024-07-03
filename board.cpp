#include "board.hpp"
using namespace std;
const std::string ANSI_RESET = "\033[0m";
const std::string ANSI_RED = "\033[31m";
const std::string ANSI_GREEN = "\033[32m";
const std::string ANSI_YELLOW = "\033[33m";
const std::string ANSI_BLUE = "\033[34m";
const std::string ANSI_MAGENTA = "\033[35m";
const std::string ANSI_CYAN = "\033[36m";
const std::string ANSI_BRIGHT_CYAN = "\033[96m";


std::vector<int> generateSeededRandomNumbers(int seed, int count = 18) {
    // Initialize the random number generator with the provided seed
    std::mt19937 generator(seed);
    
    // Define a uniform integer distribution between 2 and 12 (inclusive)
    std::uniform_int_distribution<int> distribution(2, 12);
    
    // Generate the random numbers
    std::vector<int> randomNumbers;
    randomNumbers.reserve(count);  // Reserve space for 'count' numbers
    for (int i = 0; i < count; ++i) {
        randomNumbers.push_back(distribution(generator));
    }
    
    return randomNumbers;
}

namespace ariel{
    board::board(){
        this->turn = 1;
        int counter  = 0;
        int layout[19][6] = {
            {0, 1, 2, 3, 4, 5},         // Hexagon 0
            {2, 6, 7, 8, 9, 3},         // Hexagon 1
            {7, 10, 11, 12, 13, 8},     // Hexagon 2
            {17, 5, 4, 14, 15, 16},     // Hexagon 3
            {4, 3, 9, 18, 19, 14},      // Hexagon 4
            {9, 8, 13, 20, 21, 18},     // Hexagon 5
            {13, 12, 22, 23, 24, 20},   // Hexagon 6
            {28, 16, 15, 25, 26, 27},   // Hexagon 7
            {15, 14, 19, 29, 30, 25},   // Hexagon 8
            {19, 18, 21, 31, 32, 29},   // Hexagon 9
            {21, 20, 24, 33, 34, 31},   // Hexagon 10
            {24, 23, 35, 36, 37, 33},   // Hexagon 11
            {26, 25, 30, 38, 39, 40},   // Hexagon 12
            {30, 29, 32, 41, 42, 38},   // Hexagon 13
            {32, 31, 34, 43, 44, 41},   // Hexagon 14
            {34, 33, 37, 45, 46, 43},   // Hexagon 15
            {39, 38, 42, 47, 48, 49},   // Hexagon 16
            {42, 41, 44, 50, 51, 47},   // Hexagon 17
            {44, 43, 46, 52, 53, 40}    // Hexagon 18
        };
        int row = 0;
        std::vector<int> randomNumbers = generateSeededRandomNumbers(10,19);
        this->rndNumbers = randomNumbers;
        vector<hexagon*> hexagonsrow;
        for (int i = 0; i<19; i++){
            // cout << i << endl;
            hexagon* tempH = new hexagon(randomNumbers[i]);
            vector<vertex*> tempV(6, nullptr);
            for (size_t j = 0; j < 6; j++)
            {
                if(this->vertices.at(layout[i][j]) == nullptr){
                    vertex* temp = new vertex(layout[i][j]);
                    tempV[j] = temp;
                    this->vertices.at(layout[i][j]) = temp;
                }
                else{
                    tempV[j] = this->vertices[layout[i][j]];
                }
            }
        
            for (size_t j = 0; j < 6; j++) {
                tempH->addV(tempV[j]);
                bool check = false;
                std::vector<side*> tempS = tempV[j]->getSides();
                side* tempS2 = nullptr;

                int nextIndex = (j + 1) % 6;
                int layoutIndex = layout[i][nextIndex]; // Get the index from layout array

                for (auto s : tempS) {
                    
                    // Check if side s already connects tempV[j] and layout[i][(j + 1) % 6]
                    if (s->getOwners()[0]->getId() == tempV[j]->getId() && s->getOwners()[1]->getId() == this->vertices[layoutIndex]->getId()) {
                        check = true;
                        tempS2 = s;
                    }
                    if (s->getOwners()[1]->getId() == tempV[j]->getId() && s->getOwners()[0]->getId() == this->vertices[layoutIndex]->getId()) {
                        check = true;
                        tempS2 = s;
                    }
                }

                if (!check) {
                    tempS2 = new side(tempV[j], this->vertices[layoutIndex], counter);
                    counter++;
                    tempV[j]->addNeighbor(this->vertices[layoutIndex], tempS2);
                    this->vertices[layoutIndex]->addNeighbor(tempV[j], tempS2);
                    tempH->addS(tempS2);
                    this->sides.push_back(tempS2);
                } else {
                    tempH->addS(tempS2);
                }
            }

            int curRow = row;
            if(i>2)
            {
                row = 1;
            }
            if(i>6)
            {
                row = 2;
            }
            if(i>11)
            {
                row = 3;
            }
            if(i>15)
            {
                row = 4;
            }
            if(i > 18)
            {
                row = 5;
            }
            // cout << "Row: " << row << endl;
            // cout << "CurRow: " << curRow << endl;
            if(curRow == row)
            {
                hexagonsrow.push_back(tempH);
            }
            else
            {
                this->hexagonboard.push_back(hexagonsrow);
                // cout << "Pushed" << endl;
                hexagonsrow.clear();
                hexagonsrow.push_back(tempH);
            }
            if(i == 18)
            {
                this->hexagonboard.push_back(hexagonsrow);
            }
            
        }
        this->hexagonboard[0][0]->setType("Mountains");
        this->hexagonboard[0][1]->setType("Pasture");
        this->hexagonboard[0][2]->setType("Forest");
        this->hexagonboard[1][0]->setType("Fields");
        this->hexagonboard[1][1]->setType("Hills");
        this->hexagonboard[1][2]->setType("Pasture");
        this->hexagonboard[1][3]->setType("Hills");
        this->hexagonboard[2][0]->setType("Fields");
        this->hexagonboard[2][1]->setType("Forest");
        this->hexagonboard[2][2]->setType("Desert");
        this->hexagonboard[2][3]->setType("Forest");
        this->hexagonboard[2][4]->setType("Mountains");
        this->hexagonboard[3][0]->setType("Forest");
        this->hexagonboard[3][1]->setType("Mountains");
        this->hexagonboard[3][2]->setType("Fields");
        this->hexagonboard[3][3]->setType("Pasture");
        this->hexagonboard[4][0]->setType("Hills");
        this->hexagonboard[4][1]->setType("Fields");
        this->hexagonboard[4][2]->setType("Pasture");
        int counter2 = 0;
        for(int i = 0;i<9;i++){
            if(i<1){
                cards.push_back(new knight());
                continue;
            }
            if(i<2){
                cards.push_back(new yearOfPlenty());
                continue;
            }
            if(i<3){
                cards.push_back(new monopolycard());
                continue;
            }
            if(i<4){
                cards.push_back(new roadBuilding());
                continue;
            }
            cards.push_back(new victoryPoint());
        }
    }
 

//ascii art created in https://asciiart.club/

void board::printBoard() {
    std::string help = ANSI_BLUE+ "Color help: \n"+ANSI_GREEN + "Green: Empty vertex \n"+ ANSI_YELLOW+ "Yellow: Occupied 1st player vertex icon near it is the type \n"+
    ANSI_MAGENTA+ "Magenta: Occupied 2nd player vertex icon near it is the type \n"+ ANSI_CYAN+ "Cyan: Occupied 3rd player vertex icon near it is the type \n"+
    ANSI_RED+ "Red: Random number" + ANSI_RESET;
    std::cout << help << std::endl;
      std::string ascii_art =
R"(
                    r0  v1 r1       r6 v6 r7      r11  v10 r12
              ' v0 ╓═└       ╙═v2  «²└       ╙═v7ç «²└    ╙═ v11
                ▐              ▌║             ▐ ▌             l
                ▐      [h0]    ▌║     [h1]    j ▌    [h2]     l
              r5▐   Mountains  ▌║r2  Pasture  j ▌r8 Forest    lr13
                ▐              U║             ▐ ▌             ▓
                v5ⁿ═ç      ¿═└ v3'ⁿ+,      ╓²└v8 ╙*w      ,+ⁿv12
        r16 ╓*└  "r4,'ⁿv4ⁿ-,r3└  ╙*r10ⁿv9└ r9ⁿ`  ╙r15 ╙v13└r14└  "ⁿw r27
        v17          └*╕┌²└          ╙═ ▄ⁿ-         'ⁿ╤ ═╘          v22
        ▌▐             ▌▐              ═▌             ▐               ▌
    r20 ▌▐    [h3]     ▌▐r17   [h4]    ═▌r21 [h5]     ▐r24  [h6]      ▌r28
        ▌▐   Fields    ▌▐     Hills    ═▌   Pasture   ▐     Hills     ▌
         ¬,          ,»▀└w           ,∞ ▀⌂           v20¬,          v23
  r31,v16,-ⁿw,   ╓*r18╓v14 r23_ ,«ⁿ└,v18çr26;   r25`╓═  r30w   r29*└ ╓**╖  r45
v28ⁿ"     r19 v15╓═└      ⁿ═╖v19 ╓²└r22   'ⁿ≡,v21,≡ⁿ-     └*wv24 ╓═└      ⁿ═çv35           
 ▌             [▐`            `U├             ▐ ▌             ▓▐`            'U          
 ▌r35 [h7]     [▐     [h8]     U║    [h9]     j ▌    [h10]    l▐     [h11]    U            
 ▌   Fields    [▐r32 Forest    U║r36 Desert   j ▌r39 Forest   l▐r42 Mountains U  r46         
 ▌             [▐              U║             j ▌             l▐              U           
v27∞,       ┌═ⁿv25*╖       ,╓*└v29═ç       ,⌐ⁿv31ⁿw,       ┌═╙v33*╖        ╓²v36
   r34└*v26'r33'- ╙═ç ⁿ═v30└ ╓═╙ `ⁿ═,'ⁿ═v32└ a*└ └*w └*v34ⁿ-,∞ⁿ- ⁿ═╖ ⁿ═v37└ r47
         xⁿ└      r38'═,,═'r37   r41-ⁿw ╓*└r40   r44└*▄ ∞ⁿr43   r48 ⁿ═
        ▌▐             ▌▐              ═▌             ▐               ▌
    r52 ▌▐     [h12]   ▌▐     [h13]    ═▌     [h14]   ▐      [h15]    ▌
        ▌▐    Forest   ▌▐r49 Mountains ═▌r53 Fields   ▐r56  Pasture   ▌r59
         w            ┌▌▐ç            ╓-▌,           ,▐              ┌▌
        v40╙═w    ,∞ⁿ╓+v38;ⁿ═,    ╓═╙▄═v41"*w    ,w*,▄v43▄"═╖    ,∞ⁿv45
           r51 v39▄ⁿr50   r55wv42;+r54   r58═▄v44▄═r57  r61ⁿ+▄v46 r60
                ▐              ▌├             ▐ ▌             ▓
                ▐     [h16]    ▌├      [h17]  j ▌     [h18]   l
            r65 ▐     Hills    ▌├r62 Fields   j ▌r66 Pasture  l r69
                ▐              ▌├             ▐ ▌             l
                v49ⁿw,______,mⁿ-v47└*w______╓═ⁿv50ⁿ═ç_______,wv52
                  r64  v48  r63   r68  v51 r67    r71 v53  r70
)";
    
    for (int i = 0 ; i< 10 ; i++){
        if(rndNumbers[i]<10 ){
            std::string placeholder = "[h" + std::to_string(i) + "]";
            int replace_pos = ascii_art.find(placeholder);
            ascii_art.replace(replace_pos, placeholder.length(), " " +ANSI_RED + std::to_string(this->rndNumbers[i])+ANSI_RESET + "  ");
        }
        else{
            std::string placeholder = "[h" + std::to_string(i) + "]";
            int replace_pos = ascii_art.find(placeholder);
            ascii_art.replace(replace_pos, placeholder.length(), " " + ANSI_RED+std::to_string(this->rndNumbers[i])+ ANSI_RESET+ " ");
    }
    }
    for(int i = 10; i<19; i++){
        if(rndNumbers[i]<10 ){
            std::string placeholder = "[h" + std::to_string(i) + "]";
            int replace_pos = ascii_art.find(placeholder);
            ascii_art.replace(replace_pos, placeholder.length(), "  " +ANSI_RED+ std::to_string(this->rndNumbers[i])+ANSI_RESET+ "  ");
        }
        else{
            std::string placeholder = "[h" + std::to_string(i) + "]";
            int replace_pos = ascii_art.find(placeholder);
            ascii_art.replace(replace_pos, placeholder.length(), " " +ANSI_RED+std::to_string(this->rndNumbers[i])+ANSI_RESET+ "  ");
        }
    
    }
    
    for (int i = 0; i < 54; i++)
    {
        if(this->vertices[i]->getIsOccupied() == 1){
            std::string placeholder = "v" + std::to_string(i);
            int replace_pos = ascii_art.find(placeholder);
            switch (this->vertices[i]->getPlayer())
            {
            case 1:
                ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_YELLOW + std::to_string(i) + "┬" + ANSI_RESET);
                break;
            case 2:
                ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_MAGENTA + std::to_string(i) + "┬" + ANSI_RESET);
                break;
            case 3:
                ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_CYAN + std::to_string(i) + "┬" + ANSI_RESET);
                break;
            }
            
        }
        else if (this->vertices[i]->getIsOccupied() == 2)
        {
            std::string placeholder = "v" + std::to_string(i);
            int replace_pos = ascii_art.find(placeholder);
            switch (this->vertices[i]->getPlayer())
            {
            case 1:
                ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_YELLOW + std::to_string(i) + "©" + ANSI_RESET);
                break;
            case 2:
                ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_MAGENTA + std::to_string(i) + "©" + ANSI_RESET);
                break;
            case 3:
                ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_CYAN + std::to_string(i) + "©" + ANSI_RESET);
                break;
            }
        }
        else if(this->vertices[i]->getIsOccupied() == 0)
        {
        std::string placeholder = "v" + std::to_string(i);
        int replace_pos = ascii_art.find(placeholder);
        ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_GREEN + std::to_string(i) + ANSI_RESET + " ");
        }
     
    }
    bool checked[72] = {false};
    
    for(auto v : this->hexagonboard){
        for(auto h: v){
            for(int i = 0;i<6;i++){
                string placeholder = "r" + to_string(h->getSide(i)->getId());
                int replace_pos = ascii_art.find(placeholder);
                
                if(replace_pos != string::npos&& !checked[h->getSide(i)->getId()])
                {
                    if(h->getSide(i)->getIsOccupied())
                    {
                        int x =h->getSide(i)->getPlayer();
                        switch (x)
                        {
                        case 1:
                            if(h->getSide(i)->getId()<10){
                            ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_YELLOW + "»" + ANSI_RESET + " ");
                            }
                            else{
                            ascii_art.replace(replace_pos, placeholder.length(), " " + ANSI_YELLOW + "»" + ANSI_RESET + " ");
                            }
                            break;
                        case 2:
                            if(h->getSide(i)->getId()<10){
                            ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_MAGENTA + "»" + ANSI_RESET + " ");
                            }
                            else{
                            ascii_art.replace(replace_pos, placeholder.length(), " " + ANSI_MAGENTA + "»" + ANSI_RESET + " ");
                            }
                            break;
                        case 3:
                            if(h->getSide(i)->getId()<10){
                            ascii_art.replace(replace_pos, placeholder.length(), "" + ANSI_CYAN + "»" + ANSI_RESET + " ");
                            }
                            else{
                            ascii_art.replace(replace_pos, placeholder.length(), " " + ANSI_CYAN + "»" + ANSI_RESET + " ");
                            }
                            break;
                        }
                    }
                    else{
                        // cout << "Not occupied: "<< h->getSide(i)->getId() << endl;
                        if(h->getSide(i)->getId()<10){
                            ascii_art.replace(replace_pos, placeholder.length(), "  ");
                        }
                        else{
                            ascii_art.replace(replace_pos, placeholder.length(),"   ");
                        }
                        //ascii_art.replace(replace_pos, placeholder.length(), ANSI_BRIGHT_CYAN +"r" +to_string(h->getSide(i)->getId()) + ANSI_RESET + "");
                    }
                   checked[h->getSide(i)->getId()] = true;
                }
            }
        }
    }

    
    
    std::cout << ascii_art << std::endl;

}


    void board::setOcupiedCity(int playernum, int v){
        bool canBuild = false;
        for(auto s : this->vertices[v]->getSides()){
            if(s->getIsOccupied()){
                canBuild = true;
            }
        }
        // cout << "Can build: " << canBuild << endl;
        vertex* tempV = this->vertices[v];
        // cout << "here" << endl;
        // cout << "tempV id: " << tempV->getId() << endl;
        // cout << "can build town: " << tempV->canBuildTown(playernum) << endl;
        if(tempV->canBuildTown(playernum)&&canBuild){
            tempV->setOcupied(playernum);
        }
        else{
            cout << "Cannot build town here" << endl;
            throw invalid_argument ("Cannot build road here");
        }
    }

    void board::setOcupiedRoad(int playernum, int v1, int v2){
        if(v1<0 || v1>53 || v2<0 || v2>53){
            cout << "Invalid vertex number" << endl;
            throw invalid_argument( "Invalid vertex number");
        }
        vector<side*> tempS = this->vertices[v1]->getSides();
        for (auto s : tempS)
        {
            if(s->getOwners()[0]->getId() == this->vertices[v2]->getId() || s->getOwners()[1]->getId() == this->vertices[v2]->getId()){
                if(s->canBuildRoad(playernum)){
                    s->setOcupied(playernum);
                }
                else{
                    cout << "Cannot build road here" << endl;
                    throw invalid_argument ("Cannot build road here");
                }
            }
        }
    }

    void board::addPlayer(player* p){
        this->players.push_back(p);
    }

    board* board::getBoard(){
        return this;
    }

    int board::rollDices(){
        int result = 0;
        static int seed = 0;
        result = generateSeededRandomNumbers(seed,1)[0];
        seed++;
        for(auto h : this->hexagonboard){
            for(auto hex : h){
                if(hex->getNum() == result){
                    vector<vector<int>> temp;
                    for(auto v : hex->getV()){
                        if(v->getIsOccupied() == 1){
                            for(auto p : this->players){
                                if(p->getPlayerNum() == v->getPlayer()){
                                    cout << "Player " << p->getName() << " gets 1 " << hex->getType() << endl;
                                    p->addResource(hex->getType(),1);
                                }
                            }
                        }
                        if(v->getIsOccupied() == 2){
                            for(auto p : this->players){
                                if(p->getPlayerNum() == v->getPlayer()){
                                    cout << "Player " << p->getName() << " gets 2 " << hex->getType() << endl;
                                    p->addResource(hex->getType(),2);
                                }
                            }
                        }
                    }
                }
            }
        }
        return result;
    }

    bool board::checkPlayer(int num){
        for(auto p : this->players){
            if(p->getPlayerNum() == num){
                if(p->getPlayerNum() == this->turn){
                    return true;
                }
            }
        }
        return false;
    }   

    void board::nextTurn(){
        if(this->turn == this->players.size()){
            this->turn = 1;
        }
        else{
            this->turn++;
        }
    }

    void board::firstSettlements(player* p,int v1,int v2){
        if(v1<0 || v1>53){
            cout << "Invalid vertex number" << endl;
            throw invalid_argument( "Invalid vertex number");
        }
        if(v2<0 || v2>53){
            cout << "Invalid vertex number" << endl;
            throw invalid_argument( "Invalid vertex number");
        }
        if(this->vertices[v1]->getIsOccupied() == 0 && this->vertices[v2]->getIsOccupied() == 0){
            vector<vertex*> tempV1 = this->vertices[v1]->getNeighbors();
            vector<vertex*> tempV2 = this->vertices[v2]->getNeighbors();
            for(auto v : tempV1){
                if(v->getIsOccupied() == 1 || v->getIsOccupied() == 2 || v->getId() == v2){
                    cout << "Cannot build here" << endl;
                    throw "Cannot build here";
                }
            }
            for(auto v : tempV2){
                if(v->getIsOccupied() == 1 || v->getIsOccupied() == 2 || v->getId() == v1){
                    cout << "Cannot build here" << endl;
                    throw "Cannot build here";
                }
            }
            this->vertices[v1]->setOcupied(p->getPlayerNum());
            this->vertices[v2]->setOcupied(p->getPlayerNum());
            for(auto h: this->hexagonboard){
                for(auto hex : h){
                    for(auto v : hex->getV()){
                        if(v->getId() == v1 || v->getId() == v2){
                            if(v->getIsOccupied() == 1){
                                p->addResource(hex->getType(),1);
                            }
                        }
                    }
                }
            }
        }
        else{
            cout << "Cannot build here" << endl;
            throw "Cannot build here";
        }
    }

    string board::getNameFromTurn(){
        for(auto p : this->players){
            if(p->getPlayerNum() == this->turn){
                return p->getName();
            }
        }
        return "No player found";
    }

    int board::isGameEnd(){
        for(auto p : this->players){
            if(p->getVictoryPoints() >= 10){
                return p->getPlayerNum();
            }
        }
        return 0;
    }

    player* board::getPlayerByName(string name){
        for(auto p : this->players){
            if(p->getName() == name){
                return p;
            }
        }
        return nullptr;
    }

    void board::takeCard(player* p){
        int cardNum = rand() % this->cards.size();
        p->addCard(this->cards[cardNum]);
        cout << "Player " << p->getName() << " got a card type : " <<this->cards[cardNum]->getType()  << endl;
        this->cards.erase(this->cards.begin() + cardNum);
    }

    void board::monopoly(player* p){
        cout << "Choose resource to take from other players" << endl;
        cout << "1 - wood" << endl;
        cout << "2 - bricks" << endl;
        cout << "3 - wheat" << endl;
        cout << "4 - ore" << endl;
        cout << "5 - wool" << endl;
        int resource;
        cin >> resource;
        string res;
        for (auto player : this->players)
        {
            if(player->getPlayerNum() != p->getPlayerNum()){
                switch (resource)
                {
                case 1:
                    if(player->getwood()>0)
                        res = "wood";
                    else
                        continue;
                    break;
                case 2:
                    if(player->getbricks()>0)
                        res = "bricks";
                    else
                        continue;
                    break;
                case 3:
                    if(player->getwheat()>0)
                        res = "wheat";
                    else
                        continue;
                    break;
                case 4:
                    if(player->getore()>0)
                        res = "ore";
                    else
                        continue;
                    break;
                case 5:
                    if(player->getwool()>0)
                        res = "wool";
                    else
                        continue;
                    break;  
                }
                player->addResource(res,-1);
                p->addResource(res,1);
            }
        }
    }

 


} // namespace ariel
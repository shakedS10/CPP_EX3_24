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
    
    // Define a uniform integer distribution between 2 and 16 (inclusive)
    std::uniform_int_distribution<int> distribution(2, 16);
    
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
        cout << "Random Numbers: " << endl;
        for (auto i : randomNumbers)
        {
            cout << i << endl;
        }
        //vector<int> randomNumbers = {2,3,4,5,6,7,8,9,10,11,12,11,10,9,8,7,6,5,4}; 
        vector<hexagon*> hexagonsrow;
        for (int i = 0; i<19; i++){
            cout << i << endl;
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
            cout << "Row: " << row << endl;
            cout << "CurRow: " << curRow << endl;
            if(curRow == row)
            {
                hexagonsrow.push_back(tempH);
            }
            else
            {
                this->hexagonboard.push_back(hexagonsrow);
                cout << "Pushed" << endl;
                hexagonsrow.clear();
                hexagonsrow.push_back(tempH);
            }
            if(i == 18)
            {
                this->hexagonboard.push_back(hexagonsrow);
            }
            
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
                    r1  v1 r2       r6 v6 r7          v10
              ' v0 ╓═└       ╙═v2  «²└       ╙═v7ç «²└    ╙═ v11
                ▐              ▌║             ▐ ▌             l
                ▐      [h0]    ▌║     [h1]    j ▌    [h2]     l
              r0▐   Mountains  ▌║r3  Pasture  j ▌r8 Forest    l
                ▐              U║             ▐ ▌             ▓
                v5ⁿ═ç      ¿═└ v3'ⁿ+,      ╓²└v8 ╙*w      ,+ⁿv12
            ╓*└  "r5,'ⁿv4ⁿ-,r4└  ╙*r10ⁿv9└ r9ⁿ`  ╙═; ╙v13└ ╓*└  "ⁿw
        v17          └*╕┌²└          ╙═ ▄ⁿ-         'ⁿ╤ ═╘          v22
        ▌▐             ▌▐              ═▌             ▐               ▌
        ▌▐    [h3]     ▌▐     [h4]     ═▌    [h5]     ▐     [h6]      ▌
        ▌▐   Fields    ▌▐     Hills    ═▌   Pasture   ▐     Hills     ▌
         ¬,          ,»▀└w           ,∞ ▀⌂           v20¬,          v23
      ,v16,-ⁿw,   ╓*└ ╓v14 ╙*w   ,«ⁿ└,v18ç ╙═;   ,═ⁿ`╓═ⁿw,"ⁿw    ╓*└ ╓**╖
v28ⁿ"     └*w v15╓═└      ⁿ═╖v19 ╓²└     'ⁿ≡,v21,≡ⁿ-     └*wv24 ╓═└      ⁿ═çv35           
 ▌             [▐`            `U├             ▐ ▌             ▓▐`            'U          
 ▌    [h7]     [▐     [h8]     U║    [h9]     j ▌    [h10]    l▐     [h11]    U          
 ▌   Fields    [▐    Forest    U║   Desert    j ▌   Forest    l▐    Mountains U           
 ▌             [▐              U║             j ▌             l▐              U           
v27∞,       ┌═ⁿv25*╖       ,╓*└v29═ç       ,⌐ⁿv31ⁿw,       ┌═╙v33*╖        ╓²v36
     └*v26ⁿ,,≡ⁿ- ╙═ç ⁿ═v30└ ╓═╙ `ⁿ═,'ⁿ═v32└ a*└ └*w └*v34ⁿ-,∞ⁿ- ⁿ═╖ ⁿ═v37└
         xⁿ└         ⁿ═,,═ⁿ'        -ⁿw ╓*└         └*▄ ∞ⁿ"        `ⁿ═
        ▌▐             ▌▐              ═▌             ▐               ▌
        ▌▐    [h12]    ▌▐     [h13]    ═▌    [h14]    ▐      [h15]    ▌
        ▌▐   Forest    ▌▐   Mountains  ═▌   Fields    ▐     Pasture   ▌
         w            ┌▌▐ç            ╓-▌,           ,▐ w            ┌▌
        v40╙═w    ,∞ⁿ╓+v38;ⁿ═,    ╓═╙▄═v41"*w    ,w*,▄v43▄"═╖    ,∞ⁿv45
               v39▄ⁿ└      └*wv42;+ⁿ-      └═▄v44▄═└      `ⁿ+▄v46
                ▐              ▌├             ▐ ▌             ▓
                ▐     [h16]    ▌├    [h17]    j ▌    [h18]    l
                ▐     Hills    ▌├   Fields    j ▌   Pasture   l
                ▐              ▌├             ▐ ▌             l
                v49ⁿw,______,mⁿ-v47└*w______╓═ⁿv50ⁿ═ç_______,wv52
                       v48             v51            v53
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
     this->vertices[0]->setOcupied(1);
     this->vertices[0]->setOcupied(1);
     this->vertices[1]->setOcupied(2);
     this->vertices[2]->setOcupied(3);
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
    // string placeholder = "r0";
    // int replace_pos = ascii_art.find(placeholder);
    // ascii_art.replace(replace_pos, placeholder.length(), " " + to_string(this->vertices[0]->getSides()[0]->getId()) + " ");
    int scounter = 0;
    for(auto v : this->hexagonboard){
        for(auto h: v){
            for(int i = 0;i<6;i++){
                cout << h->getSide(i)->getId() << endl;
                string placeholder = "r" + to_string(scounter);
                int replace_pos = ascii_art.find(placeholder);
                if(replace_pos != string::npos){
                    ascii_art.replace(replace_pos, placeholder.length(),ANSI_BRIGHT_CYAN+ "" + to_string(h->getSide(i)->getId()) + "" + ANSI_RESET + " ");
                    scounter++;
                }
            }
        }
    }

    
    
    std::cout << ascii_art << std::endl;

}


    void board::setOcupiedCity(int playernum, int v){
        this->vertices[v]->setOcupied(playernum);
    }

    void board::setOcupiedRoad(int playernum, int v1, int v2){
        vector<side*> tempS = this->vertices[v1]->getSides();
        for (auto s : tempS)
        {
            if(s->getOwners()[0]->getId() == this->vertices[v2]->getId() || s->getOwners()[1]->getId() == this->vertices[v2]->getId()){
                s->setOcupied(playernum);
            }
        }
    }

    board* board::getBoard(){
        return this;
    }




} // namespace ariel
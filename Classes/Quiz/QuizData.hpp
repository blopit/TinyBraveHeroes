//
//  QuizData.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-22.
//

#ifndef QuizData_hpp
#define QuizData_hpp

#include <stdio.h>

class QuizData {
private:
    QuizData();
    ~QuizData();
    
    float fire = 0;
    float water = 0;
    float earth = 0;
    float air = 0;
    bool done = false;
    
public:
    static QuizData* getInstance();
    
    
};

#endif /* QuizData_hpp */

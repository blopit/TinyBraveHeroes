//
//  QuizData.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-22.
//

#include "QuizData.hpp"

static QuizData* quizData = nullptr;

QuizData* QuizData::getInstance() {
    if (!quizData) {
        quizData = new (std::nothrow)QuizData();
    }
    
    return quizData;
}

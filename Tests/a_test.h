#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "../user_interface.h"

#pragma once




/* only to store data and state - NO UI STUFF! */
class ATestQuestion
{
private:
    std::string questionToAsk;
    std::vector<std::string> listOfPossibleAnswers;
    std::string correctAnswer;
    
public:
    std::string& getQuestionToAsk() { return questionToAsk; }
    std::vector<std::string>& getListOfPossibleAnswers() { return listOfPossibleAnswers; }
    bool isCorrectAnswer(const std::string& answer) { return true; } //TODO: implement.
    
    ATestQuestion(const std::string& questionToAsk, const std::vector<std::string>& listOfPossibleAnswers, const std::string& correctAnswer) :
        questionToAsk( questionToAsk ),
        listOfPossibleAnswers( listOfPossibleAnswers ),
        correctAnswer( correctAnswer )
    {}
};




/* only to store data and state - NO UI STUFF! */
class ATest
{
private:
    std::string name;
    std::string statement;
    std::function<void(void)> funct;
    std::vector<ATestQuestion> questions;
    
public:
    std::string& getName() { return name; }
    std::string& getStatement() { return statement; }
    std::vector<ATestQuestion>& getQuestions() { return questions; }
    void executeFunction() { funct(); }
    
    ATest(const std::string& testName, const std::string& testStatement, const std::function<void(void)>& testFunct, const std::vector<ATestQuestion>& testQuestions) :
        name( testName ), 
        statement( testStatement ),
        funct( testFunct ),
        questions( testQuestions )
    {}
};

typedef std::vector<ATest> ProductTestRoutine;




void executeProductTestRoutine(ProductTestRoutine& testRoutine)
{
    for( std::vector<ATest>::iterator it = testRoutine.begin(); 
        it != testRoutine.end() ; ++it )
    {
        ATest& t = *it;
        
        std::cout << t.getName() << std::endl;
        
        t.executeFunction();
        
        std::vector<ATestQuestion>& questions = t.getQuestions();
        
        for (std::vector<ATestQuestion>::iterator it1 = questions.begin(); 
             it1 != questions.end(); ++it1)
        {
            ATestQuestion& question = *it1;
            UserInterface::ask_multichoice_question(question.getQuestionToAsk(), question.getListOfPossibleAnswers());
        }
    }
}

#ifndef ASKFM_USE_H
#define ASKFM_USE_H

#include "account.h"
#include "question.h"
#include "systemBase.h"

#include <vector>

class User
{
private:
    Account account;
    std::vector<Question> questionsToMe;
    std::vector<Question> questionsFromMe;

public:
    User();
    User(Account &account);

    std::string get_id() const;
    std::string get_username() const;
    std::string get_name() const;
    std::string get_email() const;
    bool allowAnonymouse() const; 

    void build();
    std::vector<Question> loadAnsweredQuestions_away();
    std::vector<Question> loadAnsweredQuestions_in();
    std::vector<Question> loadunAnsweredQuestions_away();
    std::vector<Question> loadunAnsweredQuestions_in();
    std::vector<Question> fetchQuestions(bool ThradQuestion) const;
    std::vector<Account> fetchAllUsers() const; 

    void printDetails() const;
    void listAllUsers() const;
    void view_allUsers();
    void view_user(User &otherUser);

    void view_QuestionMenu(Question &question) ; 

    void view_askAwayQuestions();
    void view_askInQuestions();
    void view_askAwayQuestion(bool answeredQuestions);
    void view_askInQuestion(bool answeredQuestions); 
    void view_feed();
    void askQuestion(User &otherUser); 
    void view_otherUserQuestions(bool answer) ;
};

#endif
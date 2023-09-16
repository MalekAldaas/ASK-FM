#include "../Headers/askfm_user.h"

#include <fstream>
#include <iostream>
#include <algorithm>

User::User()
{
}
User::User(Account &_account) : account(_account)
{
    this->build();
}
std::string User::get_id() const
{
    return this->account.get_id();
}
std::string User::get_username() const
{
    return this->account.get_username();
}
std::string User::get_email() const
{
    return this->account.get_email();
}
std::string User::get_name() const
{
    return this->account.get_name();
}
bool User::allowAnonymouse() const
{
    return this->account.allowAnonymouseQuestions();
}

void User::build()
{
    this->questionsFromMe.clear();
    this->questionsToMe.clear();
    std::fstream questionsFile("Database/Questions.txt");
    if (questionsFile.fail())
    {
        std::cerr << "Oops, Error Loading Questions File." << std::endl;
        return;
    }
    std::string line;
    while (getline(questionsFile, line))
    {
        Question question(line);
        if (question.get_from_id() == this->get_id())
        {
            this->questionsFromMe.push_back(question);
        }
        else if (question.get_to_id() == this->get_id())
        {
            this->questionsToMe.push_back(question);
        }
    }
    questionsFile.close();
}

std::vector<Question> User::loadAnsweredQuestions_away()
{
    this->build();
    std::vector<Question> result;
    for (int i = 0; i < (int)this->questionsFromMe.size(); i++)
    {
        if (this->questionsFromMe[i].isAnswered())
        {
            result.push_back(this->questionsFromMe[i]);
        }
    }
    return result;
}

std::vector<Question> User::loadunAnsweredQuestions_away()
{
    this->build();
    std::vector<Question> result;
    for (int i = 0; i < (int)this->questionsFromMe.size(); i++)
    {
        if (!this->questionsFromMe[i].isAnswered())
        {
            result.push_back(this->questionsFromMe[i]);
        }
    }
    return result;
}
std::vector<Question> User::loadAnsweredQuestions_in()
{
    this->build();
    std::vector<Question> result;
    for (int i = 0; i < (int)this->questionsToMe.size(); i++)
    {
        if (this->questionsToMe[i].isAnswered())
        {
            result.push_back(this->questionsToMe[i]);
        }
    }
    return result;
}
std::vector<Question> User::loadunAnsweredQuestions_in()
{
    this->build();
    std::vector<Question> result;
    for (int i = 0; i < (int)this->questionsToMe.size(); i++)
    {
        if (!this->questionsToMe[i].isAnswered())
        {
            result.push_back(this->questionsToMe[i]);
        }
    }
    return result;
}

void User::printDetails() const
{
    this->account.printAccount();
}

void User::view_allUsers()
{
    while (true)
    {
        SystemBase systemBase;
        std::vector<Account> accountsList = this->fetchAllUsers();
        this->listAllUsers();
        if ((int)accountsList.size() == 0)
        {
            std::cout << "There Are No Other Registered Acocunts To Show." << std::endl;
        }
        std::string choiceMenu, choiceAccount;
        std::cout << "1- View Account" << std::endl;
        std::cout << "2- Back" << std::endl;
        if (!input_number(choiceMenu, {1, 2}))
        {
            continue;
        }
        if (choiceMenu == "1")
        {
            std::cout << "Enter The Index Of The User To View: " << std::endl;
            if (!input_number(choiceAccount, {1, (int)accountsList.size()}))
            {
                continue;
            }
            User otherUser(accountsList[std::stoi(choiceAccount) - 1]);
            if(otherUser.get_id() == this->get_id())
            {
                this->printDetails(); 
                std::cout << ":)" << std::endl ;
                continue ;
            }
            this->view_user(otherUser);
        }
        else if (choiceMenu == "2")
        {
            return;
        }
    }
}

void User::view_user(User &otherUser)
{
    while (true)
    {
        this->build();
        otherUser.build();
        otherUser.printDetails();
        std::cout << "1- Ask Question" << std::endl;
        std::cout << "2- View User Questions" << std::endl;
        std::cout << "3- View User Answers" << std::endl;
        std::cout << "4- Back" << std::endl;

        std::string choice;
        if (!input_number(choice, {1, 4}))
        {
            continue;
        }
        if (choice == "1")
        {
            this->askQuestion(otherUser);
        }
        else if (choice == "2")
        {
            otherUser.view_otherUserQuestions(false);
        }
        else if (choice == "3")
        {
            otherUser.view_otherUserQuestions(true);
        }
        else if (choice == "4")
        {
            return;
        }
    }
}
void User::view_askAwayQuestions()
{
    while (true)
    {

        std::cout << "1- List Your Answered Questions" << std::endl;
        std::cout << "2- List Your NOT Answered Questions" << std::endl;
        std::cout << "3- Back" << std::endl;
        std::string choice;
        if (!input_number(choice, {1, 3}))
        {
            continue;
        }
        if (choice == "1")
        {
            this->view_askAwayQuestion(true);
        }
        else if (choice == "2")
        {
            this->view_askAwayQuestion(false);
        }
        else if (choice == "3")
        {
            return;
        }
    }
}

void User::view_askInQuestions()
{
    while (true)
    {
        std::cout << "1- List Questions You've Answered" << std::endl;
        std::cout << "2- Lists Questions You Haven't Answered" << std::endl;
        std::cout << "3- Back" << std::endl;
        std::string choice;
        if (!input_number(choice, {1, 3}))
        {
            continue;
        }
        if (choice == "1")
        {
            this->view_askInQuestion(true);
        }
        else if (choice == "2")
        {
            this->view_askInQuestion(false);
        }
        else if (choice == "3")
        {
            return;
        }
    }
}
void User::view_askAwayQuestion(bool answered)
{
    std::vector<Question> askAwayQuestion_list;
    if (answered == true)
    {
        askAwayQuestion_list = this->loadAnsweredQuestions_away();
    }
    else
    {
        askAwayQuestion_list = this->loadunAnsweredQuestions_away();
    }
    int vc_size = (int)askAwayQuestion_list.size();
    if (vc_size == 0)
    {
        std::cout << "There Are No Questions You've Asked To Show. " << std::endl;
        return;
    }
    sort(askAwayQuestion_list.begin(), askAwayQuestion_list.end());
    for (int i = 0; i < vc_size; i++)
    {
        std::cout << i + 1 << ":   ";
        askAwayQuestion_list[i].showQuestion();
    }
}

void User::view_askInQuestion(bool answered)
{
    std::vector<Question> askInQuestion_list;
    if (answered == true)
    {
        askInQuestion_list = this->loadAnsweredQuestions_in();
    }
    else if (answered == false)
    {
        askInQuestion_list = this->loadunAnsweredQuestions_in();
    }
    int questionListSize = (int)askInQuestion_list.size();
    if (questionListSize == 0)
    {
        std::cout << "There Are No Questions To Show." << std::endl;
        return;
    }
    for (int i = 0; i < (int)questionListSize; i++)
    {
        std::cout << i + 1 << ":    " << std::endl;
        askInQuestion_list[i].showQuestion();
    }
    std::string choice, choiceIndex;
    std::cout << "1- View Question" << std::endl;
    std::cout << "2- Back" << std::endl;
    if (!input_number(choice, {1, 2}))
    {
        return;
    }
    if (choice == "1")
    {
        if (!input_number(choiceIndex, {1, questionListSize}))
        {
            return;
        }
        int questionIndex = std::stoi(choiceIndex) - 1;
        this->view_QuestionMenu(askInQuestion_list[questionIndex]);
    }
    else if (choice == "2")
    {
        return;
    }
}

void User::view_QuestionMenu(Question &question)
{

    question.showQuestion();
    bool answered = question.isAnswered();

    if (answered == true)
    {
        std::cout << "1- Update Answer" << std::endl;
    }
    else
    {
        std::cout << "1- Answer" << std::endl;
    }
    std::cout << "2- Back" << std::endl;

    std::string choice;
    if (!input_number(choice, {1, 2}))
    {
        return;
    }
    if (choice == "1")
    {
        std::cout << "Please Note That By Continuing You Will Lose Any Answer You've Submitted Before And Can't Get Back" << std::endl;
        std::cout << "1- Continue " << std::endl;
        std::cout << "2- Back" << std::endl;

        if (!input_number(choice, {1, 2}))
        {
            return;
        }
        if (choice == "1")
        {
            std::cout << "Enter Answer: ";
            std::string answerParagraph;
            getline(std::cin, answerParagraph);

            std::string wannaDelete = question.putOnString();
            deleteFromFile("Database/Questions.txt", wannaDelete);
            question.set_answer(answerParagraph);

            std::vector<std::string> wannaAppend = question.putOnVector();
            appendOnFile("Database/Questions.txt", wannaAppend);
        }
    }
    if (choice == "2")
    {
        return;
    }
}
std::vector<Account> User::fetchAllUsers() const
{
    std::vector<Account> result;
    std::fstream accountsFile("Database/Accounts.txt");
    if (accountsFile.fail())
    {
        std::cerr << "Oops, Error Loading Accounts File While Fetching Data." << std::endl;
        return result;
    }
    std::string line;
    while (getline(accountsFile, line))
    {
        Account _account(line);
        result.push_back(_account);
    }
    return result;
}
std::vector<Question> User::fetchQuestions(bool ThreadQuestion) const
{
    std::vector<Question> result;
    std::fstream questionsFile("Headers/Questions.txt");
    if (questionsFile.fail())
    {
        std::cerr << "Oops, Error Loading Questions File." << std::endl;
        return result;
    }
    std::string line;
    while (getline(questionsFile, line))
    {
        Question question(line);
        if (question.isThread() == ThreadQuestion)
        {
            result.push_back(question);
        }
    }
    return result;
}
void User::listAllUsers() const
{
    std::vector<Account> accountsList = this->fetchAllUsers();
    if (accountsList.size() == 0)
    {
        std::cout << "There Are No Users Yet." << std::endl;
        return;
    }
    for (int i = 0; i < accountsList.size(); i++)
    {
        std::cout << i + 1 << ": ";
        accountsList[i].printAccount();
    }
}
void User::view_feed()
{
    std::vector<Question> questions_list = this->fetchQuestions(false);
    int listSize = (int)questions_list.size();
    if (listSize == 0)
    {
        std::cout << "No Feed To Show." << std::endl;
        return;
    }
    int i, j;
    for (i = listSize - 1, j = 1; i >= (std::max(0, listSize - 3)); i--, j++)
    {
        std::cout << j << ":   " << std::endl;
        questions_list[i].showQuestion();
    }

    while (true)
    {
        std::cout << "1- Show More Feed" << std::endl;
        std::cout << "2- View Question Threads" << std::endl;
        std::cout << "3- Back" << std::endl;

        std::string choice, choiceIndex;
        int questionIndex;
        if (!input_number(choice, {1, 3}))
        {
            return;
        }
        if (choice == "1")
        {
            if (i == 0)
            {
                std::cout << "There Are No More Feed To Show." << std::endl;
                continue;
            }
            int last_i = i, last_j = j;
            for (i = last_i - 1, j = last_j - 1; i >= (std::max(0, last_i - 10)); i--, j++)
            {
                questions_list[i].showQuestion();
            }
        }
        if (choice == "2")
        {
            if (!input_number(choiceIndex, {1, j}))
            {
                return;
            }
            questionIndex = listSize - std::stoi(choiceIndex);
            std::vector<Question> threadList = this->fetchQuestions(true);
            questions_list[questionIndex].showQuestion();
            for (int thread_i = 0; thread_i < (int)threadList.size(); thread_i++)
            {
                threadList[thread_i].showQuestion();
            }
        }
    }
}

void User::askQuestion(User &otherUser)
{
    std::string id, parent_id, from_id, to_id, paragraph, anonymouse = "0";
    std::cout << "Note, " << otherUser.get_username();
    if (otherUser.allowAnonymouse())
    {
        std::cout << "ALLOW ";
    }
    else
    {
        std::cout << "DOESN'T ALLOW ";
    }
    std::cout << "Anonymouse Questions." << std::endl;
    std::cout << "1- Continue" << std::endl;
    std::cout << "2- Back" << std::endl;
    std::string choice;
    if (!input_number(choice, {1, 2}))
    {
        return;
    }
    if (choice == "2")
    {
        return;
    }
    if (otherUser.allowAnonymouse() == true)
    {
        std::cout << "Anonymouse Question: " << std::endl;
        std::cout << "1- Yes" << std::endl;
        std::cout << "2- No" << std::endl;
        if (!input_number(choice, {1, 2}))
        {
            return;
        }
        if (choice == "1")
        {
            anonymouse = "1";
        }
        else
        {
            anonymouse = "0";
        }
    }
    std::cout << "Enter The Question Paragraph: ";
    getline(std::cin, paragraph);
    SystemBase systemBase;
    id = systemBase.createNewQuestion();
    parent_id = "0";
    from_id = this->get_id();
    to_id = otherUser.get_id();
    Question question(id, parent_id, from_id, to_id, paragraph, UNANSWERED_CODE, anonymouse);

    std::vector<std::string> vc_data = question.putOnVector();
    appendOnFile("Database/Questions.txt", vc_data);
}
void User::view_otherUserQuestions(bool userAnswers)
{
    std::vector<Question> questions_list;
    if (userAnswers == true)
    {
        questions_list = this->questionsFromMe;
    }
    else
    {
        questions_list = this->questionsToMe;
    }
    for (int i = 0, cnt = 1; i < (int)questions_list.size(); i++)
    {
        if (userAnswers == false && questions_list[i].isAnonymouse())
            continue;
        std::cout << cnt << ": ";
        questions_list[i].showQuestion();
    }
}
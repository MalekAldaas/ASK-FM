#include "../Headers/question.h"
Question::Question()
{
    Question("-1", "-1", "-1", "-1", "-1", UNANSWERED_CODE, "0");
}
Question::Question(const std::string &_id, const std::string &_parent_id, const std::string &_from_id, const std::string &_to_id, const std::string &_paragraph, const std::string &_answer, const std::string &_anonymouse)
    : id(_id), parent_id(_parent_id), from_id(_from_id), to_id(_to_id), paragraph(_paragraph), answer(_answer), anonymouse(_anonymouse)
{
}
Question::Question(const std::string &dataLine)
{
    std::vector<std::string> data = readLine(dataLine);
    this->set_id(data[0]);
    this->set_parent_id(data[1]);
    this->set_from_id(data[2]);
    this->set_to_id(data[3]);
    this->set_paragraph(data[4]);
    this->set_answer(data[5]);
    this->set_anonymouse(data[6]);
}
std::string Question::get_id() const
{
    return this->id;
}

std::string Question::get_parent_id() const
{
    return this->parent_id;
}

std::string Question::get_from_id() const
{
    return this->from_id;
}

std::string Question::get_to_id() const
{
    return this->to_id;
}

std::string Question::get_paragraph() const
{
    return this->paragraph;
}
std::string Question::get_answer() const
{
    return this->answer;
}
std::string Question::get_anonymouse() const
{
    return this->anonymouse;
}
void Question::set_id(const std::string &_id)
{
    this->id = _id;
}
void Question::set_parent_id(const std::string &_parent_id)
{
    this->parent_id = _parent_id;
}
void Question::set_from_id(const std::string &_from_id)
{
    this->from_id = _from_id;
}
void Question::set_to_id(const std::string &_to_id)
{
    this->to_id = _to_id;
}
void Question::set_paragraph(const std::string &_paragraph)
{
    this->paragraph = _paragraph;
}
void Question::set_answer(const std::string &_answer)
{
    this->answer = _answer;
}
void Question::set_anonymouse(const std::string &_anonymouse)
{
    this->anonymouse = _anonymouse;
}
std::vector<std::string> Question::putOnVector() const
{
    std::vector<std::string> data;

    data.push_back(this->get_id());
    data.push_back(this->get_parent_id());
    data.push_back(this->get_from_id());
    data.push_back(this->get_to_id());
    data.push_back(this->get_paragraph());
    data.push_back(this->get_answer());
    data.push_back(this->get_anonymouse());

    return data;
}
std::string Question::putOnString() const
{
    std::string result = "" ;
    std::vector<std::string> data = this->putOnVector(); 
    for(int i = 0; i < (int)data.size(); i++)
    {
        result  +=  data[i];
        result  +=  wordsSplit; 
    }
    return result; 
}

bool Question::isThread() const
{
    return this->get_parent_id() != "0";
}
bool Question::isAnonymouse() const
{
    return this->get_anonymouse() == "1";
}
bool Question::isAnswered() const
{
    return this->get_answer() != UNANSWERED_CODE;
}
void Question::showQuestion() const
{
    Account account_from, account_to;
    account_from.set_byID(this->get_from_id());
    account_to.set_byID(this->get_to_id());

    if (this->isThread() == true)
    {
        std::cout << "\tThread Question (ID: " << this->get_id() << ") Of Base Question (ID: " << this->get_parent_id() << ") To User: " << account_to.get_username() << " With (ID: " << account_to.get_id() << ")  , ";
        if (this->isAnonymouse() == true)
        {
            std::cout << "From AQ." << std::endl;
        }
        else
        {
            std::cout << "From User: " << account_from.get_username() << " With (ID: " << account_from.get_id() << ")." << std::endl;
        }
        std::cout << "\t  Question: " << this->get_paragraph() << std::endl;
        if (this->isAnswered())
        {
            std::cout << "\t  Answer: " << this->get_answer() << std::endl;
        }
        else
        {
            std::cout << "\t  NOT ANSWERED YET." << std::endl;
        }
    }
    else
    {
        std::cout << "Question (ID: " << this->get_id() << ") To User: " << account_to.get_username() << " With (ID: " << account_to.get_id() << ")  ,";
        if (this->isAnonymouse() == true)
        {
            std::cout << "From AQ." << std::endl;
        }
        else
        {
            std::cout << "From User: " << account_from.get_username() << " With (ID: " << account_from.get_id() << ") ." << std::endl;
        }
        std::cout << "Question: " << this->get_paragraph() << std::endl;
        if (this->isAnswered())
        {
            std::cout << "Answer: " << this->get_answer() << std::endl;
        }
        else
        {
            std::cout << "NOT ANSWERED YET." << std::endl;
        }
    }
}

bool Question::operator<(const Question &otherQuestion) const
{
    if (this->get_id() < otherQuestion.get_id())
    {
        return true;
    }
    else
    {
        return this->get_parent_id() < otherQuestion.get_parent_id();
    }
}
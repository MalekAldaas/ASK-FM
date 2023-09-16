#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>

#include "account.h"
#include "helperFunctions.h"
const std::string UNANSWERED_CODE = "1001010101001101010010110010";


class Question
{
private:
    std::string id;
    std::string parent_id;
    std::string from_id;
    std::string to_id;
    std::string paragraph;
    std::string answer;
    std::string anonymouse; // 1 => anonymouse AQ, 0 => none anonymouse.
    // ANONYMOUSE QUESTION !
public:
    Question();
    Question(const std::string &_id, const std::string &_parent_id, const std::string &_from_id, const std::string &_to_id, const std::string &_paragraph, const std::string &_answer, const std::string &_anonymouse);
    Question(const std::string &dataLine);
    std::string get_id() const;
    std::string get_parent_id() const;
    std::string get_from_id() const;
    std::string get_to_id() const;
    std::string get_paragraph() const;
    std::string get_answer() const;
    std::string get_anonymouse() const;

    void set_id(const std::string &_id);
    void set_parent_id(const std::string &_parent_id);
    void set_from_id(const std::string &_from_id);
    void set_to_id(const std::string &_to_id);
    void set_paragraph(const std::string &_paragraph);
    void set_answer(const std::string &_answer);
    void set_anonymouse(const std::string &_anonymouse);

    std::vector<std::string> putOnVector() const;
    std::string putOnString() const;

    bool isThread() const;
    bool isAnonymouse() const;
    bool isAnswered() const;

    bool operator<(const Question &other) const;

    void showQuestion() const;
};

#endif
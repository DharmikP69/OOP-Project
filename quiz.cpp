// Changes :
// 1. Added virtual destructor to Question class in line 38
// 2. Added floating point division for percentage calculation in line 94 and 101
// 3. Added getline for player name input in line 195
// 4. Added comments for better understanding
#include <iostream>
#include <string>
using namespace std;

class Question {
protected:
  string questionText;
  string options[4];
  int correctAnswer;

public:
  Question(string q, string a, string b, string c, string d, int correct) {
    questionText = q;
    options[0] = a;
    options[1] = b;
    options[2] = c;
    options[3] = d;
    correctAnswer = correct;
  }

  virtual void display() {
    cout << "\n" << questionText << endl;
    cout << "  1. " << options[0] << endl;
    cout << "  2. " << options[1] << endl;
    cout << "  3. " << options[2] << endl;
    cout << "  4. " << options[3] << endl;
  }

  bool checkAnswer(int answer) { return answer == correctAnswer; }

  int getCorrectAnswer() { return correctAnswer; }

  virtual ~Question() {}
};

class BonusQuestion : public Question {
private:
  int bonusPoints;

public:
  BonusQuestion(string q, string a, string b, string c, string d, int correct,
                int bonus)
      : Question(q, a, b, c, d, correct) {
    bonusPoints = bonus;
  }

  void display() override {
    cout << "\nBONUS QUESTION (+" << bonusPoints << " extra points)" << endl;
    cout << questionText << endl;
    cout << "  1. " << options[0] << endl;
    cout << "  2. " << options[1] << endl;
    cout << "  3. " << options[2] << endl;
    cout << "  4. " << options[3] << endl;
  }

  int getBonusPoints() { return bonusPoints; }
};

class Player {
private:
  string name;
  int score;
  int totalQuestions;
  int correctAnswers;

public:
  Player(string playerName) {
    name = playerName;
    score = 0;
    totalQuestions = 0;
    correctAnswers = 0;
  }

  void addScore(int points) {
    score += points;
    correctAnswers++;
  }

  void incrementTotal() { totalQuestions++; }

  void displayResult() {
    cout << "\n========================================" << endl;
    cout << "         QUIZ RESULT - " << name << endl;
    cout << "========================================" << endl;
    cout << "  Total Questions : " << totalQuestions << endl;
    cout << "  Correct Answers : " << correctAnswers << endl;
    cout << "  Wrong Answers   : " << (totalQuestions - correctAnswers) << endl;
    cout << "  Total Score     : " << score << endl;
    cout << "  Percentage      : " << (correctAnswers * 100.0 / totalQuestions)
         << "%" << endl;
    cout << "\n  Grade           : " << getGrade() << endl;
    cout << "========================================" << endl;
  }

  string getGrade() {
    int percent = correctAnswers * 100.0 / totalQuestions;
    if (percent >= 90)
      return "A+ (Excellent!)";
    else if (percent >= 75)
      return "A  (Very Good!)";
    else if (percent >= 60)
      return "B  (Good)";
    else if (percent >= 40)
      return "C  (Average)";
    else
      return "F  (Please study more!)";
  }

  string getName() { return name; }
  int getScore() { return score; }
};

class Quiz {
private:
  Question *questions[10];
  int totalQuestions;
  string category;

public:
  Quiz(string cat) {
    category = cat;
    totalQuestions = 0;
  }

  void addQuestion(Question *q) {
    if (totalQuestions < 10) {
      questions[totalQuestions++] = q;
    }
  }

  void startQuiz(Player &player) {
    cout << "\n========================================" << endl;
    cout << "     WELCOME TO " << category << " QUIZ" << endl;
    cout << "========================================" << endl;
    cout << "  Total Questions : " << totalQuestions << endl;
    cout << "  Points per Q    : 10" << endl;
    cout << "  Enter 1-4 for answers" << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < totalQuestions; i++) {
      cout << "\nQuestion " << (i + 1) << " of " << totalQuestions << ":";

      questions[i]->display();

      int answer;
      cout << "\nYour Answer: ";
      cin >> answer;

      while (answer < 1 || answer > 4) {
        cout << "Invalid! Enter 1-4: ";
        cin >> answer;
      }

      player.incrementTotal();

      if (questions[i]->checkAnswer(answer)) {

        BonusQuestion *bq = dynamic_cast<BonusQuestion *>(questions[i]);
        if (bq != nullptr) {
          int pts = 10 + bq->getBonusPoints();
          player.addScore(pts);
          cout << "Correct! +" << pts << " points (with bonus!)" << endl;
        } else {
          player.addScore(10);
          cout << "Correct! +10 points" << endl;
        }
      } else {
        cout << "Wrong! Correct answer was: "
             << questions[i]->getCorrectAnswer() << endl;
      }

      cout << "  Current Score: " << player.getScore() << endl;
    }
  }

  ~Quiz() {
    for (int i = 0; i < totalQuestions; i++) {
      delete questions[i];
    }
  }
};

int main() {
  string playerName;

  cout << "========================================" << endl;
  cout << "        C++ OOP QUIZ APPLICATION        " << endl;
  cout << "========================================" << endl;
  cout << "Enter Your Name: ";
  getline(cin, playerName);
  // cin >> playerName;

  Player player(playerName);

  Quiz quiz("C++ & GENERAL KNOWLEDGE");

  quiz.addQuestion(
      new Question("What does OOP stand for?", "Object Oriented Programming",
                   "Open Object Processing", "Ordered Object Protocol",
                   "Object Oriented Protocol", 1));

  quiz.addQuestion(new Question("Which keyword is used for Inheritance in C++?",
                                "extends", "inherits", ":", "->", 3));

  quiz.addQuestion(
      new Question("What is Encapsulation?", "Hiding data inside a class",
                   "Creating multiple objects", "Overloading functions",
                   "Using virtual functions", 1));

  quiz.addQuestion(new Question("Which function is overridden in Polymorphism?",
                                "Static function", "Virtual function",
                                "Inline function", "Friend function", 2));

  quiz.addQuestion(new Question("What is the output of: cout << 10/3?", "3.33",
                                "3", "4", "Error", 2));

  quiz.addQuestion(new Question("Which symbol is used for pointer in C++?", "&",
                                "->", "*", "%", 3));

  quiz.addQuestion(
      new Question("What is a Constructor?", "A function to destroy object",
                   "A function with return type",
                   "A function called automatically when object is created",
                   "A static function", 3));

  quiz.addQuestion(new Question("Which is NOT a pillar of OOP?",
                                "Encapsulation", "Polymorphism", "Compilation",
                                "Inheritance", 3));

  quiz.addQuestion(
      new BonusQuestion("What is the size of int in C++ (32-bit system)?",
                        "2 bytes", "4 bytes", "8 bytes", "1 byte", 2, 5));

  quiz.addQuestion(new BonusQuestion(
      "Which concept allows same function name with different parameters?",
      "Overriding", "Encapsulation", "Overloading", "Abstraction", 3, 5));

  quiz.startQuiz(player);

  player.displayResult();

  cout << "\nThank you for playing, " << player.getName() << "." << endl;

  return 0;
}

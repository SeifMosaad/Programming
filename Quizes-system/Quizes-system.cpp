#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include<regex>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
void loadFromFile();
void Login();
void Adduser();
void Generate_A();
vector<int> arra(4, 0);
vector <int> que1;
int y = 2, t = 0, pl = 0, ad = 0, mcqc = 0, tfc = 0, cc = 0,TotalQ=0;
bool r = 0, is_Emp = 1,f=0;
long int id_seed = static_cast<long int>(t);
string file_name;
string commons;
class Helper {
public:
	// trim from start (in place)
	static inline void ltrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
	}

	// trim from end (in place)
	static inline void rtrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	}

	// trim from both ends (in place)
	static inline void trim(std::string& s) {
		ltrim(s);
		rtrim(s);
	}


	// trim from both ends (copying)
	static inline std::string trim_str(std::string s) {
		trim(s);
		return s;
	}

	static inline std::string formatComparableString(std::string s) {
		s = trim_str(s);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		return s;
	}

	static inline bool isValidCompleteQ(string testq) {
		int counter = 0;
		smatch match;
		regex r("[.]+");
		for (std::sregex_iterator i = std::sregex_iterator(testq.begin(), testq.end(), r);
			i != std::sregex_iterator();
			++i) {
			counter++;
		}
		return (counter == 1);
	}

};

class Question
{
protected:
	bool isvalid;

public:
	// Data Members 
	long id;
	string* text;
	string* correctAnswer;
	string* userAnswer;

	//Constructor
	Question(long qid, string* txt, string* correctAns) : text(txt), correctAnswer(correctAns) {
		id = qid;
		isvalid = false;
		userAnswer = new string("");
	}

	// Member Functions() 
	virtual string render(string userType)
	{
		std::stringstream ss;
		if (userType == "Admin") {
			ss << "(ID: " << id << ") " << Helper::trim_str(*text) << " (Answer:" << *correctAnswer << ")" << "\n";
		}
		else {
			ss << "(ID: " << id << ") " << Helper::trim_str(*text) << "\n";
		}
		return ss.str();
	}

	void answer(string* answer)
	{
		isvalid = Helper::formatComparableString(*answer) == Helper::formatComparableString(*correctAnswer);
		userAnswer = answer;
	}

	bool isValid()
	{
		return isvalid;
	}

	virtual string getType()
	{
		return "generic question";
	}

	virtual int getMark()
	{
		return 0;
	}

	bool operator == (const Question& toCompare) {

		return (Helper::formatComparableString(*text) == Helper::formatComparableString(*toCompare.text));
	}
};

class Quiz {
private:
	vector<Question*> questions;
public:

	// Data Members 
	long id;

	// Constructor
	Quiz(long qid)
	{
		id = qid;
	}

	// Methods
	void addQuestion(Question* q) {
		// the max fixed size is 5 ...
		if (questions.size() < 5) {
			questions.push_back(q);
		}
	}

	vector<Question*> getQuestions() {
		return questions;
	}

	int markQuiz() {
		int total = 0;
		for (Question* qt : questions) {
			if (qt->isValid()) {
				total += qt->getMark();
			}
		}
		return total;
	}

};
class User
{

public:

	// Data Members 
	long id;
	string firstName;
	string lastName;
	string userName;
	string password;
	vector<Quiz*> quizes;

	// Constructor
	User(long idNum, string fname, string lname, string uname, string pass) {
		id = idNum;
		firstName = fname;
		lastName = lname;
		userName = uname;
		password = pass;
	}

	bool operator == (const User& toCompare) {

		return (Helper::formatComparableString(userName) == Helper::formatComparableString(toCompare.userName));
	}

	// Member Functions() 
	virtual string getRole()
	{
		return "User";
	}

	string toString() {
		std::stringstream ss;
		ss <<"-"<<Helper::formatComparableString(firstName) << setw(20) << "-" << Helper::formatComparableString(lastName) << setw(20) << "-" << Helper::formatComparableString(userName);
		string res = ss.str();
		return res;
	}

	void Changename(string s, string a)
	{
		firstName = s;
		lastName = a;
	}

	string showQuizStats() {
		int quizSum = 0, quizMax = 0, quizMin = 0, mcqNum = 0, mcqSum = 0, cqNum = 0, cqSum = 0, tfqNum = 0, tfqSum = 0, tmp = 0;
		double quizAvg = 0, mcqAvg = 0, cqAvg = 0, tfqAvg = 0;

		if (quizes.size() > 0)
			quizMin = quizes[0]->markQuiz();

		for (Quiz* qz : quizes) {
			tmp = qz->markQuiz();
			quizSum += tmp;
			if (tmp > quizMax) {
				quizMax = tmp;
			}
			if (tmp < quizMin) {
				quizMin = tmp;
			}
			for (Question* q : qz->getQuestions()) {
				if (q->getType() == "MCQ") {
					mcqNum++;
					if (q->isValid())
					{
						mcqSum += q->getMark();
					}
				}
				else if (q->getType() == "TFQ") {
					tfqNum++;
					if (q->isValid())
					{
						tfqSum += q->getMark();
					}
				}
				else
				{
					cqNum++;
					if (q->isValid())
					{
						cqSum += q->getMark();
					}

				}
			}
			mcqAvg = mcqSum / (double)mcqNum;
			tfqAvg = tfqSum / (double)tfqNum;
			cqAvg = cqSum / (double)cqNum;
		}
		quizAvg = (quizSum / (double)quizes.size());
		std::stringstream ss;
		ss << "\nYour score statistics per quiz:";
		ss << "\n\t-Number of Quizes taken:" << quizes.size();
		ss << "\n\t-Highest quiz score:" << quizMax << "/10";
		ss << "\n\t-Lowest quiz score:" << quizMin << "/10";
		ss << "\n\t-Average quiz score:" << quizAvg << "/10";
		ss << "\nYour score statistics per question type:";
		ss << "\n\t-Number of MC questions:" << mcqNum;
		ss << "\n\t-Number of Complete questions:" << cqNum;
		ss << "\n\t-Number of T/F questions:" << tfqNum;
		ss << "\n\t-Average grade for MC questions:" << mcqAvg << "/2";
		ss << "\n\t-Average grade for Complete questions:" << cqAvg << "/3";
		ss << "\n\t-Average grade for T/F questions:" << tfqAvg << "/1";
		return ss.str();
	}
	string getLastTwoQuizStats() {

		string res = "";
		int const qlenth = (int)quizes.size();
		if (qlenth > 1) {
			int const last = qlenth - 1;
			int const llast = qlenth - 2;
			std::stringstream ss, ss1, ss2;
			ss << "\nYour results from the last two quizes are as follows:" << endl;

			Quiz* qz1 = quizes[last];
			Quiz* qz2 = quizes[llast];

			ss1 << "\nScores from Quiz id: " << qz1->id << endl;
			ss2 << "\nScores from Quiz id: " << qz2->id << endl;

			vector<Question*> qz1_quest = qz1->getQuestions();
			vector<Question*> qz2_quest = qz2->getQuestions();
			int questionLen = qz1->getQuestions().size();

			for (int i = 0; i < questionLen; i++) {

				ss1 << "[" << qz1_quest[i]->getType() << " Question] " << *qz1_quest[i]->text << endl;
				ss2 << "[" << qz2_quest[i]->getType() << " Question] " << *qz2_quest[i]->text << endl;

				if (qz1_quest[i]->isValid()) {
					ss1 << "Your correctly answered the question with: " << *qz1_quest[i]->userAnswer << endl;
					ss1 << "Your score for that question is " << qz1_quest[i]->getMark() << "/" << qz1_quest[i]->getMark() << endl;
				}
				else {
					ss1 << "Your answer: " << *qz1_quest[i]->userAnswer << " was wrong, the correct answer is " << *qz1_quest[i]->correctAnswer << endl;
					ss1 << "Your score for that question is 0/" << qz1_quest[i]->getMark() << endl;
				}
				if (qz2_quest[i]->isValid()) {
					ss2 << "Your correctly answered the question with: " << *qz2_quest[i]->userAnswer << endl;
					ss2 << "Your score for that question is " << qz2_quest[i]->getMark() << "/" << qz2_quest[i]->getMark() << endl;
				}
				else {
					ss2 << "Your answer: " << *qz2_quest[i]->userAnswer << " was wrong, the correct answer is " << *qz2_quest[i]->correctAnswer << endl;
					ss2 << "Your score for that question is 0/" << qz2_quest[i]->getMark() << endl;
				}

			}
			ss << ss1.str();
			ss << ss2.str();
			return ss.str();
		}
		return "";
	}
	string getallscore()
	{
		int tr = 0, tw = 0;
		static int id = 1;
		cout << "-Total Number Of Quizes : " << quizes.size() << endl;
		for (Quiz* qz : quizes) {
			cout << "-Your Mark For Quiz Number " << id << " Is : " << qz->markQuiz() << endl;
			id++;
		}
		for (Quiz* qz : quizes) {
			for (Question* q : qz->getQuestions()) {
				if (q->isValid() == 1) tr++;
				else tw++;
			}
		}
			stringstream ss;
			ss << "-Total Number Of Right Answers : " << tr << endl;
			ss << "-Total Number Of Wrong Answers : " << tw << endl;
			return ss.str();
	}
};
class MCQ : public Question
{

public:
	// Data Members 
	string* answerChoices;

	//Constructor
	MCQ(long qid, string* txt, string* correctAns, string* choices) : Question(qid, txt, correctAns) {
		answerChoices = choices;
	}

	string getType()
	{
		return "MCQ";
	}

	string render(string userType)
	{
		std::stringstream ss;
		string ans[4] = { "a","b","c","d" };

		if (userType == "Admin") {
			ss << "(ID: " << id << ") " << *text << "\n";
			for (int i = 0; i < 4; i++) {
				if (Helper::formatComparableString(*correctAnswer) == Helper::formatComparableString(answerChoices[i]))
					ss << "\t*[" << ans[i] << "] " << answerChoices[i];
				else
					ss << "\t[" << ans[i] << "] " << answerChoices[i];
			}
			ss << "\n";
		}
		else
		{
			ss << "(ID: " << id << ") " << *text << "\n" << "\t[a] " << answerChoices[que1[0]] << "\t[b] " << answerChoices[que1[1]] << "\t[c] " << answerChoices[que1[2]] << "\t[d] " << answerChoices[que1[3]] << "\n";
		}

		return ss.str();
	}

	int getMark()
	{
		return 2;
	}

};
class TFQ : public Question
{
public:

	//Constructor
	TFQ(long qid, string* txt, string* correctAns) : Question(qid, txt, correctAns) {	}

	string getType()
	{
		return "TFQ";
	}

	int getMark()
	{
		return 1;
	}
};
class CQ : public Question
{
public:

	//Constructor
	CQ(long qid, string* txt, string* correctAns) : Question(qid, txt, correctAns) {	}

	string getType()
	{
		return "CQ";
	}

	int getMark()
	{
		return 3;
	}
};
class Admin : public User
{

public:
	// Constructor 
	Admin(long idNum, string fname, string lname, string uname, string pass) : User(idNum, fname, lname, uname, pass) {}

	// Member Functions() 
	string getRole()
	{
		return "Admin";
	}
};
class Player : public User
{

public:

	// Constructor 
	Player(long idNum, string fname, string lname, string uname, string pass) : User(idNum, fname, lname, uname, pass) {}

	// Member Functions() 
	string getRole()
	{
		return "Player";
	}
};
void AMenu(User *c1);
void PMenu(User *c1);
void AChoices(User *c1);
void PChoices(User* c1);
void GenerateCC();
void GenerateTFQ();
vector <string> file_names;
vector<string> ve1;
vector<MCQ> mcqQuestions;
vector<TFQ>tfQuestions;
vector<CQ>cQuestions;
vector<User*> Users;
vector<int> arr(100, 0);
vector <int> que;
vector <int> que2;
vector <int> Quizes;
int cntr = 0;
Quiz* generateQuiz(long id) {
	cntr = cntr % 2;
	Quiz* qz = new Quiz(id);
	long qid = id;
	qz->addQuestion(new MCQ(mcqQuestions[rand() % mcqc]));
	qz->addQuestion(new TFQ(tfQuestions[que2[0]]));
	qz->addQuestion(new TFQ(tfQuestions[que2[1]]));
	qz->addQuestion(new CQ(cQuestions[que[0]]));
	qz->addQuestion(new CQ(cQuestions[que[1]]));
	cntr++;
	return qz;
}
int main()
{
	// Initialize the unique ID seed within this session
	srand(time(NULL));
	time_t t = time(nullptr);
	t = time(nullptr);
	long int id_seed = static_cast<long int>(t);
	Player t1(id_seed++, "player", "player", "player", "123456");
	Admin t2(id_seed++, "admin", "admin", "admin", "123456");
	Users.push_back(&t1);
	Users.push_back(&t2);
	Login();
}
void loadFromFile()
{
	cout << "Enter the file name : ";
	cin >> file_name;
	int j = file_name.length();
	string qa;
	for (int i = 0; i < j; i++)
	{
		qa += tolower(file_name[i]);
	}
	file_names.push_back(qa);
	//Opening File
	ifstream file;
	file.open(file_name);
	//Check if the file has an error
	if (file.fail())
	{
		system("cls");
		cerr << "Error While Opening The File" << endl;
		system("cls");
	}
	//Getting All lines
	string line;
	int count = 0;
	while (getline(file, line, '\n'))
	{
		ve1.push_back(line);
		count++;
		is_Emp = 0;
	}
	//Check if the file is empty
	if (is_Emp == 1)
	{
		system("cls");
		cout << "The file is empty, you have to add 5 questions to start a quiz.\n";
		file_names.pop_back();
	}
	is_Emp = 1;
	for (int i = 0; i < count; i++)
	{

		if (ve1[i] == "MCQ")
		{
			mcqQuestions.push_back(MCQ(id_seed++, new string(ve1[i + 1]), new string(ve1[i + 2]), new string[4]{ ve1[i + 2], ve1[i + 3] ,ve1[i + 4],ve1[i + 5] }));
			mcqc++;
			TotalQ++;
			i += 5;
		}
		else if (ve1[i] == "TF")
		{
			tfQuestions.push_back(TFQ(id_seed++, new string(ve1[i + 1]), new string (ve1[i + 2])));
			tfc++;
			TotalQ++;
			i += 2;
		}
		else if (ve1[i] == "COMPLETE")
		{
			cQuestions.push_back(CQ(id_seed++, new string (ve1[i + 1]),new string (ve1[i + 2])));
			cc++;
			TotalQ++;
			i += 2;
		}
	}
	cout << file_name << "Has Been Loaded Succussfully PRESS 1 To Getback To Your Menu : ";
	int c;
	cin >> c;
	AMenu(Users[t]);
	AChoices(Users[t]);
	system("cls");
}
void Login()
{
Main:
	cout << "*******************************************************************\n";
	cout <<setw(55)<< "Welcome to the Quiz game program V2.0!\n";
	cout << "*******************************************************************\n";
	bool r = 0;
	cout << "Please Enter The Username : ";
	string u;
	cin >> u;
	cout << "Please Enter The Password : ";
	string p;
	cin >> p;
	for (int i = 0; i < Users.size(); i++)
	{
		if (u == Users[i]->userName && p == Users[i]->password)
		{
			t = i;
			r = 1;
			break;
		}
	}
	if (r == 1)
	{
		system("cls");
		string s12 = Users[t]->getRole();
		commons = s12;
		if (commons == "Admin")
		{
			AMenu(Users[t]);
			AChoices(Users[t]);
		}
		else if (commons == "Player")
		{
			PMenu(Users[t]);
			PChoices(Users[t]);
		}
	}
	if (r != 1)
	{
		system("cls");
		cout << "This Username And Password Are Not Existed To Re-enter A Correct Information PRESS 1 Or 0 To Exit : ";
		int ch;
		cin >> ch;
		if (ch == 0) exit(1);
		else
		{	
			system("cls");
			goto Main;
		}
	}
}
void Adduser()
{
L:
	bool f = 0;
	string fname, lname, uname, pass, role;
	cout << "Please Enter The First Name : ";
	cin >> fname;
	cout << "Please Enter The Last Name : ";
	cin >> lname;
	cout << "Please Enter The Username : ";
	cin >> uname;
	cout << "Please Enter The Password : ";
	cin >> pass;
	R:
	cout << "Please Enter The Role : ";
	cin >> role;
	if (role == "player")
	{
		bool b1 = 0;
		Player a(id_seed++, fname, lname, uname, pass);
		for (int i = 0; i < Users.size(); i++)
		{
			if (a == *Users[i])
			{
				b1 = 1;
				break;
			}
		}
		if (b1 == 1)
		{
			system("cls");
			cout << "This User Is Already Existed PRESS 1 To Re-enter A New Information Or -1 To Getback To Your Menu [1/-1] : ";
			int cho = 0;
			cin >> cho;
			if (cho == 1) goto L;
			else
			{
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
		}
		f = b1;
		if (f == 0)
		{
			Users.push_back(&a);
			system("cls");
			cout << "User Has Been Added Succussfully Press 1 To Enter Another User Or -1 To Getback To Your Menu [1/-1] : ";
			int c3;
			cin >> c3;
			if (c3 == 1) goto L;
			else
			{
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
		}
	}
	else if (role == "admin")
	{
		bool b1 = 0;
		Admin a(id_seed++, fname, lname, uname, pass);
		for (int i = 0; i < Users.size(); i++)
		{
			if (a == *Users[i])
			{
				b1 = 1;
				break;
			}
		}
		if (b1 == 1)
		{
			cout << "This User Is Already Existed PRESS 1 To Re-enter A New Information Or -1 To Getback To Your Menu [1/-1] : ";
			int cho = 0;
			cin >> cho;
			if (cho == 1) goto L;
			else
			{
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
		}
		f = b1;
		if (f == 0)
		{
			Users.push_back(&a);
			cout << "User Has Been Added Succussfully Press 1 To Enter Another User Or -1 To Getback To Your Menu [1/-1] : ";
			int c3;
			cin >> c3;
			if (c3 == 1) goto L;
			else
			{
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
		}
	}
	else
	{
		if (role != "player" && role != "admin")
		{
			cout << "Invalid Role Please Press 1 To Re-Enter A Correct One Or -1 To Getback To Your Menu [1/-1] : ";
			int c2;
			cin >> c2;
			if (c2 == 1) goto R;
			else
			{
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
		}
	}
}
void AChoices(User *c1)
{
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			system("cls");
			Login();
		}
		else if (choice == 2)
		{
			system("cls");
			cout << "Please Enter Your First Name : ";
			string fn;
			cin >> fn;
			cout << "Please Enter Your Last Name : ";
			string ln;
			cin >> ln;
			c1->Changename(fn, ln);
			system("cls");
			if (commons == "Admin")
			{
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
			else if (commons == "Player")
			{
				PMenu(Users[t]);
			}
		}
		else if (choice == 3)
		{
			system("cls");
			cout << "Existing users in the system:\n";
			cout << "-" << "First name" << setw(20) << "-" << "Last Name" << setw(20) << "-" << "Username" << setw(20) << "-" << "Role" << endl;
			for (User* ve : Users) cout << ve->toString() << setw(20) << ve->getRole() << endl;
			cout << "Press 1 To Add New User Or -1 To Getback To Your Menu [1/-1] : ";
			int c4;
			cin >> c4;
			if (c4 == 1) Adduser();
			else
			{
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
		}
		else if (choice == 4)
		{
			system("cls");
			Adduser();
		}
		else if (choice == 5)
		{
			P:
			if (mcqc == 0 && tfc == 0 && cc == 0)
			{
				system("cls");
				cout << "There Is No Questions Press 1 To Getback To Your Menu To Add Some Questions : ";
				int y;
				cin >> y;
				AMenu(Users[t]);
				AChoices(Users[t]);
			}
			else {
				cout << "Number of questions avaliable : " << TotalQ << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "MC Questions list (Total: " << mcqc << " Questions)" << endl;
				cout << "---------------------------------------------------" << endl;
				for (MCQ x : mcqQuestions) cout << x.render(commons) << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "TF Questions list (Total: " << tfc << " Questions)" << endl;
				cout << "---------------------------------------------------" << endl;
				for (TFQ x : tfQuestions) cout << x.render(commons) << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "Complete Questions list (Total: " << cc << " Questions)" << endl;
				cout << "---------------------------------------------------" << endl;
				for (CQ x : cQuestions) cout << x.render(commons) << endl;
				cout << "---------------------------------------------------" << endl;
				cout << "If You Wann To Delete A Question Type Question's ID OR -1 To Getback To Your Menu [ID/-1] : ";
				int ch;
				cin >> ch;
				if (ch == -1)
				{
					AMenu(Users[t]);
					AChoices(Users[t]);
				}
				else
				{
					if (TotalQ > 5)
					{
						for (int i = 0; i < mcqQuestions.size(); i++)
						{
							if (ch == mcqQuestions[i].id)
							{
								mcqQuestions.erase(mcqQuestions.begin() + i);
								mcqc--;
								TotalQ--;
							}
						}
						for (int i = 0; i < tfQuestions.size(); i++)
						{
							if (ch == tfQuestions[i].id)
							{
								tfQuestions.erase(tfQuestions.begin() + i);
								tfc--;
								TotalQ--;
							}
						}
						for (int i = 0; i < cQuestions.size(); i++)
						{
							if (ch == cQuestions[i].id)
							{
								cQuestions.erase(cQuestions.begin() + i);
								cc--;
								TotalQ--;
							}
						}
					}
					else
					{
						cout << "You Can't Delete More Questions\n";
					}
					system("cls");
					goto P;
				}
			}
		}
		else if (choice == 6)
		{
	E:
	system("cls");
			int cho = 0;
			cout << "Please Enter Quesion Type [MCQ/TFQ/CQ] : ";
			string type;
			cin >> type;
			while (type != "MCQ" && type != "TFQ" && type != "CQ")
			{
				cout << "Invalid Type Please Enter Quesion Type [MCQ/TFQ/CQ] : ";
				cin >> type;
			}
			if (type == "MCQ")
			{
				bool g = 0, h = 0;
				string ch[4];
				cout << "Please Enter The Question Text : ";
				string t1;
				cin.ignore();
				getline(cin, t1);
				while (g == 0)
				{
					cout << "Please Enter The Choices , Only One Will Be Correct\n";
					cout << "First Choice : ";
					cin >> ch[0];
					cout << "Second Choice : ";
					cin >> ch[1];
					cout << "Third Choice : ";
					cin >> ch[2];
					cout << "Forth Choice : ";
					cin >> ch[3];
					for (int i = 0; i < 3; i++)
					{
						h = 0;
						for (int j = i + 1; j < 4; j++)
						{
							if (ch[i] == ch[j])
							{
								cout << "You Can't Type Repeated Answers Please Re-enter Them.\n";
								h = 1;
								break;
							}
						}
						if (h == 1) break;
						else g = 1;
					}
					if (g == 0) continue;
					else break;
				}
				cout << "Please Enter The Correct Answer : ";
				string co;
				cin >> co;
				mcqQuestions.push_back(MCQ(id_seed++, new string (t1),new string (co), new string[4]{ ch[0],ch[1],ch[2],ch[3] }));
				mcqc++;
				TotalQ++;
				cout << "Question Has Been Added Succsufully Press 1 To Enter A New One Or -1 To Goback To Your Menu [1/-1] : ";
				cin >> cho;
				if (cho == 1) goto E;
				else
				{
					AMenu(Users[t]);
					AChoices(Users[t]);
				}
			}
			else if (type == "TFQ")
			{
				cout << "Please Enter The Question Text : ";
				string t1;
				cin.ignore();
				getline(cin, t1);
				cout << "Please Enter The Correct Answer [true/false] : ";
				string co;
				cin >> co;
				tfQuestions.push_back(TFQ(id_seed++, new string (t1), new string (co)));
				tfc++;
				TotalQ++;
				cout << "Question Has Been Added Succsufully Press 1 To Enter A New One Or -1 To Goback To Your Menu [1/-1] : ";
				cin >> cho;
				if (cho == 1) goto E;
				else
				{
					AMenu(Users[t]);
					AChoices(Users[t]);
				}
			}
			else if (type == "CQ")
			{
			Y:
				int f12;
				vector<int> check;
				cout << "Please Enter The Question Text : ";
				string t1;
				cin.ignore();
				getline(cin, t1);
				f12= Helper::isValidCompleteQ(t1);
				if (f12 == 0)
				{
					cout << "You Can't Enter More Than One Correct Answer , PRESS 1 To Re-enter The Question Or -1 To Getback to Your Menu [1/-1] : ";
					int u;
					cin >> u;
					if (u == 1)
					{
						check.clear();
						goto Y;
					}
					else
					{
						AMenu(Users[t]);
						AChoices(Users[t]);
					}

				}
				else
				{
					cout << "Please Enter The Correct Answer : ";
					string co;
					cin >> co;
					cQuestions.push_back(CQ(id_seed++, new string(t1), new string(co)));
					cc++;
					TotalQ++;
					cout << "Question Has Been Added Succsufully Press 1 To Enter A New One Or -1 To Goback To Your Menu [1/-1] : ";
					cin >> cho;
					if (cho == 1) goto E;
					else
					{
						AMenu(Users[t]);
						AChoices(Users[t]);
					}
				}
			}
		}
		else if (choice == 7) {
		system("cls");
			loadFromFile();
		}
		else if (choice == 8) exit(1);
}
void AMenu(User* c1)
{
	system("cls");
	cout << "Welcome " << c1->firstName << " " << c1->lastName << "(ADMIN), please choose from the following options:\n" << "        [1] Switch accounts\n" << "        [2] Update your name\n" << "        [3] View all users\n" << "        [4] Add new user\n" << "        [5] View all questions\n" << "        [6] Add new question\n" << "        [7] Load questions from file\n" << "        [8] Exit the program\n" << "My Choice : ";
}
void PMenu(User* c1)
{
	system("cls");
	cout << "Welcome " << c1->firstName << " " << c1->lastName << "(PLAYER), please choose from the following options:\n" << "        [1] Switch accounts\n" << "        [2] Update your name\n" << "        [3] Start a new quiz\n" << "        [4] Display your scores statistics\n" << "        [5] Display all your scores\n" << "        [6] Display details of your last 2 quizzes\n" << "        [7] Exit the program\n";
}
void PChoices(User* c1)
{
	int choice;
	//cout << "My Choice : ";
	cin >> choice;
	if (choice == 1)
	{
		system("cls");
		Login();
	}
	else if (choice == 2)
	{
		system("cls");
		cout << "Please Enter Your First Name : ";
		string fn;
		cin >> fn;
		cout << "Please Enter Your Last Name : ";
		string ln;
		cin >> ln;
		c1->Changename(fn, ln);
		system("cls");
		if (commons == "Admin")
		{
			AMenu(Users[t]);
			AChoices(Users[t]);
		}
		else if (commons == "Player")
		{
			PMenu(Users[t]);
			PChoices(Users[t]);
		}
	}
	else if (choice == 3)
	{
		if (TotalQ < 5 || mcqc <1 ||tfc <2 ||cc<2)
		{
			system("cls");
			int u;
			cout << "To Start A New Quiz You Have To Add 2 MCQ Questions And 2 TFQ And 1 TF Question\n";
			cout << "Press 0 to get back to main menu or 6 to exit [0/6] : ";
			cin >> u;
			system("cls");
			if (u == 0)
			{
				PMenu(Users[t]);
				PChoices(Users[t]);
			}
			else exit(0);
		}
		else
		{
			GenerateCC();
			system("cls");
			GenerateTFQ();
			string temp;
			cin.ignore();
			Quiz* test = generateQuiz(id_seed++);
			cout << "*******************************************************************\n";
			cout << setw(55) << "Welcome to the Quiz Best Wishes\n";
			cout << "*******************************************************************\n";
				string tmp = "";
				for (Question* q :test->getQuestions())
				{
					Generate_A();
					bool f = 0;
					cout << "\n Question type is " << q->getType() << "\n";
					cout << q->render(Users[t]->getRole());
					getline(cin, temp);
					//temp = Helper::formatComparableString(temp);
					q->answer(new string(temp));
					que1.clear();
				}
				int finalMark = test->markQuiz();
				cout << "\n ===================================== \n";
				cout << "\n Your Final Mark Is " << finalMark << "\n";
				que.clear();
				que2.clear();
				Users[t]->quizes.push_back(test);
			cout << "Quiz Is Finished Press 1 To Getback To Your Menu Or -1 To Exit [1/-1] : ";
			int ch;
			cin >> ch;
			if (ch == 1)
			{
				PMenu(Users[t]);
				PChoices(Users[t]);
			}
			else exit(0);
		}
	}
	else if (choice == 4)
	{
		system("cls");
		cout << "*******************************************************************\n";
		cout << setw(55) << "Your Scores Statistics\n";
		cout << "*******************************************************************\n";
		cout << Users[t]->showQuizStats() << endl;
		cout << "Press 1 To Getback To Your Menu Or -1 To Exit [1/-1] : ";
		int ch;
		cin >> ch;
		if (ch == 1)
		{
			PMenu(Users[t]);
			PChoices(Users[t]);
		}
		else exit(0);
	}
	else if (choice == 6)
	{
	system("cls");
	cout << "*******************************************************************\n";
	cout << setw(55) << "Your Details Of Your Last 2 Quizzes\n";
	cout << "*******************************************************************\n";
	cout << Users[t]->getLastTwoQuizStats() << endl;
	cout << "Press 1 To Getback To Your Menu Or -1 To Exit [1/-1] : ";
	int ch;
	cin >> ch;
	if (ch == 1)
	{
		PMenu(Users[t]);
		PChoices(Users[t]);
	}
	else exit(0);
	}
	else if (choice == 5)
	{
	system("cls");
	cout << "*******************************************************************\n";
	cout << setw(55) << "Your Details Of Your All Scores\n";
	cout << "*******************************************************************\n";
	cout << Users[t]->getallscore() << endl;
	cout << "Press 1 To Getback To Your Menu Or -1 To Exit [1/-1] : ";
	int cho;
	cin >> cho;
	if (cho == 1)
	{
		PMenu(Users[t]);
		PChoices(Users[t]);
	}
	else exit(0);
	}
}
void GenerateCC()
{
	int count1 = 0;
	while (count1 < 2)
	{
		int num = rand() % cc;
		if (arr[num] == 0)
		{
			arr[num] = 1;
			que.push_back(num);
			count1++;
		}
	}
	fill(arr.begin(), arr.end(), 0);
}
void GenerateTFQ()
{
	int count1 = 0;
	while (count1 < 2)
	{
		int num = rand() % tfc;
		if (arr[num] == 0)
		{
			arr[num] = 1;
			que2.push_back(num);
			count1++;
		}
	}
	fill(arr.begin(), arr.end(), 0);
}
void Generate_A()
{
	int count1 = 0;
	while (count1 < 4)
	{
		int num = rand() % 4;
		if (arra[num] == 0)
		{
			arra[num] = 1;
			que1.push_back(num);
			count1++;
		}
	}
	fill(arra.begin(), arra.end(), 0);
}
#include "Status.h"
#include "FanPage.h"
#include "Member.h"
#include "FaceBook.h"
#include "exception.h"


FaceBook::FaceBook() : ActiveFaceBook(true)
{ // this is the constructor of the class "FaceBook" , initializing all the variables of the class , make and check memory allocation if needed,
	//Also this function adds to the system the first entities (Fan pages and members) and prints the intro to the Facebook.
	try {
		BinFileExtractData();
		initialProgram();
		printIntro();
	}
	catch (std::bad_alloc& e) {
		cout << "Exception thrown: " << e.what() << endl;
	}
}

int FaceBook::printMenu() {
	// this function prints the menu of facebook to the user.
	int choice = 0;
	cout << "This is our menu - " << endl;
	cout << "To add a user press -  1" << endl;
	cout << "To add a fan page press - 2" << endl;
	cout << "To add status to a user name or fan Page press - 3" << endl;
	cout << "To see a user's or fan page's status press - 4" << endl;
	cout << "to see the last 10 statuses of all friends of a particular user press - 5" << endl;
	cout << "to create a friendship between 2 users press - 6" << endl;
	cout << "To cancel a friendship with another user press - 7" << endl;
	cout << "To like fan page press - 8" << endl;
	cout << "To remove a like from fan page press - 9" << endl;
	cout << "To see all the users that currently registered in our system press - 10" << endl;
	cout << "To see all the friends of specific user or fan page press - 11" << endl;
	cout << "To exit from our system press - 12" << endl;
	cout << "Please enter your choice: " << endl;
	cin >> choice;
	return choice;
}

void FaceBook::performUserSelection(FaceBook& faceBook) {
	// this function activates the current function to perform the user selection according to his choice.
	try {
		switch (printMenu()) {
		case 1:
			faceBook.adduser();
			break;
		case 2:
			faceBook.addFanPage();
			break;
		case 3:
			faceBook.addStatus();
			break;
		case 4:
			faceBook.showStatus();
			break;
		case 5:
			faceBook.show10status();
			break;
		case 6:
			faceBook.friendship();
			break;
		case 7:
			faceBook.friendship(true);
			break;
		case 8:
			faceBook.AddOrRemoveFanPage();
			break;
		case 9:
			faceBook.AddOrRemoveFanPage(true);
			break;
		case 10:
			faceBook.ShowAllEntities();
			break;
		case 11:
			faceBook.ShowMembers();
			break;
		case 12:
			faceBook.Exit();
			break;
		default:
			PrintWrongSelection();
			break;
		}
	}
	catch (std::bad_alloc& e) {
		cout << "Exception thrown: " << e.what() << endl;
	}
	catch (Invalid_choice& e) {
		cout << "Exception thrown: " << endl << e.what();
		PrintExitLine();
		return;
	}
	catch (logic_error& e) {
		cout << "Exception thrown: " << endl << e.what();
	}
}

void FaceBook::adduser() {
	// this function adds a new user to the system database , by saving his details (username & birthdate)
	//as well as validating that this username hasn't been used until now by another username , then sends the user back to the main menu.
	bool done = false;
	string Name;
	printEnterUsername();
	cin.ignore();
	getline(cin, Name);
	while (!done) {
		try {
			checkName(Name);
			done = true;
		}
		catch (invalid_argument& e) {
			int choice;
			cout << "Exception thrown: " << endl << e.what();
			cin >> choice;
			if (choice == MAIN) {
				PrintExitLine();
				return;
			}
			else if (choice == CONTINUE)
			{
				printEnterUsername();
				cin.ignore();
				getline(cin, Name);
			}
		}
	}
	membersList += new Member(std::move(Name), fillDate());
	cout << "Your user has been created!" << endl;
	PrintExitLine();
}

int FaceBook::findEntityByName(const string& Name, bool member) const {
	// this function is checking if a username / fan page name is already exist in the system.
	if (member) {
		for (int i = 0; i < membersList.size(); ++i)
			if (*membersList[i] == Name)
				return i;
		throw invalid_argument("none of the users matching that name.\n");
	}
	else {
		for (int i = 0; i < fanPageList.size(); ++i) {
			if (*fanPageList[i] == Name)
				return i;
		}
		throw invalid_argument("none of the fan pages matching that name.\n");
	}
}

void FaceBook::checkName(const string& Name, bool member) const {
	if (member) {
		if (std::find_if(membersList.begin(), membersList.end(), [Name](const auto& mem) { return *mem == Name; }) != membersList.end()) {
			throw invalid_argument(alreadyUsed());
		}
	}
	else {
		if (std::find_if(fanPageList.begin(), fanPageList.end(), [Name](const auto& fp) { return *fp == Name; }) != fanPageList.end()) {
			throw invalid_argument(alreadyUsed());
		}
	}
}

void FaceBook::addFanPage() {
	// this function creates new fan page in the facebook system by taking the fan page name from the user
	// and validating that this name hasn't been used until now by another fan page , then sends the user back to the main menu.
	bool done = false;
	string Name;
	printEnterFanPageName();
	cin.ignore();
	getline(cin, Name);
	while (!done) {
		try {
			checkName(Name, false);
			done = true;
		}
		catch (invalid_argument& e) {
			int choice;
			cout << "Exception thrown: " << endl << e.what();
			cin >> choice;
			if (choice == MAIN) {
				PrintExitLine();
				return;
			}
			else if (choice == CONTINUE)
			{
				printEnterFanPageName();
				cin.ignore();
				getline(cin, Name);
			}
		}
	}
	fanPageList += new FanPage(Name);
	cout << "Your fan page has been created!" << endl;
	PrintExitLine();
}

void FaceBook::addStatus() {
	// this function adds a new status to a member / fan page profile by letting the user write his
	// new status , this function also save the date and time that the status has been published , then sends the user back to the main menu.
	int index, choice = 0,status=0;
	bool done = false;
	string content;
	while (!done) {
		try {
			cout << "Do you wish to add status to a username or fan page?" << endl;
			PrintChoices();
			cin >> choice;
			if (choice != MEMBER && choice != FAN_PAGE && choice != RETURN_MAIN_PAGE)
				throw invalid_argument("Invalid choice!\nplease try again.\n");
			if (choice != RETURN_MAIN_PAGE){
				printStatusChoices();
				cin >> status;
				if (status != TEXT && status != IMAGE && status != VIDEO)
					throw invalid_argument("Invalid choice!\nplease try again.\n");
			}
			done = true;
		}
		catch (invalid_argument& e) {
			cout << "Exception thrown: " << endl << e.what();
		}
	}
	if (choice == MEMBER) {
		if (membersList.empty()) {
			throw Invalid_choice("There are no users.\n");
		}
		if (inputIntegrity(index))
			return;
		cout << "Please enter the content of the status: " << endl;
		cin >> content;
		*membersList[index] += createStatus(content, getDateAndTime(), status);
		PrintExitLine();
	}
	else if (choice == FAN_PAGE) {
		if (fanPageList.empty()) {
			throw Invalid_choice("There are no fan pages.\n");
		}
		else {
			if (inputIntegrity(index, false))
				return;
			cout << "Please enter the content of the status: " << endl;
			getline(cin, content);
			*fanPageList[index] += createStatus(content, getDateAndTime(), status);
			PrintExitLine();
		}
	}
	else {
		PrintExitLine();
	}
}

void FaceBook::showStatus() const {
	// this function shows to the user all the statuses of another user / fan page
	// by asking the name of the other user/ fan page , then sends the user back to the main menu.
	int choice = 0, index;
	bool done = false;
	while (!done) {
		try {
			cout << "Do you wish to see  a username or fan page status?" << endl;
			PrintChoices();
			cin >> choice;
			if (choice != MEMBER && choice != FAN_PAGE && choice != RETURN_MAIN_PAGE)
				throw invalid_argument("Invalid choice!\nplease try again.\n");
			done = true;
		}
		catch (invalid_argument& e) {
			cout << "Exception thrown: " << endl << e.what();
		}
	}
	if (choice == MEMBER) {
		if (membersList.empty()) {
			throw Invalid_choice("There are no users.\n");
		}
		if (inputIntegrity(index))
			return;
		cout << "Here are all of the statuses of: " << membersList[index]->getName() << " - " << endl;
		membersList[index]->printAllStatuses();
	}
	else if (choice == FAN_PAGE) {
		if (fanPageList.empty()) {
			throw Invalid_choice("There are no fan pages.\n");
		}
		if (inputIntegrity(index, false))
			return;
		cout << "Here are all of the statuses of: " << fanPageList[index]->getName() << " - " << endl;
		fanPageList[index]->printAllStatuses();
	}
	PrintExitLine();
}

void FaceBook::show10status() const {
	// this function shows the 10 most recent statuses of all the friends and the fan pages
	// that the user follow , then sends the user back to the main menu.
	int index;
	if (membersList.empty()) {
		throw Invalid_choice("There are no users.\n");
	}
	if (inputIntegrity(index))
		return;
	membersList[index]->printLastFriendsStatuses();
	PrintExitLine();
}

void FaceBook::friendship(bool remove) {
	// this function makes the user a friend of another user that he has been liked to be a friend of
	// , then sends the user back to the main menu.
	int index1, index2;
	if (membersList.size() <= 1) {
		throw Invalid_choice("not enough users.\n");
	}
	if (inputIntegrity(index1) || inputIntegrity(index2, true, false))
		return;
	if (remove) {
		if (!(membersList[index1]->checkIfWeAreFriends(membersList[index2]->getName())))
			throw logic_error("The users are not even friends!\n");
		*membersList[index1] -= membersList[index2];
		cout << "The users are not friends now!" << endl;
	}
	else {
        if (membersList[index1] == membersList[index2]) {
            throw logic_error("Users can't be friend of themselves!\n");
        }
		if (membersList[index1]->checkIfWeAreFriends(membersList[index2]->getName()))
			throw logic_error("The users are already friends!\n");
		*membersList[index1] += membersList[index2];
		cout << "The users are friends now!" << endl;
	}
	PrintExitLine();
}

void FaceBook::AddOrRemoveFanPage(bool dislike) {
	// this function adding / removing a fan page (that the user wants to follow/unfollow)
	// from his fan page list , then sends the user back to the main menu.
	int index1, index2;
	if (fanPageList.empty() || membersList.empty()) {
		throw Invalid_choice("not enough users or fan pages.\n");
	}
	if (inputIntegrity(index1) || inputIntegrity(index2, false, false))
		return;
	bool Like = checkLike(index1, fanPageList[index2]->getName());
	if (dislike) {
		if (!Like) {
			throw logic_error("The user didnt liked this fan page from the beginning!\n");
		}
		*fanPageList[index2] -= membersList[index1];
		cout << "The user like have been removed now from this fan page!" << endl;
		PrintExitLine();
	}
	else {
		if (Like) {
			throw logic_error("The user already liked this fan page from the beginning!\n");
		}
		*fanPageList[index2] += membersList[index1];
		cout << "The user is connected to this fan page now!" << endl;
		PrintExitLine();
	}
}

bool FaceBook::checkLike(const int& index1, const string& Name) const {
	// this function checks if the user already liked/ follow the fan page that he asked to follow.
	return std::any_of(membersList[index1]->getLikedFanPages().begin(), membersList[index1]->getLikedFanPages().end(),
		[Name](const FanPage* page) { return *page == Name; });
}

void FaceBook::ShowAllEntities() const {
	// this function shows all the entities that has been registered until now to the facebook system
	// by printing all the members names and birthdate and all the fan pages names , then sends the user back to the main menu.
	if (fanPageList.empty() && membersList.empty()) {
		throw Invalid_choice("There aren't any users or fan pages.\n");
	}
	cout << "This are all the users that sign in to our system: " << endl;
	for (int i = 0; i < membersList.size(); ++i) {
		PrintEntity(i);
	}
	cout << "This are all the fan pages that sign in to our system: " << endl;
	for (int i = 0; i < fanPageList.size(); ++i) {
		PrintEntity(i, false);
	}
	PrintExitLine();
}

void FaceBook::ShowMembers() const {
	// this function shows all the friends of a certain member or all the followers of certain fan page
	// by printing all the members names , then sends the user back to the main menu.
	int index, choice = 0;
	bool done = false;
	while (!done) {
		try {
			cout << "Do you wish to see all the friends of user or fan page?" << endl;
			PrintChoices();
			cin >> choice;
			if (choice != MEMBER && choice != FAN_PAGE && choice != RETURN_MAIN_PAGE)
				throw invalid_argument("Invalid choice!\nplease try again.\n");
			done = true;
		}
		catch (invalid_argument& e) {
			cout << "Facebook Exception thrown: " << endl << e.what();
		}
	}
	if (choice == MEMBER) {
		if (inputIntegrity(index))
			return;
		if (membersList[index]->getFriendsArr().empty())
			throw Invalid_choice("This member has no friends yet. \n");
		cout << "This are all the friends of " << *membersList[index] << ": " << endl;
		for (const Member* it : membersList[index]->getFriendsArr()) {
			cout << *it << endl;
		}
	}
	else if (choice == FAN_PAGE) {
		if (inputIntegrity(index, false))
			return;
		if (fanPageList[index]->getFriendsArr().empty())
			throw invalid_argument("This fan page has no followers yet.\n");
		cout << "This are all the users that connect to " << *fanPageList[index] << ": " << endl;
		for (const Member* it : fanPageList[index]->getFriendsArr()) {
			cout << *it << endl;
		}
	}
	PrintExitLine();
}

void FaceBook::Exit() {
	// this function closes the facebook and perform log out for the user.
	cout << "See you next time! bye!" << endl;
	ActiveFaceBook = false;
}

void FaceBook::PrintWrongSelection() {
	// this function prints a warning message to the user because he inserted wrong character
	// for his menu choice , then letting the user performing the selection again.
	cout << "You have entered a wrong number" << endl;
	cout << "Please try again." << endl;
}

bool FaceBook::inputIntegrity(int& index, bool member, bool flag) const {
	// this function asks the user to select on which entity he wants to perform the action on.
	bool done = false;
	string Name;
	while (!done) {
		try {
			if (member)
				printEnterUsername();
			else
				printEnterFanPageName();
			if (flag)
				cin.ignore();
			getline(cin, Name);
			index = findEntityByName(Name, member);
			done = true;
		}
		catch (invalid_argument& e) {
			int choice = -1;
			cout << "Exception thrown: " << endl << e.what();
			while (choice != MAIN && choice != CONTINUE)
			{
				PrintChoiceOption(member);
				cin >> choice;
				if (choice == 0) {
					PrintExitLine();
					return true;
				}
			}
			if (!flag)
				cin.ignore();
		}
	}
	return false;
}

void FaceBook::PrintChoiceOption(bool member) {
	// this function prints the warnings message if a member / fan page
	// , that a user want to select and make actions on , is not existed in the facebook system.
	if (member) {
		cout << "Sorry! this user is not exist in our system" << endl;
		cout << "Please try another user name or return to the main menu" << endl;
		cout << "press 1 to insert another user name or 0 to return to the main menu" << endl;
	}
	else {
		cout << "Sorry! this fan page is not registered in our system!" << endl;
		cout << "Please try another fan page name or return to the main menu" << endl;
		cout << "press 1 to insert another page name or 0 to return to the main menu" << endl;
	}
}

void FaceBook::PrintEntity(const int& i, bool member) const {
	// this function prints the data of  a certain entity (member / fan page)
	// that is registered in the facebook system .
	if (member) {
		cout << "Member number " << i + 1 << " name: " << endl;
		cout << *membersList[i] << endl;
		cout << "Member number " << i + 1 << " birth date: " << endl;
		cout << membersList[i]->getBirthDate() << endl;
	}
	else {
		cout << "Fan page number " << i + 1 << " name: " << endl;
		cout << *fanPageList[i] << endl;
	}
}

void FaceBook::initialProgram() {
	// this function initials the first entities on the system.
	// first we will create the new members -
	if (membersList.empty())
	{
		membersList += new Member("Oren", { 20, 07, 1999 });
		membersList += new Member("Zach", { 04, 10, 1999 });
		membersList += new Member("Sagi", { 14, 07, 2003 });

		// here we create the new Fan pages -

		fanPageList += new FanPage("Ynet");
		fanPageList += new FanPage("walla");
		fanPageList += new FanPage("twitter");
		fanPageList += new FanPage("facebook");

		// now we will make friendships between some members -
		*membersList[0] += membersList[1];
		*membersList[0] += membersList[2];
		*membersList[1] += membersList[2];

		// now we make some members to "like" Fan pages -
		*membersList[2] += fanPageList[0];
		*membersList[2] += fanPageList[1];
		*membersList[0] += fanPageList[2];
		*membersList[0] += fanPageList[3];

		// lastly we will add some statuses to members/fan pages -
		*membersList[0] += new Status("Hello world", getDateAndTime());
		*membersList[2] += new Status("Im so hungry!", getDateAndTime());
		*fanPageList[0] += new Status("Breaking news today at 8!!", getDateAndTime());
		*fanPageList[3] += new Status("Hello and welcome to facebook! this is our first status!", getDateAndTime());
	}
}

string FaceBook::getDateAndTime() {
	// this function gets the curren time and date (for the status).
	time_t now = time(nullptr);
	string date_time = ctime(&now);
	return date_time;
}

void FaceBook::PrintExitLine() {
	// this function printing our basic line when user choose to return to the menu
	// or when an action ends.
	cout << "You will return to the main menu now" << endl;
}

void FaceBook::PrintChoices() {
	// this function prints the options for the user.
	cout << "1-for member" << endl;
	cout << "2-for fan page" << endl;
	cout << "3-return to main page" << endl;
}
void FaceBook::printStatusChoices()
{
	// this function prints the options for the user.
	cout << "1-for Text" << endl;
	cout << "2-for Image" << endl;
	cout << "3-for Video" << endl;
}
Status* FaceBook::createStatus(const string& content,const string& Date,int choice)
{
	if (choice == TEXT)
		return new Status(content, Date);
	else if (choice == IMAGE)
		return new Image(content, Date);
	else if (choice == VIDEO)
		return new Video(content, Date);
}

DOB FaceBook::fillDate()
{ // this function get from the user his birthdate details and inserting those to the variable.
	bool done = false;
	int day, month, year;
	while (!done) {
		try {
			cout << "Please enter your birth day:" << endl;
			cin >> day;
			if (CHECK_DAY(day))
				throw invalid_argument("Invalid day!\nplease try again.\n");
			cout << "Please enter your birth month:" << endl;
			cin >> month;
			if (CHECK_MONTH(month))
				throw invalid_argument("Invalid month!\nplease try again.\n");
			cout << "Please enter your birth year:" << endl;
			cin >> year;
			if (CHECK_YEAR(year))
				throw invalid_argument("Invalid year!\nplease try again.\n");
			done = true;
		}
		catch (invalid_argument& e) {
			cout << "Exception thrown: " << endl << e.what();
		}
	}
	return { day , month , year };
}

string FaceBook::alreadyUsed() {
	string str;
	str = "Sorry! that name is already used.";
	str += "\nPlease enter another user name or return to the main menu: ";
	str += "\npress 1 to insert another user name or 0 to return to the main menu: ";
	return str;
}

FaceBook:: ~FaceBook() {
	for (auto& it : membersList) {
		for (auto& i : it->getBulletinBoard()) {
			delete i;
		}
		delete it;
	}
	for (auto& it : fanPageList) {
		for (auto& i : it->getBulletinBoard()) {
			delete i;
		}
		delete it;
	}
}

void FaceBook::DataToBinFile()const
{
	fstream file("MyFile.bin", std::ios::binary | std::ios::out | std::ios::trunc);
	if (!file.is_open()) {//check if the file opened successfully
		throw std::ifstream::failure("failed to open file");
	}
	else
	{
		/// <summary>insert all the members to the file
		unsigned long membersListSize = membersList.size();
		file.write(reinterpret_cast<char*>(&membersListSize), sizeof(int));
		for (int i = 0; i < membersListSize; i++) {
			membersList[i]->Serialize(file);
		}
		/// <summary>insert all the fan pages to the file
        unsigned long fanPageListSize = fanPageList.size();
		file.write(reinterpret_cast<char*>(&fanPageListSize), sizeof(int));
		for (int i = 0; i < fanPageListSize; i++) {
			fanPageList[i]->Serialize(file);
			fanPageList[i]->SerializeBulletinBoard(file);
		}
		/// <summary>this part insert to the file Who was a friend of whom
		for (int i = 0; i < membersListSize; i++) {
			membersList[i]->WriteConnections(file);

		}
		/// <summary>this part insert to the file Who liked each fan page
		for (int i = 0; i < fanPageListSize; i++) {
			fanPageList[i]->WriteConnections(file);
		}
	}
	file.close();
}

void FaceBook::BinFileExtractData()
{
	std::ifstream file("MyFile.bin", std::ios::binary);
	if (!file) { //check if the file opened successfully
		return;
	}
	else if (file.peek() != EOF)
	{
		/// <summary> extract all the members from the file
		int MemberSize, FanPageSize;
		file.read(reinterpret_cast<char*>(&MemberSize), sizeof(int));
		for (int i = 0; i < MemberSize; i++) {
			auto* m = new Member;
			m->fillData(file);
			m->getStatusFromBin(file);
			membersList += m;
		}
		/// <summary> extract all the fan pages from the file
		file.read(reinterpret_cast<char*>(&FanPageSize), sizeof(int));
		for (int i = 0; i < FanPageSize; i++) {
			auto* f = new FanPage;
			f->fillData(file);
			f->getStatusFromBin(file);
			fanPageList += f;
		}
		/// <summary>this part tells Who was a friend of whom
		for (int i = 0; i < MemberSize; i++) {
			int size, length;
			char* NameTemp;
			file.read(reinterpret_cast<char*>(&size), sizeof(int));
			for (int j = 0; j < size; j++) {
				file.read(reinterpret_cast<char*>(&length), sizeof(int));
				NameTemp = new char[length + 1];
				file.read(NameTemp, length);
				NameTemp[length] = '\0';
				membersList[i]->addFriend(membersList[findEntityByName(NameTemp)]);
				delete[] NameTemp;
			}
		}
		/// <summary> this part tells Who liked each fan page
		for (int i = 0; i < FanPageSize; i++) {
			int size, length;
			char* NameTemp;
			file.read(reinterpret_cast<char*>(&size), sizeof(int));
			for (int j = 0; j < size; j++) {
				file.read(reinterpret_cast<char*>(&length), sizeof(int));
				NameTemp = new char[length+1];
				file.read(NameTemp, length);
				NameTemp[length] = '\0';
				fanPageList[i]->addFriend(membersList[findEntityByName(NameTemp)]);
				delete[] NameTemp;
			}
		}
		file.close();
	}
}



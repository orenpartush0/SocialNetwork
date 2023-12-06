#include "Status.h"
#include "FanPage.h"
#include "Member.h"
#include "exception.h"


void FanPage::addFriend(Member* member){ 
    // this function is adding a member who liked the fan page to the fan page list of "followers".
    friendsArr.push_back(member);
    member->addFanPage(this);
}

void FanPage::removeFriend(Member* member){ 
    // this function is removing a member who disliked the fan page from the fan page list of "followers".
    friendsArr.erase(std::remove_if(friendsArr.begin(), friendsArr.end(),
                                     [member](const auto & obj) { return obj == member; }));
    member->removeFanPage(this);
}

void FanPage::printAllStatuses() const { 
    // this function prints all the statuses that a fan page ever published.
        if (BulletinBoard.empty())
            throw Invalid_choice("This fan page doesn't have any Status yet!\n");
        std::for_each(BulletinBoard.begin(), BulletinBoard.end(), [](const auto& obj) { obj->printStatus(); });
}



bool FanPage::checkIfWeAreFriends(const string& Name) const { 
    // this function checks if 2 users already friends.
    return std::any_of(friendsArr.begin(), friendsArr.end(),
        [Name](const auto& mem) { return *mem == Name; });
}

void FanPage::printLastFriendsStatuses() const { 
    // this function prints the 10 most recent statuses of all the friend of the member.
    for (const auto& it : friendsArr) {
        cout << "The 10 most recent Statuses of " << it->getName() << ": " << endl;
        if (it->BulletinBoard.empty())
            cout << "This member has no status yet!\n" << endl;
        else {
            int count = RECENT;
            for (auto iterator = it->BulletinBoard.rbegin(); count > 0 && iterator < it->BulletinBoard.rend(); ++iterator)
            {
                (*iterator)->printStatus();
                count--;
            }
        }
    }
}

void FanPage::Serialize(fstream& file) {
    //insert fan page data to bin file
    unsigned long len = name.size();
    file.write(reinterpret_cast<char*>(&len), sizeof(int));
    file.write(name.c_str(), len);
}

void FanPage::SerializeBulletinBoard(fstream& file) const {
    //insert fan page status to bin fil
    unsigned long size = BulletinBoard.size();
    file.write(reinterpret_cast<char*>(&size), sizeof(int));
    for (int i = 0; i < size; i++) {
        BulletinBoard[i]->Serialize(file);
    }
}

void FanPage::WriteConnections(fstream& file) const {
    //fill the file every connection between members or between member and a fan page
    unsigned long tempSize = friendsArr.size();
    file.write(reinterpret_cast<char *>(&tempSize), sizeof(int));
    for (const auto *it: friendsArr) {
        const char *temp = it->getName().c_str();
        unsigned long  size = it->getName().size();
        file.write(reinterpret_cast<char *>(&size), sizeof(int));
        file.write(temp, (long)size);
    }
}

void FanPage::fillData(std::ifstream& file)
{
    //fill FanPage data to bin file
    int namLen;
    char* buffer;
    file.read(reinterpret_cast<char*>(&namLen), sizeof(int));
    buffer = new char[namLen+1];
    file.read(buffer, namLen);
    buffer[namLen] = '\0';
    name = buffer;
    delete[] buffer;
}
void FanPage::getStatusFromBin(std::ifstream& file)
{
    //extract FanPage status from bin file
    int BulletinBoardSize, contentLen, DateLen;
    char* buffer=nullptr;
    int typeLen;
    char* type=nullptr;

    file.read(reinterpret_cast<char*>(&BulletinBoardSize), sizeof(int));
    for (int j = 0; j < BulletinBoardSize; j++) {
        file.read(reinterpret_cast<char*>(&typeLen), sizeof(int));
        type = new char[typeLen];
        file.read(type, typeLen);
        string Type(type, typeLen);
        delete[]type;
        file.read(reinterpret_cast<char*>(&contentLen), sizeof(int));
        buffer = new char[contentLen];
        file.read(buffer, contentLen);
        string content(buffer, contentLen);
        delete[] buffer;
        file.read(reinterpret_cast<char*>(&DateLen), sizeof(int));
        buffer = new char[DateLen];
        file.read(buffer, DateLen);
        string date(buffer, DateLen);
        delete[] buffer;
        if(Type==STATUS_)
            this->addStatus(new Status(content, date));
        else if(Type ==IMAGE_)
            this->addStatus(new Image(content, date));
        else if (Type == VIDEO_)
            this->addStatus(new Video(content, date));
    }
}
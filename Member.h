#ifndef FACEBOOK_MEMBER_H
#define FACEBOOK_MEMBER_H
#include "Status.h"

struct DOB {
    int day ;
    int month ;
    int year ;
    friend std::ostream& operator<<( std::ostream& os, const DOB& obj) { os << obj.day << "." << obj.month
                                                                            << "." << obj.year << endl;return os;};
    // this function override the "<<" operator in order to print the member birthdate.
};

class Member :public FanPage {

    DOB birthDate;
    vector<FanPage*> fanPagesArr;

public:
    Member():birthDate({0,0,0}) {};
    // this is the default constructor of the class "Member".
    Member(string &&Name, DOB &&BirthDate)  : FanPage(Name) , birthDate(BirthDate){}
    // this is the constructor of the class "Member" , initializing all the variables of the class with temporary variables.
    Member(string &Name, DOB &BirthDate)  : FanPage(Name) , birthDate(BirthDate){}
    // this is the constructor of the class "Member" , initializing all the variables of the class.
    void addFanPage(FanPage* fanPage) {fanPagesArr += fanPage;}// this function is adding the fun pages that a member liked to his fan page list.
    void removeFanPage(const FanPage* fanPage);
    void printFanPages() const;
    const vector<FanPage*>& getLikedFanPages() const { return  fanPagesArr; }
    // this function gets the liked fan pages list of a member.
    const DOB& getBirthDate() const { return birthDate; }
    // this function gets the birthdate of a member.
    void addFriend(Member* member) override;
    // this function is adding to the friends list of each member ,  that wanted to connect , the other person.
    void removeFriend(Member* member) override;
    // this function is removing  the friends  from each other list of members.
    const Member& operator += (Member* newFriend) override {addFriend(newFriend);return *this;}
    // this function override the "+=" operator in order to add a new friend to the friends list.
    const Member& operator += (FanPage* newPage) {addFanPage(newPage);return *this;}
    // this function override the "+=" operator in order to add a new liked fan page to the fan pages list.
    const Member& operator += (Status*&& newStatus) override {addStatus(newStatus);return *this;}
    // this function override the "+=" operator in order to add a new status to the member feed.
    const Member& operator-= (Member* mem ) override {removeFriend(mem);return *this;}
    // this function override the "-=" operator in order to remove a friend from the friends list.
    friend const vector<Member*>& operator+=(vector<Member*>& MembersList, Member*& obj ) {MembersList.push_back(obj);return MembersList;}
    // this function override the "+=" operator in order to add a new friend to the member friends list.
    friend const vector<Member*>& operator+=(vector<Member*>& MembersList, Member*&& obj ) {MembersList.push_back(obj);return MembersList;}
    // this function override the "+=" operator in order to add a new member to the systems members list.
    void Serialize(fstream& file) override { FanPage::Serialize(file); file.write(reinterpret_cast<char*>(&birthDate), sizeof(DOB)); FanPage::SerializeBulletinBoard(file); };
    //insert member data to bin file
    void fillData(std::ifstream& file) override { FanPage::fillData(file); file.read(reinterpret_cast<char*>(&birthDate), sizeof(DOB));};
    //extract to a member data from bin file
    ~Member()  = default;
    // this is the default destructor of the class "Member".
};

#endif //FACEBOOK_MEMBER_H

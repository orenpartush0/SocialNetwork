
#ifndef FACEBOOK_FAN_PAGE_H
#define FACEBOOK_FAN_PAGE_H
#include "Status.h"
#include "image.h"
#include "video.h"

#define RECENT 10
#define MEMBER 1
#define FAN_PAGE 2

class Member;
class Status;

class FanPage{
    string name;
    vector<Status*> BulletinBoard;
protected:
    vector<Member*> friendsArr;
public:
    FanPage() = default;
    explicit FanPage(string&& Name):name(std::move(Name)) {} 
    // this a constructor of the class "Fan Page" , initializing the name with a temporary object.
    explicit FanPage(string& Name):name(Name) {}  
    // this a constructor of the class "Fan Page" , initializing the name of the fan page.
    const vector<Member*>& getFriendsArr()  {return friendsArr;} 
    // this function gets the friends list
    const string& getName() const { return name; }
    // this function gets the name of a member.
    vector<Status*>& getBulletinBoard() { return BulletinBoard; }
    // this function gets the status list of a member.
    virtual void addFriend(Member* member);
    virtual void removeFriend(Member* member);
    void addStatus(Status* status){BulletinBoard.push_back(status);} 
    //  this function is adding a new status that the fan page published to the status list.
    void printAllStatuses() const;
    bool checkIfWeAreFriends(const string& name) const;
    void printLastFriendsStatuses() const;
    virtual const FanPage& operator+=(Member* newFan ) {addFriend(newFan);return *this;}
    // this overload function override the "+=" operator in order to add a new member who liked the fan page , to the friends list.
    virtual const FanPage& operator+=(Status*&& newStatus ) {addStatus(newStatus);return *this;}
    // this overload function override the "+=" operator in order to add a new status to the fan page feed.
    bool operator > (const FanPage& other ) const {return friendsArr.size() > other.friendsArr.size();}
    // this overload function override the ">" operator in order to compare 2 fan pages sizes.
    bool operator == (const FanPage& page ) const {return name == page.name;}
    // this overload function override the "==" operator in order to compare 2 fan pages names.
    bool operator == (const string& Name ) const {return name ==Name;}
    // this overload function override the "==" operator in order to compare fan page name with string.
    virtual const FanPage& operator-= (Member* newFan ){removeFriend(newFan);return *this;}
    // this overload function override the "-=" operator in order to remove a member from the fan page members list.
    friend const vector<FanPage*>& operator+=(vector<FanPage*>& fanPagesList, FanPage*& obj ) {fanPagesList.push_back(obj);return fanPagesList;}
    // this overload function override the "+=" operator in order to add new fan page to the systems fan page list.
    friend const vector<FanPage*>& operator+=(vector<FanPage*>& FanPageList, FanPage*&& obj ) {FanPageList.push_back(obj);return FanPageList;}
    // this overload function override the "+=" operator in order to add new fan page to the systems fan page list.
    friend std::ostream& operator<<(std::ostream& os, const FanPage& obj) {os << obj.name; return os;};

    virtual void Serialize(fstream& file);
    //insert fan page data to bin file
    void SerializeBulletinBoard(fstream& file) const;
    //insert fan page status to bin fil
    void WriteConnections(fstream& file) const;
    //fill the file every connection between members or between member and a fan page
    virtual void fillData(std::ifstream& file);
    //fill FanPage data to bin file
    void getStatusFromBin(std::ifstream& file);
    //extract FanPage status from bin file
    ~FanPage() = default; 
    // this is the destructor of the class.
};

#endif //FACEBOOK_FAN_PAGE_H


#ifndef FACEBOOK_FACEBOOK_H
#define FACEBOOK_FACEBOOK_H

#include "Status.h"
#include "FanPage.h"
#include "Member.h"
#include "image.h"
#include "video.h"
#include <algorithm>

#define RETURN_MAIN_PAGE 3
#define RECENT 10
#define CHECK_DAY(x) (x < 1 || x > 31)
#define CHECK_MONTH(x) (x < 1 || x > 12)
#define CHECK_YEAR(x) (x < 1900 || x > 2022)
#define TEXT 1
#define IMAGE 2
#define VIDEO 3
#define MAIN 0
#define CONTINUE 1



class FaceBook {
    vector<Member*> membersList;
    vector<FanPage*> fanPageList;
    bool ActiveFaceBook;
public:
    FaceBook();
     const FaceBook& operator = (const FaceBook& other) = delete;
    // there is no need for the "operator" so we won't make it possible to avoid errors in the future.
    FaceBook(const FaceBook& _faceBook) = delete;
    // there is no need for a copy constructor.
    FaceBook(FaceBook&& _faceBook) = delete; 
    // there is no need for a move constructor.
    bool getActiveFaceBook() const {return ActiveFaceBook;} ; 
    // this function tells if the system should keep working or
    // the user preform a "log out"
    void initialProgram();
    static void  printIntro() {cout << "Hello and welcome to facebook! " << endl;};
    // this function prints
    // the intro to facebook when the system turns on.
    static void printEnterUsername() {cout << "Please enter user name:" << endl;};
    // this function prints
    // the request from the user to enter a username.
    static void printEnterFanPageName() {cout << "Please enter fan page name: " << endl;}; 
    // this function print the request from the user to enter a fan page name.
    int static printMenu();
    void static performUserSelection(FaceBook &faceBook);
    static string getDateAndTime();
    static DOB fillDate();
    static void PrintChoices();
    static void PrintExitLine();
    void adduser();
    int findEntityByName(const string& name, bool member = true) const;
    void addFanPage();
    void addStatus();
    void showStatus() const;
    void show10status() const;
    void friendship(bool remove = false);
    void AddOrRemoveFanPage(bool dislike = false);
    void ShowAllEntities() const;
    void ShowMembers() const;
    void Exit();
    static void printStatusChoices();
    static Status* createStatus(const string& content,const string& Date,int choice);
    void static PrintWrongSelection();
    void checkName(const string& Name , bool member = true) const;
    bool checkLike(const int &index1,const string &fanPageName) const;
    bool inputIntegrity(int& index,bool member = true,bool flag=true) const;
    void static PrintChoiceOption(bool member = true);
    void PrintEntity(const int &i , bool member = true) const;
    static string alreadyUsed();
    void DataToBinFile()const;
    //convert all the data in to bin File
    void BinFileExtractData();
    //extract all the data from bin file
    ~FaceBook(); 
    // this is the destructor of the "FaceBook" class.
};


#endif //FACEBOOK_FACEBOOK_H

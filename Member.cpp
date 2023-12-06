#include "Status.h"
#include "FanPage.h"
#include "Member.h"
#include "exception.h"

void Member::removeFanPage(const FanPage* fanPage) { // this function is removing fan pages that a member has dislike from his fan page list.
	fanPagesArr.erase(std::remove_if(fanPagesArr.begin(), fanPagesArr.end(),
		[fanPage](const FanPage* obj) { return *obj == *fanPage; }));
}

void Member::printFanPages() const { // this function is printing all the fan pages that a member liked.
	cout << "Your liked fan pages are: " << endl;
	std::for_each(fanPagesArr.begin(), fanPagesArr.end(), [](const auto& obj) { cout << obj << endl; });
}

void Member::addFriend(Member* member) { // this function is adding to the friends list of each member ,  that wanted to connect , the other person.
	if (this->checkIfWeAreFriends(member->getName())) {
		return;
	}
	friendsArr += member;
	member->addFriend(this);
}

void Member::removeFriend(Member* member) { // this function is removing from the friends list of each member ,  that wanted to remove the connection from each other , the other person.
	if (!(this->checkIfWeAreFriends(member->getName()))) {
		return;
	}
	friendsArr.erase(std::remove_if(friendsArr.begin(), friendsArr.end(),
		[member](const Member* obj) { return *obj == *member; }));
	member->removeFriend(this);
}




#include "Status.h"

void Status::Serialize(fstream& file) const
{
	int typeNameLen = STATUS_LEN;//strlen("Status")
	string typeName = STATUS_;
	file.write(reinterpret_cast<char*>(&typeNameLen), sizeof(int));
	file.write(typeName.c_str(), typeNameLen);
	unsigned long size1 = content.length();
	file.write(reinterpret_cast<char*>(&size1), sizeof(int));
	file.write(content.c_str(), (long)content.length());
    unsigned long size2 = DateAndTime.length();
	file.write(reinterpret_cast<char*>(&size2), sizeof(int));
	file.write(DateAndTime.c_str(), (long)DateAndTime.length());
}

void Status::printStatus()const
{
	cout << content << endl;
	cout << "This status published at: " << DateAndTime;
	cout << "This status is shown black&white with using a simple program" << endl;
	cout << "----------------------------------------------------------" << endl;
}
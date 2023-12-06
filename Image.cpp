#include "image.h"

void Image::Serialize(fstream& file) const
{
	int typeNameLen = IMAGE_VIDEO_LEN;
	string typeName = IMAGE_;
	file.write(reinterpret_cast<char*>(&typeNameLen), sizeof(int));
	file.write(typeName.c_str(), typeNameLen);
	unsigned long size = getContent().length();
	file.write(reinterpret_cast<char*>(&size), sizeof(int));
	file.write(getContent().c_str(), (long)getContent().length());
    unsigned long size1 = getDate().length();
	file.write(reinterpret_cast<char*>(&size1), sizeof(int));
	file.write(getDate().c_str(), (long)getDate().length());
}
void Image::printStatus()const
{
	cout << *this << endl;
	cout << "This image published at: " << this->getDate();
	cout << "This image is colorful and is shown with using a simple program" << endl;
	cout << "----------------------------------------------------------" << endl;

}
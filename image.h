#pragma once
#include "Status.h"

class Image :public Status
{
public:
	Image(const string& _content, const string& Date) :Status(_content, Date) {};
    void printStatus() const override;
    void Serialize(fstream& file) const override;
	~Image() override = default;
};
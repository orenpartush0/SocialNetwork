#pragma once
#include "Status.h"

class Video :public Status
{
public:
	Video(const string& _content, const string& Date) :Status(_content, Date) {};
    void printStatus() const override;
    void Serialize(fstream& file) const override;
	~Video() override = default;
};
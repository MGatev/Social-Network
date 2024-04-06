#include "UpDownVotes.h"
#include <iostream>

namespace {
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

void UpDownVotes::copyFrom(const UpDownVotes& other) {
	upVotesCapacity = other.upVotesCapacity;
	downVotesCapacity = other.downVotesCapacity;
	upVotesCount = other.upVotesCount;
	downVotesCount = other.downVotesCount;
	upVotes = new int[upVotesCapacity];
	downVotes = new int[downVotesCapacity];
	for (size_t i = 0; i < upVotesCount; i++)
	{
		upVotes[i] = other.upVotes[i];
	}
	for (size_t i = 0; i < downVotesCount; i++)
	{
		downVotes[i] = other.downVotes[i];
	}
}

void UpDownVotes::moveFrom(UpDownVotes&& other) noexcept {
	upVotesCapacity = other.upVotesCapacity;
	downVotesCapacity = other.downVotesCapacity;
	upVotesCount = other.upVotesCount;
	downVotesCount = other.downVotesCount;
	upVotes = other.upVotes;
	downVotes = other.downVotes;
	other.upVotes = other.downVotes = nullptr;
	other.upVotesCapacity = other.upVotesCount = other.downVotesCapacity = other.downVotesCount = 0;
}

void UpDownVotes::free() {
	if (upVotes != nullptr)
		delete[] upVotes;
	if (downVotes != nullptr)
		delete[] downVotes;
}

UpDownVotes::UpDownVotes(const UpDownVotes& other) {
	copyFrom(other);
}
UpDownVotes& UpDownVotes::operator=(const UpDownVotes& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
UpDownVotes::UpDownVotes(UpDownVotes&& other) noexcept {
	moveFrom(std::move(other));
}
UpDownVotes& UpDownVotes::operator=(UpDownVotes&& other) noexcept {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void UpDownVotes::resizeUpVotes() {
	int* temp = new int[upVotesCapacity *= 2];
	for (size_t i = 0; i < upVotesCount; i++)
	{
		temp[i] = upVotes[i];
	}
	delete[] upVotes;
	upVotes = temp;
	temp = nullptr;
}

void UpDownVotes::resizeDownVotes() {
	int* temp = new int[downVotesCapacity *= 2];
	for (size_t i = 0; i < downVotesCount; i++)
	{
		temp[i] = upVotes[i];
	}
	delete[] downVotes;
	downVotes = temp;
	temp = nullptr;
}

UpDownVotes::UpDownVotes() {
	upVotes = new int[upVotesCapacity];
	downVotes = new int[downVotesCapacity];
}

UpDownVotes::~UpDownVotes() {
	free();
}

bool UpDownVotes::addUpVote(const size_t userID) {
	if (upVotesCapacity == upVotesCount)
		resizeUpVotes();

	upVotes[upVotesCount++] = static_cast<int>(userID);
	return true;
}

bool UpDownVotes::addDownVote(const size_t userID) {
	if (downVotesCapacity == downVotesCount)
		resizeDownVotes();

	downVotes[downVotesCount++] = static_cast<int>(userID);
	return true;
}

bool UpDownVotes::removeUpVote(const size_t userID) {
	for (size_t i = 0; i < upVotesCount; i++)
	{
		if (upVotes[i] == userID)
		{
			upVotes[i] = -1;
			swap(upVotes[i], upVotes[upVotesCount - 1]);
			upVotesCount--;
			return true;
		}
	}
	return false;
}

bool UpDownVotes::removeDownVote(const size_t userID) {
	for (size_t i = 0; i < downVotesCount; i++)
	{
		if (downVotes[i] == userID) {
			downVotes[i] = -1;
			swap(downVotes[i], downVotes[upVotesCount - 1]);
			downVotesCount--;
			return true;
		}
	}

	return false;
}

size_t UpDownVotes::getUpVotesCount()const {
	return upVotesCount;
}

size_t UpDownVotes::getDownVotesCount()const {
	return downVotesCount;
}

const int* UpDownVotes::getUpVotes()const {
	return upVotes;
}

const int* UpDownVotes::getDownVotes()const {
	return downVotes;
}

void UpDownVotes::readFromBinaryFile(std::ifstream& input) {
	size_t upVotesCount = 0, downVotesCount = 0;
	input.read((char*)&upVotesCount, sizeof(upVotesCount));
	int readTemp = 0;
	for (size_t i = 0; i < upVotesCount; i++)
	{
		input.read((char*)&readTemp, sizeof(readTemp));
		addUpVote(readTemp);
	}

	input.read((char*)&downVotesCount, sizeof(downVotesCount));
	for (size_t i = 0; i < downVotesCount; i++)
	{
		input.read((char*)&readTemp, sizeof(readTemp));
		addDownVote(readTemp);
	}

}
void UpDownVotes::writeToBinaryFile(std::ofstream& output) const {
	output.write((const char*)&upVotesCount, sizeof(upVotesCount));
	for (size_t i = 0; i < upVotesCount; i++)
		output.write((const char*)&upVotes[i], sizeof(int));

	output.write((const char*)&downVotesCount, sizeof(downVotesCount));
	for (size_t i = 0; i < downVotesCount; i++)
		output.write((char*)&downVotes[i], sizeof(int));
}
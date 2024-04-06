#pragma once
#include <fstream>

class UpDownVotes {

	//IDs of users who upVoted
	int* upVotes = nullptr;
	size_t upVotesCount = 0;
	size_t upVotesCapacity = 4;

	//IDs of users who downVotes
	int* downVotes = nullptr;
	size_t downVotesCount = 0;
	size_t downVotesCapacity = 4;

	void free();
	void copyFrom(const UpDownVotes& other);
	void moveFrom(UpDownVotes&& other)noexcept;
	void resizeUpVotes();
	void resizeDownVotes();

public:
	UpDownVotes();
	UpDownVotes(const UpDownVotes& other);
	UpDownVotes& operator=(const UpDownVotes& other);
	UpDownVotes(UpDownVotes&& other)noexcept;
	UpDownVotes& operator=(UpDownVotes&& other) noexcept;
	~UpDownVotes();

	bool addUpVote(const size_t userID);
	bool addDownVote(const size_t userID);
	bool removeUpVote(const size_t userID);
	bool removeDownVote(const size_t userID);

	size_t getUpVotesCount()const;
	size_t getDownVotesCount()const;
	
	const int* getUpVotes()const;
	const int* getDownVotes()const;

	void readFromBinaryFile(std::ifstream& input);
	void writeToBinaryFile(std::ofstream& output) const;
};
#pragma once
#include <string>

using namespace std;

class Create
{
public:
	bool TryToCreate();
	Create();

private:
	bool ItHasPrivilege();
	bool CheckIfUsernameExist();
	bool CheckIfTypeExist();
	bool CheckAmount();
	string userName;
	string userType;
	float initialAmount;
};


#include "stdafx.h"
#include "Handle.h"
#include "Create.h"
#include "Login.h"
#include "Delete.h"
#include "Addcredit.h"

Handle::Handle()
{
}


Handle::~Handle()
{
}

int Handle::create()
{
	return createUser();
}

int Handle::login()
{
	return loginUser();
}

int Handle::addcredit()
{
	return addtouser();
}

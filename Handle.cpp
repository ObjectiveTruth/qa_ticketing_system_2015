#include "stdafx.h"
#include "Handle.h"
#include "Create.h"
#include "Delete.h"

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

int Handle::remove()
{
	return removeUser();
}

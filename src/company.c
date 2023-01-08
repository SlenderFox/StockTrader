#include "company.h"
#include <stdlib.h> // malloc, free
#include <memory.h> // memmove

void
st_company_construct (st_company **_company, char *_name)
{
	*_company = malloc (sizeof (st_company));
	(*_company)->value = 0;
	(*_company)->owned_stocks = 0;
	st_company_name_set (*_company, "Untitled");
}

void
st_company_destruct (st_company *_company)
{
	free (_company);
}

void
st_company_update (st_company *_company)
{
	++_company->value;
}

void
st_company_name_set (st_company *_company, char *_name)
{
	int namelen = strlen (_name);
	int size = (namelen < ST_COMPANY_NAME_MAX) ? namelen : ST_COMPANY_NAME_MAX;
	memmove (_company->name, _name, size);
	if (size == ST_COMPANY_NAME_MAX)
	{
		_company->name[ST_COMPANY_NAME_MAX - 1] = '\0';
	}
}

char *
st_company_name_get (st_company *_company)
{
	return _company->name;
}

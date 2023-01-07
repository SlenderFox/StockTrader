#pragma once

#define ST_COMPANY_NAME_MAX 32

typedef struct st_company
{
	int value;
	int owned_stocks;
	char name[ST_COMPANY_NAME_MAX];
} st_company;

void
st_company_construct (st_company **_company, char *_name);

void
st_company_destruct (st_company *_company);

void
st_company_update (st_company *_company);

void
st_company_name_set (st_company *_company, char *_name);

char*
st_company_name_get (st_company *_company);

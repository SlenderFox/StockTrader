#pragma once

#define ST_COMPANY_NAME_MAX 32

/** A company that can have stocks bought and sold from.
 * Every company havea value that is updated with each timestep,
 * a count of how many stocks in the company are owned by the player,
 * and a name.
 */
typedef struct st_company
{
	int value;
	int owned_stocks;
	char name[ST_COMPANY_NAME_MAX];
} st_company;

/** Allocate memory for the company struct and init a name
 * @param _company Output pointer to the company
 * @param _name The name for the company
 */
void
st_company_construct (st_company **_company, char *_name);

/** Free the memory of the company struct
 * @param _company The company
 */
void
st_company_destruct (st_company *_company);

/** Will update the value of the company struct
 * @param _company The company
 */
void
st_company_update (st_company *_company);

/** Set the name of a company
 * Has overflow protection
 * @param _company
 * @param _name
 */
void
st_company_name_set (st_company *_company, char *_name);

/** Safe and easy way to get the name of a company
 * The name is stored in a char array which can cause some issues
 * @param _company The company to get the name from
 * @return [char*] The name as a char*
 */
char*
st_company_name_get (st_company *_company);

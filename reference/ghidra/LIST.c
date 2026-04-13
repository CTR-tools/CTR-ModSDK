
// LIST_Clear
void FUN_80031734(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


// LIST_AddFront
// param_1 is linkedList
// param_2 is item
void FUN_80031744(int **param_1,int *param_2)

{
  int *piVar1;

  // If pointer is not nullptr
  if (param_2 != (int *)0x0)
  {
	// newMember->prev
    param_2[1] = 0;

	// list->first
	piVar1 = param_1[0];

	// newMember->next = list->first
	param_2[0] = piVar1;

	// if there is no first,
	// making this the first item
	if (piVar1 == (int *)0x0)
	{
	  // list->last = newMember
      param_1[1] = param_2;
    }

	// if a member is already on the list
	else
	{
	  // list->first->prev = newMember
      param_1[0]->offset4 = param_2;
    }

	// list->first = newMember
    param_1[0] = param_2;

	// increase member count
    param_1[2] = param_1[2] + 1;
  }
  return;
}


// LIST_AddBack
// param_1 is linkedList
// param_2 is item
void FUN_80031788(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;

  // If pointer is not nullptr
  if (param_2 != (undefined4 *)0x0)
  {
	// newMember->next
    param_2[0] = 0;

	// list->last
    iVar1 = param_1[1];

	// newMember->prev = last
    param_2[1] = iVar1;

	// if list->last does not exist,
	// making this the first member of list
	if (iVar1 == 0)
	{
	  // list->first = newMember
      *(undefined4 **)param_1 = param_2;
    }

	// if list->last exists
	else
	{
	  // list->last->next = newMember
      param_1[1]->offset0 = param_2;
    }

	// list->last = newMember
    param_1[1] = param_2;

	// increase member count
    param_1[2] = param_1[2] + 1;
  }
  return;
}


// LIST_GetNextItem
undefined4 FUN_800317cc(undefined4 *param_1)

{
  return *param_1;
}


// LIST_GetFirstItem
undefined4 FUN_800317d8(undefined4 *param_1)

{
  return *param_1;
}


// LIST_RemoveMember
int * FUN_800317e4(int *param_1,int *param_2)

{
  // if pointer is valid
  if (param_2 != (int *)0x0)
  {
	// list->first is valid
    if (*param_1 != 0)
	{
	  // if member->prev is null
	  // member is the first on list
      if (param_2[1] == (int *)0x0)
	  {
		// list->first = member->next
        param_1[0] = param_2[0];
      }

	  // if member->prev is valid
	  else
	  {
		// member->prev->next = member->next
        param_2[1]->offset0 = param_2[0];
      }

	  // if member->next is null
	  // member is last on list
      if (param_2[0] == 0)
	  {
		// list->last = member->prev
        param_1[1] = param_2[1];
      }

	  // if member->next is valid
	  else
	  {
		// member->next->prev = member->prev
        param_2[0]->offset4 = param_2[1];
      }

	  // decrease item count
      param_1[2] = param_1[2] + -1;
    }

	// erase links
    *param_2 = 0;
    param_2[1] = 0;
  }
  return param_2;
}


// LIST_RemoveFront
int * FUN_8003186c(int **param_1)

{
  int **ppiVar1;

  // member = list->first
  ppiVar1 = (int *)param_1[0];

  // This was a lazy copy/paste of LIST_RemoveMember,
  // replacing the parameterized member with first member

  // if member exist
  if (ppiVar1 != (int **)0x0)
  {
	// member->prev is null
    if (ppiVar1[1] == (int *)0x0)
	{
	  // list->first = member->next
      param_1[0] = ppiVar1[0];
    }

	// if member->prev exists
    else
	{
	  // member->prev->next = member->next
      ppiVar1[1]->offset0 = ppiVar1[0];
    }

	// if member->next is null
    if (*ppiVar1 == (int *)0x0)
	{
	  // list->last = member->prev
      param_1[1] = ppiVar1[1];
    }

	// if member->next is valid
    else
	{
	  // member->next->prev = member->prev
      ppiVar1[0]->offset4 = ppiVar1[1];
    }

	// decrease item count
    param_1[2] = param_1[2] + -1

	// erase links
    *(int *)ppiVar1 = 0;
    *(int *)(ppiVar1 + 1) = 0;
  }
  return (int *)ppiVar1;
}


// only from 231
// LIST_RemoveBack
int * FUN_800318ec(int *param_1)

{
  int *piVar1;

  // This was a lazy copy/paste of LIST_RemoveMember,
  // replacing the parameterized member with last member

  // member = list->last
  piVar1 = (int *)param_1[1];

  // if it exists
  if (piVar1 != (int *)0x0)
  {
	// if list->first exists
    if (*param_1 != 0)
	{
	  // if member->prev is null
	  // member is the first on list
      if ((int *)piVar1[1] == (int *)0x0)
	  {
		// list->first = member->next
        param_1[0] = piVar1[0];
      }

	  // if member->prev is valid
      else
	  {
		// member->prev->next = member->next
        piVar1[1]->offset0 = piVar1[0];
      }

	  // if member->next is null
	  // member is last on list
      if (*piVar1 == 0)
	  {
		// list->last = member->prev
        param_1[1] = piVar1[1];
      }

      else
	  {
		// member->next->prev = member->prev
        piVar1[0]->offset4 = piVar1[1];
      }

	  // decrease item count
      param_1[2] = param_1[2] + -1;
    }

	// erase links
    *piVar1 = 0;
    piVar1[1] = 0;
  }
  return piVar1;
}


// LIST_Init
// param_1 pointer to linked list
// param_2 pointer to member
// param_3 size of each member
// param_4 number of members
void FUN_8003197c(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;

  // reduce remainig amount by one
  iVar1 = param_4 + -1;

  // if there is at least one member
  if (param_4 != 0)
  {
	// keep going until done
    do
	{
	  // LIST_AddBack
      // add to freeItems
      FUN_80031788(param_1,param_2);

	  // reduce remaining amount by one
      iVar1 = iVar1 + -1;

	  // increment pointer to next member
	  param_2 = param_2 + param_3;

    } while (iVar1 != -1);
  }
  return;
}

#include <common.h>

void DECOMP_RB_Turtle_ThTick(struct Thread* t)
{
	struct Turtle* turtleObj;
	struct Instance* turtleInst;
	int currTimer;
	int newTimer;
	
	turtleObj = t->object;
	turtleInst = t->inst;
	
	// 0 from moment it hits bottom to moment it hits top
	if(turtleObj->direction == 0)
	{
		// use timer variables for milliseconds
		
		currTimer = turtleObj->timer;
		
		// if less than 1.0 seconds
		// wait for rise
		if(currTimer < 0x3c0)
		{
			// increment
			currTimer += sdata->gGT->elapsedTimeMS;
			
			// set
			turtleObj->timer = currTimer;
			
			// == fixed Naughty Dog bug ==
			
			#if 0
			
			// Naughty Dog "intended" this
			if(currTimer >= 0x3c0)
			{
				turtleObj->timer = 0x3c0;
				PlaySound3D(0x7d, turtleInst);
			}
			
			#else
				
			// but for the sake of a functionally
			// identical decomp that represents 
			// the "shipped" game
			
			if(currTimer > 0x3c0)
			{
				turtleObj->timer = 0x3c0;
			}
			
			#endif
			
		}
		
		// if more than one second has passed
		// time to rise
		else
		{
			// turtle not fully down,
			// impacts jumping
			turtleObj->state = 1;
			
			// use timer variables for frame counting
			
			// decrement frame (make turtle rise)
			currTimer = turtleInst->animFrame - 1;
			
			// end of animation
			if(currTimer < 1)
			{
				// reset direction
				turtleObj->direction = 1;
				
				// reset timer
				turtleObj->timer = 0;
			}
			
			// playing animation
			else
			{
				// decrement frame (make turtle rise)
				turtleInst->animFrame = currTimer;
			}
		}
	}
	
	// 1 from moment it hits top to moment it hits bottom
	else
	{
		// use timer variables for milliseconds
		
		currTimer = turtleObj->timer;
		
		// if less than 1.0 seconds
		// wait for fall
		if(currTimer < 0x3c0)
		{
			// increment
			currTimer += sdata->gGT->elapsedTimeMS;
			
			// set
			turtleObj->timer = currTimer;
			
			// == fixed Naughty Dog bug ==
			
			if(currTimer > 0x3c0)
			{
				turtleObj->timer = 0x3c0;
			}
		}
		
		// if more than one second has passed
		// time to fall
		else
		{			
			// use timer variables for frame counting
			
			// increment frame (make turtle fall)
			currTimer = turtleInst->animFrame + 1;
			
			// playing animation
			if(currTimer < DECOMP_INSTANCE_GetNumAnimFrames(turtleInst, 0))
			{
				// increment frame (make turtle fall)
				turtleInst->animFrame = currTimer;
			}
			
			// finished animation
			else
			{
				// reset direction
				turtleObj->direction = 0;
				
				// reset timer
				turtleObj->timer = 0;
				
				// turtle is "fully" down
				turtleObj->state = 0;
			}
		}
	}
}

int DECOMP_RB_Turtle_LInC(struct Instance* inst, struct Thread* driverTh)
{
	int speed;
	int jumpType;
	struct Driver* driver;
	
	driver = driverTh->object;
	
	// absolute value
	speed = driver->speedApprox;
	if(speed < 0) speed = -speed;
	
	if(speed > 0x1400)
	{
		// small jump
		jumpType = 1;
		
		if(
			// turtleObj->state != FULLY_DOWN
			((struct Turtle*)inst->thread->object)
			->state != 0
		)
		{
			// big jump
			jumpType = 2;
		}
		
		// make the player jump
		driver->forcedJump_trampoline = jumpType;
		
		return 2;
	}
	
	return 1;
}

void DECOMP_RB_Turtle_LInB(struct Instance* inst)
{
	int turtleID;
	struct Thread* t;
	struct Turtle* turtleObj;
	
	#ifdef REBUILD_PC
	// turtles crash the renderer?
	inst->flags |= 0x80;
	return;
	#endif
	
	inst->flags |= 0x2000;

	t = 
		DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Turtle), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Turtle_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	inst->scale[0] = 0x1000;
	inst->scale[1] = 0x1000;
	inst->scale[2] = 0x1000;
	
	// double-digit number,
	turtleID = inst->name[8];
	
	// take [8] and check for null character (0x00)
	// switch to [7] if [8] is invalid 
	if(turtleID == 0) turtleID = inst->name[7];
	
	// one turtle is just "turtle" with no number
	if(turtleID == 0) turtleID = 1;
	
	// dont subtract '0', just do & 1,
	// that'll work fine
	
	turtleObj = ((struct Turtle*)t->object);
	turtleObj->timer = 0;
	
	// put turtles on different cycles, based on turtleID
	if((turtleID & 1) == 0)
	{
		// fully up
		turtleObj->direction = 1;
		turtleObj->state = 1; // "not fully down"
		inst->animFrame = 0;
		return;
	}
	
	// fully down
	turtleObj->direction = 0;
	turtleObj->state = 0;
	inst->animFrame = DECOMP_INSTANCE_GetNumAnimFrames(inst, 0);
}
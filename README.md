# FallGuySurvival

A Survival Game created using Unreal Engine 5.  
Project Started on August 19th, 2024.

## All Bugs
- Stamina does not reduce even after reaching 0 while holding Left Shift.
- Jumping while in the air or clicking the jump button again reduces stamina.
- If Hunger reduces to 0 , then thirst will stop reducing.
- Hunger and Thirst Stats are not being saved or loaded. (Can be both)

## Current Bugs:
- If Hunger reduces to 0 , then thirst will stop reducing.
- Hunger and Thirst Stats are not being saved or loaded. (Can be both)

## Fixed Bugs
- Stamina does not reduce even after reaching 0 while holding Left Shift.
- Jumping while in the air or clicking the jump button again reduces stamina.

### Fixed Bugs Code
- Jumping while in the air or clicking the jump button again reduces stamina.
	- Original Code
 		```cpp
  		void ATFPlayerCharacter::Playerjump()
  		{
	  		if (ATFCharacter::CanJump())
	  		{
		 		 ATFCharacter::HasJumped();
	  		}
  		}
	- Fixed Code
   		```cpp
     		void ATFPlayerCharacter::Playerjump()
		{
			if (ATFCharacter::CanJump() && !GetMovementComponent()->IsFalling())
			{
				ATFCharacter::HasJumped();
			}
		}

## References
The Save game Functionality is a copy of and even a slight variation of Tom Looman's Tutorials.  
This is a link to [Tom Looman's Tutorial][1].
[1]: https://www.tomlooman.com/unreal-engine-cpp-save-system/

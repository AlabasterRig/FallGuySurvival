# Fall Guy Survival

A Survival Game created using Unreal Engine 5.  
Project Started on August 19th, 2024.

## All Bugs
- Stamina does not reduce even after reaching 0 while holding Left Shift.
- Jumping while in the air or clicking the jump button again reduces stamina.
- If Hunger reduces to 0 , then thirst will stop reducing.
- Hunger and Thirst Stats are not being saved or loaded. (Can be both)
- Only 2 Stats are getting stored currently on the code level.

## Current Bugs:
- If Hunger reduces to 0 , then thirst will stop reducing.

## Fixed Bugs
- Stamina does not reduce even after reaching 0 while holding Left Shift.
- Jumping while in the air or clicking the jump button again reduces stamina.
- Hunger and Thirst Stats are not being saved or loaded. (Can be both) - It was Both.
- Only 2 Stats are getting stored currently on the code level.

### Fixed Bugs Code
- Jumping while in the air or clicking the jump button again reduces stamina.
  
	- Fixed Code
   		```cpp
     	void ATFPlayerCharacter::Playerjump()
		{
			if (ATFCharacter::CanJump() && !GetMovementComponent()->IsFalling())
			{
				ATFCharacter::HasJumped();
			}
		}
- Hunger and Thirst Stats are not being saved or loaded. (Can be both) - It was Both.
   
	- Fixed Code
   		```cpp
     	FSaveComponentsData UStatlineComponent::GetComponentSaveData_Implementation()
		{
			FSaveComponentsData Ret;
			Ret.ComponentClass = this->GetClass();
			Ret.RawData.Add(Health.GetSaveString());
			Ret.RawData.Add(Stamina.GetSaveString());
			Ret.RawData.Add(Hunger.GetSaveString());
			Ret.RawData.Add(Thirst.GetSaveString());
			// Add Additional Data added here needs to be included in the SetComponentsSaveData_Implementation().
		
			return Ret;
		}

		void UStatlineComponent::SetComponentSaveData_Implementation(FSaveComponentsData Data)
		{
			TArray<FString> Parts;
			for (int i = 0; i < Data.RawData.Num(); i++)
			{
				Parts.Empty();
				Parts = StringChop(Data.RawData[i], '|');
				switch (i)
				{
				case 0:
					Health.UpdateFromSaveString(Parts);
					break;
				case 1:
					Stamina.UpdateFromSaveString(Parts);
					break;
				case 2:
					Hunger.UpdateFromSaveString(Parts);
					break;
				case 3:
					Thirst.UpdateFromSaveString(Parts);
					break;
				default:
					//Log Error
					break;
				}
			}
		}

- Only 2 Stats are getting stored currently on the code level.
   
	- Fixed Code
   		```cpp
     	TArray<FString> StringChop(FString Source, char split)
		{
			TArray<FString> Ret;
			FString LSide, RSide;

			while (Source.Split(&split, &LSide, &RSide))
			{
				Ret.Add(LSide);
				Source = RSide;
				LSide.Empty();
			}
			if (!RSide.IsEmpty())
			{
				Ret.Add(RSide);
			}
			
			return Ret;
		}

## References
The Save game Functionality is a copy of and even a slight variation of Tom Looman's Tutorials.  
This is a link to [Tom Looman's Tutorial][1].

[1]: https://www.tomlooman.com/unreal-engine-cpp-save-system/

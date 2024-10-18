# Bugs  
This `.md` file states the bugs encountered during debugging and playtesting. There might be more bugs deep in the code that I haven't seen yet. Will update accordingly.

## All Bugs
- Stamina does not reduce even after reaching 0 while holding Left Shift.
- Jumping while in the air or clicking the jump button again reduces stamina.
- If Hunger reduces to 0, then thirst will stop reducing.
- Hunger and Thirst Stats are not being saved or loaded. (Can be both)
- Only 2 Stats are getting stored currently on the code level.
- Interaction Raytrace is triggered from the beginning, instead of getting close to the object.
- Actor Transform not being saved correctly.
- Harvestable Tree code not working, so implemented using Blueprints, which is correctly destroying the MainTree mesh but not spawning the StumpTree mesh.
- Harvest State of Trees are not saved properly. (It was actually not being loaded properly).
- Interaction Rayrace not working on mushroom (Interaction Trace or Actor not being added to InteractionActor Array).
- Inventory not opening if no items added beforehand. It also doesn't open even after picking up an item after initially opening an empty inventory. (Fixed in previous commits).
- Cannot pickup actor again after regrowth and `OnDayChange` breakpoint not hitting.
- Time not updating correctly as the day change does not get loaded once saved.

## Current Bugs
- Cannot pickup actor again after regrowth and `OnDayChange` breakpoint not hitting.

## Fixed Bugs
- Stamina does not reduce even after reaching 0 while holding Left Shift.
- Jumping while in the air or clicking the jump button again reduces stamina.
- Hunger and Thirst Stats are not being saved or loaded. (Can be both) - It was both.
- Only 2 Stats are getting stored currently on the code level.
- Interaction Raytrace is triggered from the beginning, instead of getting close to the object.
- Actor Transform not being saved correctly.
- Harvestable Tree code not working, so implemented using Blueprints, which is correctly destroying the MainTree mesh but not spawning the StumpTree mesh.
- Harvest State of Trees are not saved properly. (It was actually not being loaded properly).
- If Hunger reduces to 0, then Thirst will stop reducing. (Fixed long ago).
- Inventory not opening if no items added beforehand. It also doesn't open even after picking up an item after initially opening an empty inventory. (Fixed in previous commits).
- Interaction Rayrace not working on mushroom (Interaction Trace or Actor not being added to InteractionActor Array).

### Fixed Bugs Code
- Jumping while in the air or clicking the jump button again reduces stamina.

  - Fixed Code:  
    ```cpp
    void ATFPlayerCharacter::Playerjump()
    {
        if (ATFCharacter::CanJump() && !GetMovementComponent()->IsFalling())
        {
            ATFCharacter::HasJumped();
        }
    }
    ```

- Hunger and Thirst Stats are not being saved or loaded. (Can be both) - It was both.

  - Fixed Code:
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
                Thirst UpdateFromSaveString(Parts);
                break;
            default:
                //Log Error
                break;
            }
        }
    }
    ```

- Only 2 Stats are getting stored currently on the code level.

  - Fixed Code:
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
    ```

- Interaction Raytrace is triggered from the beginning, instead of getting close to the object.

  - Fix Explanation:  
    There were no issues with the previously deleted code. The issue was that there was no collision mesh set for the door; hence, the `InteractableActors` array was not populating with the objects that have `InteractionInterface` implemented. I was unaware that the meshes from Quixel Bridge did not have preset collision, which is why I did not add a collision mesh using C++. (Currently removed all `UE_LOG` logging from previous commits to keep the code clean).

- Actor Transform not being saved correctly.

  - Fix Explanation:  
    Added `ISaveActorInterface` to `TFCharacter.h`. (I remember adding that when I created the `SaveActorInterface` class, idk what happened to it later).

- Harvestable Tree code not working, so implemented using Blueprints, which is correctly destroying the MainTree mesh but not spawning the StumpTree mesh.

  - Fix Explanation:  
    `MarkComponentsRenderStateDirty()` - This is meant to update new meshes at runtime.

- Harvest State of Trees are not saved properly. (It was actually not being loaded properly).

  - Fix Explanation:  
    Changed the load game logic in `TFGameInstance`. At first the code finds the actors which were marked as **spawned** and destroys them, it then loops through the save actor data and respawns them and also restores their transform and their state. (This was very difficult to fix—almost gave up thrice fixing this! Took help from StackOverflow and also the Unreal Enigne forums. Also, I noticed a bug that the `TFDoorBase` is not saving its state correctly).

- If Hunger reduces to 0, then Thirst will stop reducing. (Fixed Long ago when this code was added).

  - Fix Solution:
    ```cpp
    void UStatlineComponent::TickStats(const float& DeltaTime)
    {
        TickStamina(DeltaTime);
        TickHunger(DeltaTime);
        TickThirst(DeltaTime);
        if (Thirst.GetCurrent() <= 0.0 || Hunger.GetCurrent() <= 0.0)
        {
            return;
        }
        Health.TickStat(DeltaTime);
    }
    ```
- Inventory not opening if no items added beforehand. It also doesn't open even after picking up an item after initially opening an empty inventory.

  - Fix Explanation:  
    Made blueprint changes to the UI aspect and also to the `BP_ThirdPersonCharacter` graph to fix this issue.
    
- Interaction Rayrace not working on mushroom (Interaction Trace or Actor not being added to InteractionActor Array).

  - Fix Explanation:   
    I again forgot that items imported from quixel do not have a collision mesh. Now after adding collision its working pefectly fine as intended.

- Time not updating correctly as the day change does not get loaded once saved.

  - Fix Explanation:   
    Changed StringChop function while keeping the same logic behind. The issue was that the split char `|` was not being seperated by the code (but somehow works correctly on different uses such as `StatlineComponent`?). So now this is correctly reading and seperating the different inputs in `Source`.   
    - Solution Code:
    ```cpp
    TArray<FString> StringChop(FString Source, char split)
    {
	    TArray<FString> Ret;
	    FString Push;
	    for (int i = 0; i < (int)Source.Len(); i++)
	    {
		    if (Source[i] == split)
		    {
			    Ret.Add(Push);
			    Push.Empty();
		    }
		    else
		    {
			    Push += Source[i];
			    if (i == ((int)Source.Len() - 1))
			    {
				    Ret.Add(Push);
			    }
		    }
	    }
	    return Ret;
    }

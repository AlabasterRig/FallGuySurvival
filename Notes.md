# Ideas for future iterations
This markdown file is for future ideas to be implemented - may or may not implement but will try. Mostly by seeing a video or something.
- Add an Inventory System.
- Add harvestable trees.
- Save Actor transform and their states.
- Add a Grass painting tool (Have to learn from scratch).
- Day/Night Cycle. - (Do from blueprints maybe).
- Weather Effects (Sunny, Rainy, etc) - (Have to learn this as well lol).
- Basic Weather Effects on character (heat, cold) - (Even this I gotta learn).
- Better Logging (or maybe just adding clarity to issues in `logging.h`) - (I'll just see a video, will be better than my current).
  
.  
.  

# Explanation to how things are made to work and reason why bugs are not being fixed
Might explain the additions or changes done in the project (or might not lol), will be using mostly for issues.
- Harvest state of trees is not saved properly.  
    Some logic issue in the save and loading code, I really cannot figure out what exactly. I'll not fix it now as it is highly time-consuming and I cannot move forward to other things.  
    Update: 12/09/2024 - Fixed the load logic of the trees and its log spawning.

# FYI
I realize my mistake of committing too many times unnecessarily in a single day, and what I mean by that is I change `.md` files on GitHub instead of the editor I'm using. The reason being is that I am not confident to add stuff to `.md` files without previewing it first, hence the bloated number of commits. So, if you do see a high number of commits, please do check their content and the changes done to them.

I also realize my error in the commit messages. Since I have too much information to provide on the changes in each iteration, I keep on adding characters to the commit message. Henceforth, I'll use the description provided with each commit message to give more details about the changes made in an iteration.

I don't know for sure, but cloning this repository might not provide anyone with the necessary files to play the game. I think these are just references to the files I create and change in Unreal Engine, and most of the blueprint scripting might not be available for others to see or change.

I am not aware of any other way of providing insight into the development of this project and the constant iterations I do in it. I don't even know where else to store this project, to be honest, as it has a huge file size.

**<mark>My main focus was to show the coding aspect of the game along with its logic.</mark>**

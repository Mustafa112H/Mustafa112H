# You can use this workspace to write and submit your adventure game project.\
import time
import random


def pause_print(string):
    print(string)
    time.sleep(1)


def fight(weapon):
    pause_print(f"The {enemy} is coming closer!",)
    pause_print("Watch out! he is going to attack!")
    pause_print("You don't feel ready for this match,"
                f"you only have one weapon with you a {weapon}")
    choice = input("Are you going to (1) fight or (2) run away?\n")
    if choice == '1':
        if weapon == "magic wand":
            pause_print("you try to fight with the magic wand....")
            pause_print("you tried your best but couldn't seem to use "
                        "the wand correctly as you don't know the spells")
            pause_print(f"The {enemy} has defeated you!!")
        elif weapon == 'sword':
            pause_print(f"The {enemy} tries to sneak attack you however"
                        " you noticed his plan and revealed your shiny sword")
            pause_print("The sword held off for quiet a bit however its stre"
                        "ngth does not compare to the "
                        f"strength of the {enemy}")
            pause_print("The enemy has broke your sword into two pieces")
            pause_print(f"Tough luck! You have been defeated")
        else:
            pause_print("You don't have much faith in the "
                        "orb so you decided to use your combat skills")
            pause_print("At first it seemed ok but you were soon to realise"
                        f" your strength is nothing compared to the {enemy}'s")
            pause_print(f"Just as the {enemy} was about to "
                        "defeat you a shiny light appears.....")
            pause_print("It's the orb!!")
            pause_print(f"It protects you against the {enemy}"
                        f" and causes the {enemy} to vanish")
            pause_print("You are a Hero! You have rid the "
                        f"town from the {enemy}")
    elif choice == '2':
        pause_print("You flee back to the field faster "
                    "than you ever ran before.")
        Location_choice()
    else:
        fight(weapon)


def intro():
    pause_print("You find yourself standing in an open field, "
                "filled with grass and yellow wildflowers")
    pause_print(f"Rumor has it that a wicked {enemy} is somewhere aro"
                "und here, and has been terrifying the nearby village.")
    pause_print("You can see a crossroad in front of "
                "you that points to two locations")
    pause_print(f"In front is a castle")
    pause_print(f"on the left is a magic garden")
    pause_print(f"you carry with you a mysterious {weapon}")


def castle():
    pause_print("you cross the bridge to the castle")
    pause_print(f"you knock on the castle door")
    pause_print("OH NO!!........")
    pause_print(f"You woke the {enemy} from his 1000 year slumber")
    fight(weapon)


def garden():
    global visited
    global weapon
    pause_print("you run towards the garden")
    if visited:
        pause_print("You discovered this location previously")
    else:
        pause_print("you see many different flowers of beautiful colors")
        pause_print("Something over there is sparkling inside that flower")
        pause_print("you pick it up....")
        pause_print("it's a magic orb!!!")
        pause_print(f"you leave your silly {weapon} and take the orb")
        weapon = "orb"
    visited = True
    pause_print("You leave the garden")
    Location_choice()


def Location_choice():
    pause_print(f"Enter 1 to go to the castle")
    pause_print(f"Enter 2 to go to the magic garden")
    pause_print("What would you like to do?")
    pause_print("Please enter 1 or 2")
    choice = ''
    while choice != '1' and choice != '2':
        choice = input()
        if choice == '1':
            castle()
        elif choice == '2':
            garden()
        else:
            pause_print("Please enter 1 or 2")


def play_again():
    choice = ''
    while choice not in ['y', 'n']:
        choice = input("Would you like to play again? (y/n)\n")
        if choice == 'n':
            pause_print("Thanks for playing! Goodbye!.")
            return False
        elif choice == 'y':
            pause_print("Get ready for your next adventure! ...")
            weapon = 'orb'
            return True


while True:
    weapons = ["magic wand", "sword"]
    weapon = random.choice(weapons)
    enemies = ["dragon", "troll", "giant", "witch", "elf"]
    enemy = random.choice(enemies)
    visited = False
    intro()
    Location_choice()
    if not play_again():
        break

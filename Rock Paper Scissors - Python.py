#!/usr/bin/env python3

"""This program plays a game of Rock, Paper, Scissors between two Players,
and reports both Player's scores each round."""

import random
moves = ['rock', 'paper', 'scissors']

"""The Player class is the parent class for all of the Players
in this game"""


class Player:
    def move(self):
        return 'rock'

    def learn(self, my_move, their_move):
        pass


class AllRockPlayer(Player):
    pass


class ReflectPlayer(Player):
    def learn(self, my_move, their_move):
        self.last_move = their_move

    def move(self):
        try:
            return self.last_move
        except AttributeError:
            return random.choice(moves)


class CyclePlayer(Player):

    def learn(self, my_move, their_move):
        pos = moves.index(my_move)
        self.new_move = moves[(pos + 1) % 3]

    def move(self):
        try:
            return self.new_move
        except AttributeError:
            return random.choice(moves)


class HumanPlayer(Player):
    def move(self):
        while True:
            my_move = input("Rock, paper or Scissors?\n")
            my_move = my_move.lower()
            if my_move in moves:
                return my_move
            else:
                print("Invalid, choose Rock, paper or Scissors")


class RandomPlayer(Player):
    def move(self):
        return random.choice(moves)


def beats(one, two):
    return ((one == 'rock' and two == 'scissors') or
            (one == 'scissors' and two == 'paper') or
            (one == 'paper' and two == 'rock'))


def winner(Player1, Player2):
    print("\nTHE FINAL SCORE\n"
          f"{Player1}:{Player2}")
    if Player1 > Player2:
        print("Player One has won the Game!")
    elif Player1 < Player2:
        print("Player Two has won the Game!")
    else:
        print("Tie! No one Wins!")


class Game:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2
        self.p1.count = 0
        self.p2.count = 0

    def play_round(self):
        move1 = self.p1.move()
        move2 = self.p2.move()
        print(f"Player 1: {move1}  Player 2: {move2}")
        self.p1.learn(move1, move2)
        self.p2.learn(move2, move1)
        if move1 == move2:
            print("Tie! No one wins!")
            print(f"The Score: Player1 {self.p1.count},"
                  f" Player2 {self.p2.count}")
        elif beats(move1, move2):
            print("Player one wins the round!!")
            self.p1.count += 1
            print(f"The Score: Player1 {self.p1.count},"
                  f" Player2 {self.p2.count}")

        else:
            print("Player two Wins the round!!")
            self.p2.count += 1
            print(f"The Score: Player1 {self.p1.count},"
                  f" Player2 {self.p2.count}")

    def play_game(self):
        print("Game start!")
        for round in range(3):
            print(f"Round {round}:")
            self.play_round()
        winner(self.p1.count, self.p2.count)
        print("Game over!")


def Start_Game(Player1, Player2):
    game = Game(Player1, Player2)
    game.play_game()


def GameStarter():
    print("**WELCOME TO ROCK, PAPER, AND SCISSORS**")
    while True:
        mode = input("Choose game mode: Starter,"
                     "Easy, Medium, Hard or Exit\n").lower()
        if mode == "starter":
            game = Start_Game(HumanPlayer(), AllRockPlayer())
        elif mode == "easy":
            game = Start_Game(HumanPlayer(), CyclePlayer())
        elif mode == "medium":
            game = Start_Game(HumanPlayer(), ReflectPlayer())
        elif mode == "hard":
            game = Start_Game(HumanPlayer(), RandomPlayer())
        elif mode == "exit":
            print("GoodBye!")
            break
        else:
            print("Enter a valid Option!")


if __name__ == '__main__':
    GameStarter()

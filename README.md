# MindThrashing
Iterative and Recursive solution to score maximum points in a limited time in the MindThrashing game

# PROBLEM BACKGROUND

Let assume you are a massive fan of the game “MIND - THRASHING,” an online tricky,
challenging, and mind-blowing puzzle game. You love to have a healthy competition with
your friends. Obviously, you always want to score higher than all your friends. But given
that you are a FAST student, you do not have much time to put in. To score maximum
points in a limited time, you need to use your computer science skills and plan.
The game “MIND Thrashing” launch a set of different stages each week. Each stage is
independent; that is, there is no restriction on which stage should be completed first. Each
stage has some points and an estimated time required to solve it.
Now you want to play the stages that give you maximum points in the limited time that
you can spare in a week. Your task is to write an algorithm that takes in the following
information and output the name of the stages that you should play, given your time
restrictions.

The input to your algorithm will be
1. No of stages
2. For each stage input; the name of the stage, points, and time required to complete
it (in minutes)
3. Time you can put in to play the game (in minutes)
4. 
The output will be: Name of the stages you should play

## Part a) Write an iterative algorithm using a stack to solve the above problem. Use
your own stack class.
## Part b) Write a recursive function to solve the above problem

## Example
Assume that the Week 1 game has three stages

Stage 1: Drowning, points 50, time needed 10 min
Stage 2: Killer, points 80, time needed 20 min
Stage 3: Remarkable, points 100, time needed 30 min
Time you can spare 50 mins
Various solutions exist
Play stage 1 only, Point = 50
Play stage 2 only, Point = 80
Play stage 3 only, Point = 100
Play stage 1 and 2 only, Point = 50+80= 130
Play stage 1 and 3 only, Point = 50 +100 = 150
Play stage 2 and 3 only, Point = 80 +100 = 180
Play stage 1, 2 and 3, Not possible as time required is greater than what you can spare

BEST CHOICE: Play Stage 2 and 3

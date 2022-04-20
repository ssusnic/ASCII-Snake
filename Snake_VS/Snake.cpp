/**############################################################################
#
# @Program		SNAKE
# @File			Snake.cpp
# @Description	A terminal based game made in C++ for the Windows Console.
#				Move the snake with the cursor keys and eat as much food 
#				as possible before you die of insatiable greed.
#
# @Author		Srdjan Susnic
# @Website		https://www.askforgametask.com
# @Github		https://www.github.com/ssusnic
# @Youtube		https://www.youtube.com/ssusnic
#
# Copyright (C) 2022 Ask For Game Task
#
#############################################################################*/

// include the framework
#include "Terminator.h"

#include <vector>

/******************************************************************************
*
* Definition of the Game Class.
*
******************************************************************************/

class Game
{
private:
	// game states
	enum {
		GAME_SPLASH,
		GAME_INIT,
		GAME_PLAY,
		GAME_OVER
	};
	
	// current game state
	int state = GAME_SPLASH;
	
	// point structure
	struct Point {
		int x;
		int y;
	};
	
	// snake is consisted of a series of segments
	vector<Point> snake;
	
	// snake direction
	Point direction = {1, 0};
	
	// food position
	Point food;
	
	// bonus position
	Point bonus;
	
	// period of time during which the bonus is displayed
	int bonusTime;
	
	// current score and high score
	int score;
	int hiscore = 0;
	
public:
	//=========================================================================
	// Runs the main game loop.
	//=========================================================================
	void Run()
	{		
		while (!quit){
			StartTimer();
			ClearScreen(BG_BLACK);
			
			switch (state){
				case GAME_SPLASH:
					ShowSplash();
					break;
					
				case GAME_INIT:
					Restart();
					Render();
					break;
					
				case GAME_PLAY:
					Logic();
					Render();
					break;
					
				case GAME_OVER:
					Render();
					ShowGameOver();
					break;
			}
			
			if (GetAsyncKeyState(VK_ESCAPE)) quit = true;
			
			RedrawScreen();
			WaitTimer();
		}
	}
	
private:
	//=========================================================================
	// Shows the splash screen with instructions.
	//=========================================================================
	void ShowSplash()
	{
		int cx = screenCols/2;
		
		DrawTextC(" SNAKE ", cx, 1, WHITE, BG_BLUE);
		
		DrawText("You are a very voracious snake with a life goal of", 5, 4, WHITE);
		DrawText("eating as much food as possible before you die of", 5, 5, WHITE);
		DrawText("insatiable greed.", 5, 6, WHITE);
		
		DrawText("To control your direction, use the cursor keys.", 5, 8, YELLOW);
		
		DrawText("The snake earns points with each item eaten, but it", 5, 10, WHITE);
		DrawText("also gets longer as a result of enormous gluttony.", 5, 11, WHITE);
		
		DrawText("Here is today's menu:", 5, 13, WHITE);
		DrawText("%", 8, 15, RED);
		DrawText("- red evil mouse  :  10 points + 3 segments", 10, 15, WHITE);
		DrawText("$", 8, 16, GREEN);
		DrawText("- extra bonus coin: 100 points + 1 segment", 10, 16, WHITE);
		
		DrawText("The game is over when the snake runs into yourself", 5, 18, WHITE);
		DrawText("or hits the border walls.", 5, 19, WHITE);
		
		DrawTextC(" --- PRESS SPACE TO START THE GAME --- ", cx, 22, YELLOW);
		
		DrawTextC("www.askforgametask.com | www.youtube.com/ssusnic", cx, 26, CYAN);
		DrawTextC("Copyright (C) 2022 Ask For Game Task", cx, 28, CYAN);

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) state = GAME_INIT;
	}
	
	//=========================================================================
	// Restarts the game.
	//=========================================================================
	void Restart()
	{
		// initialize random seed
		srand((unsigned) time(NULL));
		
		// create a new snake with 5 segments in the screen center
		snake.clear();
		for (int i=0; i<5; i++){
			snake.push_back( {30, 15} );
		}
		
		// place the food on a random location
		food = GetRandomPos();
		
		// hide the bonus item
		bonus = {-10, -10};
		bonusTime = 0;
		
		// reset score
		score = 0;
		
		// play sound of snake
		PlayAudio(L"snd_snake.wav", 0.35f, false);
		
		// switch to the game play state
		state = GAME_PLAY;
	}
	
	//=========================================================================
	// Returns a random position in the snake arena.
	//=========================================================================
	Point GetRandomPos(){
		return {1 + rand()%58, 1 + rand()%28};
	}
	
	//=========================================================================
	// Performs the game logic!
	//=========================================================================
	void Logic()
	{
		// get the old direction so we know if it is changed
		Point olddir = direction;
		
		// use cursors keys to control the snake direction
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) direction = {-1, 0};
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) direction = {1, 0};
		if (GetAsyncKeyState(VK_UP) & 0x8000) direction = {0, -1};
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) direction = {0, 1};
		
		// play the sound of snake if its direction is change
		if (olddir.x!=direction.x || olddir.y!=direction.y){
			PlayAudio(L"snd_snake.wav", 0.35f, false);
		}
		
		// get the snake's head and tail
		Point head = snake.front();
		Point tail = snake.back();
		
		// move the head to a new position
		head.x += direction.x;
		head.y += direction.y;
		
		// insert the new head at the beginning of the snake body
		snake.insert(snake.begin(), head);
		
		// remove the last segment from the snake body
		snake.pop_back();
		
		// check if the snake eats food
		if (head.x == food.x && head.y == food.y){ 
			// increase the snake by reproducing its tail (3x)
			for (int i=0; i<3; i++) snake.push_back(tail);
			
			// replace food
			food = GetRandomPos();
			
			// update score
			score += 10;
			hiscore = max(score, hiscore);
			
			// activate bonus on a random position after every 30 points earned
			if (score%30 == 0){
				bonus = GetRandomPos();
				bonusTime = 50 + rand()%50;
			}
			
			PlayAudio(L"snd_eat.wav", 0.77f, true);
		
		// check if the snake finds a bonus item
		} else if (head.x == bonus.x && head.y == bonus.y){
			// increase the snake by reproducing its tail (1x)
			snake.push_back(tail);
			
			// update score
			score += 100;
			hiscore = max(score, hiscore);
			
			// deactivate bonus
			bonusTime = 0;
			
			PlayAudio(L"snd_bonus.wav", 0.44f, true);
		
		// check if the snake hits the walls
		} else if (head.x==0 || head.x==59 || head.y==0 || head.y==29){
			PlayAudio(L"snd_hit.wav", 0.4f, true);
			state = GAME_OVER;
		
		// check if the snake hits itself
		} else {
			for (int i=1; i<snake.size(); i++){
				if (head.x == snake.at(i).x && head.y == snake.at(i).y){
					PlayAudio(L"snd_hit.wav", 0.4f, true);
					state = GAME_OVER;
				}
			}
		}
		
		// keep the bonus activated until its time expires
		if (bonusTime > 0) bonusTime--;
		else bonus = {-10, -10};
	}
	
	//=========================================================================
	// Renders the game scene.
	//=========================================================================
	void Render()
	{		
		// draw arena
		for (int i=0; i<60; i++){
			DrawChar(' ', i, 0, GREY, BG_GREY);
			DrawChar(' ', i, 29, GREY, BG_GREY);
		}
		
		for (int j=0; j<30; j++){
			DrawChar(' ', 0, j, GREY, BG_GREY);
			DrawChar(' ', 59, j, GREY, BG_GREY);
		}
		
		// draw bonus
		DrawChar('$', bonus.x, bonus.y, GREEN);
		
		// draw food
		DrawChar('%', food.x, food.y, RED);
		
		// draw snake body
		for (auto &segment : snake){
			DrawChar(state==GAME_OVER ? 'x':'O', segment.x, segment.y, YELLOW);
		}
		
		// draw snake head
		DrawChar('@', snake.front().x, snake.front().y, DARK_YELLOW);
		
		// draw score
		DrawText("SCORE: "+to_string(score), 1, 0, BLACK, BG_GREY);
		DrawTextR("HI: "+to_string(hiscore), 59, 0, BLACK, BG_GREY);
	}
	
	//=========================================================================
	// Shows the game over dialog.
	//=========================================================================
	void ShowGameOver()
	{
		DrawRect(18, 12, 25, 6, BG_BLUE);
		DrawTextC("GAME OVER", 30, 13, WHITE);
		DrawTextC("Spacebar - Restart", 30, 15, YELLOW);
		DrawTextC("Backspace - Main Menu", 30, 16, YELLOW);
		
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) state = GAME_INIT;
		if (GetAsyncKeyState(VK_BACK) & 0x8000) state = GAME_SPLASH;
	}
};

/******************************************************************************
*
* Main program 
*
******************************************************************************/

int main()
{
	CreateConsole(
		L"SNAKE",       // game title
		60,             // screen columns
		30,             // screen rows
		L"Consolas",    // font name
		20,             // font width    (increases/decreases window width)
		26,             // font height   (increases/decreases window height)
		20              // fps           (slows down/speeds up the game)
	);
	
	Game game;
	game.Run();

	DestroyConsole();
	
	return 0;
}

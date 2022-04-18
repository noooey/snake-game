#include <clocale>
#include <ncurses.h>
#include <iostream>
#include <ctime>
#include "snake.h"
#include "kbhit.h"
using namespace std;

const double HALF_SECOND = 0.5;

SNAKE snake;   // SNAKE 객체 생성

// 옵션 초기화
void OptionInit(){
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_YELLOW);   // 팔레트1
  init_pair(2, COLOR_WHITE, COLOR_GREEN);    // 팔레트2
}

// 터미널 초기화
void TermInit(){
  resize_term(24, 50);
  border('|', '|', '-', '-', '+', '+', '+', '+');   // 테두리
  mvprintw(1, 1, "SnakeGame!");
  refresh();   // 화면 출력
  noecho();   // 입력한 문자 가리기
  getch();   // 문자 입력시 다음 이동
}

// 윈도우 초기화
void WinInit(){
  snake.win = newwin(21, 21, 2, 1);   // 맵 생성
  wbkgd(snake.win, '0');   // 맵 배경

  keypad(snake.win, TRUE);   // 특수 키 입력 가능
  curs_set(0);   // 커서 가림

  wattron(snake.win, COLOR_PAIR(2));
  wborder(snake.win, '1', '1', '1', '1', '2', '2', '2', '2');
  wattroff(snake.win, COLOR_PAIR(2));

  // sanke 초기화
  snake.y = 10;   // 처음 위치 초기화
  snake.x = 10;
  snake.length = 3;   // 길이 초기화
  snake.head = KEY_RIGHT;   // 방향 초기화
  wattron(snake.win, COLOR_PAIR(1));
  mvwprintw(snake.win, snake.y, snake.x, "3");
  wattroff(snake.win, COLOR_PAIR(1));

  wrefresh(snake.win);
}

// 방향키 받는 함수
int Head(){
  if(kbhit() == true)
    return getch();
}

// 회전
void Turn(int input){
    // 초기화 및 배경 유지
    wclear(snake.win);
    wbkgd(snake.win, '0');
    wattron(snake.win, COLOR_PAIR(2));
    wborder(snake.win, '1', '1', '1', '1', '2', '2', '2', '2');
    wattroff(snake.win, COLOR_PAIR(2));
    // 회전
    wattron(snake.win, COLOR_PAIR(1));
    if(snake.head == KEY_LEFT){   // head방향: 좌
      switch(input){
          case KEY_UP:
          mvwprintw(snake.win, --snake.y, ++snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
          case KEY_DOWN:
          mvwprintw(snake.win, ++snake.y, ++snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
          case KEY_LEFT:
          break;
          case KEY_RIGHT:
          break;  // fail
      }
    }
    else if(snake.head == KEY_RIGHT){
      switch(input){
          case KEY_UP:
          mvwprintw(snake.win, --snake.y, --snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
          case KEY_DOWN:
          mvwprintw(snake.win, ++snake.y, --snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
          case KEY_LEFT:
          break;   // fail
          case KEY_RIGHT:
          break;
      }
    }
    else if(snake.head == KEY_UP){
      switch(input){
          case KEY_UP:
          break;
          case KEY_DOWN:
          break;  // fail
          case KEY_LEFT:
          mvwprintw(snake.win, ++snake.y, --snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
          case KEY_RIGHT:
          mvwprintw(snake.win, ++snake.y, ++snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
      }
    }
    else if(snake.head == KEY_DOWN){
      switch(input){
          case KEY_UP:
          break;   //fail
          case KEY_DOWN:
          break;
          case KEY_LEFT:
          mvwprintw(snake.win, --snake.y, --snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
          case KEY_RIGHT:
          mvwprintw(snake.win, --snake.y, ++snake.x, "3");
          snake.head = input;  // head방향(=pre) 갱신
          break;
      }
    }
    wattroff(snake.win, COLOR_PAIR(1));
}

// 상태 업데이트
void StateUpdate(clock_t curr){
   if(((curr - snake.standTime)/1000000) >= HALF_SECOND){
     snake.standTime = curr;
     // 초기화 및 배경 유지
     wclear(snake.win);
     wbkgd(snake.win, '0');
     wattron(snake.win, COLOR_PAIR(2));
     wborder(snake.win, '1', '1', '1', '1', '2', '2', '2', '2');
     wattroff(snake.win, COLOR_PAIR(2));
     wattron(snake.win, COLOR_PAIR(1));
     if(snake.head == KEY_LEFT) mvwprintw(snake.win, snake.y, --snake.x, "3");
     else if(snake.head == KEY_RIGHT) mvwprintw(snake.win, snake.y, ++snake.x, "3");
     else if(snake.head == KEY_UP) mvwprintw(snake.win, --snake.y, snake.x, "3");
     else if(snake.head == KEY_DOWN) mvwprintw(snake.win, ++snake.y, --snake.x, "3");
     wattroff(snake.win, COLOR_PAIR(1));
   }
}

int main(){
  OptionInit();
  TermInit();
  WinInit();

  while(1){
    int input = Head();
    if(input != 0) Turn(input);   // input값 실행시
    clock_t currTime = clock();
    StateUpdate(currTime);
    wrefresh(snake.win);
  }
  getch();
  delwin(snake.win);
  endwin();

  return 0;

}

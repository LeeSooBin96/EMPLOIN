#include <iostream>
#include <unistd.h>
#include <termios.h>

#include "GetCh.h"

int getch()
{
    int in_char;
    struct termios back_up;
    struct termios change;
    
    tcgetattr(0,&back_up); //기존 설정 저장
    change = back_up;
    //설정 변경
    change.c_lflag &= ~(ICANON|ECHO);
    change.c_cc[VMIN]=1;
    change.c_cc[VTIME]=0;

    tcsetattr(0,TCSAFLUSH,&change); //변경된 설정 적용
    in_char=getchar();
    tcsetattr(0,TCSAFLUSH,&back_up); //원래 설정으로 복구
    return in_char;
}
#include <iostream>

#include "LoginPage.h"
#include "InitPage.h"

int main(void)
{
    bool quit=false;
    //로그인 페이지
    LoginPage login;
    while(!(quit=login.ProcessLogin())) //종료 선택할 때까지
    {
        //로그인 완료되면 아래 진행
        //초기 화면
        InitPage init;
        init.ProcessInit();
    }
    //종료 선택되면 return
    return 0;
}
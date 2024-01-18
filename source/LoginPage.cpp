#include <iostream>
#include <sqlite3.h>

#include "Database.h"
#include "LoginPage.h"
#include "GetCh.h"

using std::cout;

//로그인 화면
void LoginPage::LoginScreen(void)
{
    using std::cin;
    system("clear");
    cout<<"\x1b[1;96m┌───────────────────────┐ \n"
          "│    |L||o||g||i||n|    │\n"
          "└───────────────────────┘ \x1b[m\n";
    cout<<"아이디 > ";
    cin>>id;
    cout<<"PIN번호 > ";
    cin>>pin;
    cout<<id <<" "<<pin<<std::endl;
    //로그인 정보 확인해야함
    cin.get();
    cin.get();
}
//회원가입 화면
void LoginPage::JoinScreen(void)
{
    using std::cin;
    std::string sqlTMP;
    system("clear");
    cout<<"\x1b[1;96m┌────────────────────────┐ \n"
          "│      |J||o||i||n|      │\n"
          "└────────────────────────┘ \x1b[m\n";
    cout<<"아이디 > ";
    cin>>id;
    cout<<"PIN번호 > ";
    cin>>pin;
    cout<<"이메일 > ";
    cin>>email;
    cout<<"휴대폰번호 > ";
    cin>>phone;
    cout<<id<<" "<<pin<<" "<<email<<" "<<phone<<std::endl;
    //DB INSERT 구문 만들기 -- 테이블 구성 먼저하기
    sqlTMP = "INSERT INTO User(Uid,Upin,Ueml,Uph) VALUES('"+id+"',"+pin+",'"+email+"','"+phone+"')";
    //회원 테이블에 저장해야함
    SQLite db;
    db.DataBaseOpen("DB_Hin.db");
    db.DataBaseQuery(sqlTMP.c_str());
    db.DataBaseClose();
    cin.get();
    cin.get();
}
//커서 위치에 따른 페이지 목록
void LoginPage::ListforPos(unsigned short pos)
{
    cout<<"\x1b[1;96m ##   ##  ##  ####    ##   ## \n"
          " ##   ##  ##   ##     ###  ## \n"
          " ##   ##  ##   ##     #### ## \n"
          " #######       ##     ## #### \n"
          " ##   ##  ##   ##     ##  ### \n"
          " ##   ##  ##   ##     ##   ## \n"
          " ##   ##  ##  ####    ##   ## \x1b[m\n";

    switch(pos)
    {
        case 0:
            cout<<"●  로그인 \n"
                  "\x1b[30m○  회원가입 \n"
                  "○  종료 \x1b[m\n";
            break;
        case 1:
            cout<<"\x1b[30m○  로그인 \x1b[m\n"
                  "●  회원가입 \n"
                  "\x1b[30m○  종료 \x1b[m\n";
            break;
        case 2:
            cout<<"\x1b[30m○  로그인 \n"
                  "○  회원가입 \x1b[m\n"
                  "●  종료 \n";
            break;
        default:
            break;
    }
    cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
}
//로그인 페이지 메인 프로세스
bool LoginPage::ProcessLogin(void)
{
    //구성 : (아스키 아트/)로그인/ 회원가입/ 종료
    unsigned short pos=0;
    bool quit=false;
    int input;
    
    //회원 테이블 없을 시 테이블 생성
    SQLite db;
    db.DataBaseOpen("DB_Hin.db");
    db.DataBaseQuery("CREATE TABLE IF NOT EXISTS User(Unum INTEGER PRIMARY KEY,Uid TEXT,Upin INTEGER,Ueml TEXT,Uph TEXT);");
    db.DataBaseClose();

    system("clear");
    ListforPos(pos);
    while(!quit)
    {
        input=getch();
        switch(input)
        {
            case 65: //방향키 상
                if(pos!=0) pos--;
                system("clear");
                ListforPos(pos);
                break;
            case 66: //방향키 하
                if(pos!=2) pos++;
                system("clear");
                ListforPos(pos);
                break;
            case 10: //엔터
                quit = true;
                break;
            default:
                break;
        }
    }
    switch (pos)
    {
    case 0: //로그인
        cout<<"로그인을 진행합니다. \n";
        LoginScreen();
        return false;
    case 1: //회원가입
        cout<<"회원가입을 진행합니다. \n";
        JoinScreen();
        return ProcessLogin();
    case 2: //종료
        cout<<"종료됩니다. \n";
        return true;
    default:
        break;
    }
    return true;
}   
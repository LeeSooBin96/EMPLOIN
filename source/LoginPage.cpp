#include <iostream>
#include <sqlite3.h>

#include "CEOMode.h"
#include "Database.h"
#include "LoginPage.h"
#include "GetCh.h"

using std::cout;

SQLite db;
std::string sqlTMP;

//로그인 화면
bool LoginPage::LoginScreen(void)
{
    using std::cin;
    system("clear");
    cout<<"\x1b[1;96m┌───────────────────────┐ \n"
          "│    |L||o||g||i||n|    │\n"
          "└───────────────────────┘ \x1b[m\n"
          "[ 이전화면으로 돌아가려면 x를 입력하세요 ]\n";
    while(true)
    {
        cout<<"아이디 > ";
        cin>>id;
        if(!id.compare("x")||!id.compare("X"))
        {
            cin.get();
            return false;
        }
        //기업 로그인 추가
        if(!id.compare("_company")||!id.compare("_COMPANY"))
        {
            CEOMode ceo;
            ceo.ProgressCEOMode();
            return false;
        }
        cout<<"PIN번호 > ";
        cin>>pin;
        if(!pin.compare("x")||!pin.compare("X"))
        {
            cin.get();
            return false;
        }
        //로그인 정보 확인해야함
        db.DataBaseOpen("DB_Hin.db");
        sqlTMP="SELECT UID FROM USER_TB;";
        if(!db.ProcessCMP(sqlTMP.c_str(),id)) //일치하는 아이디가 있을때
        {
            // db.DataBaseClose();
            // db.DataBaseOpen("DB_Hin.db");
            sqlTMP="SELECT UPIN FROM USER_TB WHERE UID='"+id+"';";
            if(!db.ProcessCMP(sqlTMP.c_str(),pin))
            {
                cout<<"로그인에 성공하셨습니다! \n";
                // db.DataBaseClose();
                break;
            }
            else
            {
                cout<<"존재하지 않는 아이디 혹은 PIN번호 입니다.\n";
            }
        }
        else
        {
            cout<<"존재하지 않는 아이디 혹은 PIN번호 입니다.\n";
        }
    }
    db.DataBaseClose();
    cout<<"엔터를 눌러 계속)\n";
    cin.get();
    cin.get();
    return true;
}
//회원가입 화면
void LoginPage::JoinScreen(void)
{
    using std::cin;
    bool dup=false; //중복검사값

    system("clear");
    cout<<"\x1b[1;96m┌────────────────────────────────────────────┐ \n"
          "│          |J|    |o|    |i|    |n|          │\n"
          "└────────────────────────────────────────────┘ \x1b[m\n"
          "  [ 이전화면으로 돌아가려면 x를 입력하세요 ]\n";

    while(!dup)
    {
        cout<<"아이디 > ";
        cin>>id;
        if(!id.compare("x")||!id.compare("X"))
        {
            cin.get();
            return;
        } 
        //아이디 중복 검사
        db.DataBaseOpen("DB_Hin.db");
        dup=db.ProcessCMP("SELECT UID FROM USER_TB;",id); //일치하는게 없으면 true반환
        if(!dup) //검사값이 false(중복이 있으면)
        {
            cout<<"-- 중복된 아이디입니다. 다시 입력해주세요. --\n";
        }
        // db.DataBaseQuery("SELECT Uid FROM User;",db.CallbackCMP); --콜백 버려...
        // db.ProcessCMP(id);
        db.DataBaseClose();
    }dup=false;
    cout<<"PIN번호 > ____\b\b\b\b";
    cin>>pin;
    if(!pin.compare("x")||!pin.compare("X"))
    {
        cin.get();
        return;
    }
    //4자리 숫자 적합성 검사
    if(pin.size()==4)
    {
        for(int i=0;i<4;i++)
        {
            if(!isdigit(pin[i]))
            {
                dup=false; break;
            }
            else dup=true;
        }
    }
    while(!dup)
    {
        cout<<"-- PIN번호는 숫자 4자리로 입력하셔야 합니다. --\n";
        cout<<"PIN번호 > ____\b\b\b\b";
        cin>>pin;
        if(!pin.compare("x")||!pin.compare("X"))
        {
            cin.get();
            return;
        }
        //4자리 숫자 적합성 검사
        if(pin.size()==4)
        {
            for(int i=0;i<4;i++)
            {
                if(!isdigit(pin[i]))
                {
                    dup=false; break;
                }
                else dup=true;
            }
        }
    }dup=false;
    //이메일 입력 및 중복 검사
    while(!dup)
    {
        cout<<"이메일 > ";
        cin>>email;
        if(!email.compare("x")||!email.compare("X"))
        {
            cin.get();
            return;
        }
        //중복 검사
        db.DataBaseOpen("DB_Hin.db");
        dup=db.ProcessCMP("SELECT UEML FROM USER_TB;",email); //일치하는게 없으면 true반환
        if(!dup) //검사값이 false(중복이 있으면)
        {
            cout<<"-- 중복된 이메일입니다. 다시 입력해주세요. --\n";
        }
        db.DataBaseClose();
    }dup=false;
    //휴대폰 번호 입력 및 중복 검사
    while(!dup)
    {
        cout<<"휴대폰 번호(-제외) > ";
        cin>>phone;
        if(!phone.compare("x")||!phone.compare("X"))
        {
            cin.get();
            return;
        }
        //-제외 해야함
        for(int i=0;i<phone.size();i++)
        {
            if(!isdigit(phone[i]))
            {
                cout<<"-- 올바르지 않은 입력입니다. 다시 입력해주세요. --\n";
                cout<<"휴대폰 번호(-제외) > ";
                cin>>phone;
                continue;
            }
        }
        //중복 검사
        db.DataBaseOpen("DB_Hin.db");
        dup=db.ProcessCMP("SELECT UPH FROM USER_TB;",phone); //일치하는게 없으면 true반환
        if(!dup) //검사값이 false(중복이 있으면)
        {
            cout<<"-- 중복된 휴대폰 번호입니다. 다시 입력해주세요. --\n";
        }
        db.DataBaseClose();
    }dup=false;
    // cout<<id<<" "<<pin<<" "<<email<<" "<<phone<<std::endl; //추적용
    //DB INSERT 구문 만들기 -- 테이블 구성 먼저하기
    sqlTMP = "INSERT INTO USER_TB(UID,UPIN,UEML,UPH) VALUES('"+id+"',"+pin+",'"+email+"','"+phone+"')";
    //회원 테이블에 저장해야함
    db.DataBaseOpen("DB_Hin.db");
    db.DataBaseQuery(sqlTMP.c_str());
    db.DataBaseClose();
    //등록된 회원정보 출력해야 함
    sqlTMP="SELECT * FROM USER_TB WHERE UID='"+id+"';";
    sqlite3* user;
    sqlite3_stmt* res;
    if(sqlite3_open("DB_Hin.db",&user)!=SQLITE_OK||sqlite3_prepare_v2(user,sqlTMP.c_str(),-1,&res,0)!=SQLITE_OK)
    {
        std::cout<<"Cannot open database: "<<sqlite3_errmsg(user)<<std::endl;
        sqlite3_close(user);
        exit(1);
    }
    else if(sqlite3_step(res)==SQLITE_ROW)
    {
        cout<<"\n< 등록된 회원정보는 다음과 같습니다 > \n"
              "회원번호 : "<<sqlite3_column_text(res,0)<<std::endl;
        cout<<"아이디 : "<<sqlite3_column_text(res,1)<<std::endl;
        cout<<"비밀번호 : "<<sqlite3_column_text(res,2)<<std::endl;
        cout<<"이메일 : "<<sqlite3_column_text(res,3)<<std::endl;
        cout<<"전화번호 : "<<sqlite3_column_text(res,4)<<std::endl;
        sqlite3_finalize(res);
        sqlite3_close(user);
    }
    cout<<"엔터를 눌러 계속)";
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
    db.DataBaseOpen("DB_Hin.db");
    db.DataBaseQuery("CREATE TABLE IF NOT EXISTS USER_TB(UNUM_PK INTEGER PRIMARY KEY,UID TEXT NOT NULL,UPIN INTEGER NOT NULL,UEML TEXT NOT NULL,UPH TEXT NOT NULL);");
    db.DataBaseClose();

    system("clear");
    ListforPos(pos);
    while(!quit)
    {
        input=getch();
        switch(input)
        {
            case 65: //방향키 상
                if(pos!=0)
                {
                    pos--;
                    system("clear");
                    ListforPos(pos);
                }
                break;
            case 66: //방향키 하
                if(pos!=2) 
                {
                    pos++;
                    system("clear");
                    ListforPos(pos);
                }
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
        if(LoginScreen()) return false;
        else return ProcessLogin();
        // return false;
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
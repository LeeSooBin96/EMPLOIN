#include <cstdlib>
#include <iostream>

#include "Database.h"
#include "DetailPage.h"
#include "GetCh.h"
#include "InitPage.h"
#include "SearchPage.h"

using std::cout;

sqlite3* db;

//공고 목록 출력 함수 - 커서 위치 입력받아서 색 변경 적용
void InitPage::ShowNotice(unsigned short pos)
{
    if(pos!=1) cout<<"\x1b[30m○  공고 목록 \n";
    else cout<<"●  공고 목록 \n";
}
//커서 위치에 따른 목록 출력
void InitPage::ListforPos(unsigned short pos)
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
            cout<<"●  로그아웃 \n";
            ShowNotice(0);
            cout<<"○  검색 > \x1b[m\n";
            break;
        case 1:
            cout<<"\x1b[30m○  로그아웃 \x1b[m\n";
            ShowNotice(1);
            cout<<"\x1b[30m○  검색 > \x1b[m\n";
            break;
        case 2:
            cout<<"\x1b[30m○  로그아웃 \n";
            ShowNotice(2);
            cout<<"\x1b[m●  검색 > \n";
            break;
        default:
            break;
    }
    cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
}
//초기 페이지 메인 프로세스
void InitPage::ProcessInit(void)
{
    srand(time(NULL));
    while(true)
    {    
        //일단 다른거 생각안하고 공고 랜덤으로 3~5개 출력되도록
        unsigned short lnumMax = rand()%3+3; //목록 개수
        //구성: 공고 목록/ 검색 입력/ 로그아웃
        unsigned short pos=0;
        bool quit=false;
        int input;

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
                    if(pos!=2+lnumMax) pos++;
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
        if(pos==0) //로그아웃
        {
            cout<<"로그아웃을 진행합니다. \n";
            return;
        }
        else if(pos>0&&pos<lnumMax+1) //공고 상세 정보
        {
            DetailPage detail;
            detail.ProcessDetail();
        }
        else if(pos==lnumMax+1) //검색
        {
            SearchPage search;
            search.ProcessSearch();
        }
        // switch (pos)
        // {
        // case 0: //로그아웃
        //     cout<<"로그아웃을 진행합니다. \n";
        //     return;
        // case 1: //공고 상세 정보
        // {
        //     cout<<"공고의 상세 정보를 조회합니다. \n";
        //     //공고 상세 정보 페이지
        //     DetailPage detail;
        //     detail.ProcessDetail();
        //     break;
        // }
        // case 2: //검색
        // {
        //     cout<<"검색 결과를 출력합니다. \n";
        //     //검색 페이지
        //     SearchPage search;
        //     search.ProcessSearch();
        //     break;
        // }
        // default:
        //     break;
        // }
    }
}
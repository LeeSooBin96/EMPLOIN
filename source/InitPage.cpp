#include <cstdlib>
#include <iostream>
#include <string>

#include "Database.h"
#include "DetailPage.h"
#include "GetCh.h"
#include "InitPage.h"
#include "SearchPage.h"

using std::cout;


//공고 목록 출력 함수 - 커서 위치 입력받아서 색 변경 적용
void InitPage::ShowNotice(unsigned short pos)
{
    SQLite db;
    std::string sql;
    db.DataBaseOpen("DB_Hin.db");
    for(int i=0;i<lnumMax;i++)
    {
        if(pos==i+1) cout<<"\x1b[m● ";
        else cout<<"○ ";
        //간단 공고에 들어가는 내용: 공고제목, 회사명, 마감일,근무지,경력,학력
        sql="SELECT HTITLE AS '',CNAME AS '',HDATE AS '마감일',HSTATE AS '근무지',HCARR AS '경력',HEDU AS '학력' FROM HIRE_TB WHERE HNUM_PK="+std::to_string(lnum[i])+";";
        db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
        if(pos==i+1) cout<<"\x1b[30m";
    }
    db.DataBaseClose();
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
    //pos 범위 0에서 lnumMAX+1까지
    //0일때
    if(pos==0)
    {
        cout<<"●  로그아웃 \x1b[30m\n";
        ShowNotice(pos); 
        cout<<"○  검색 > \x1b[m\n";
    }
    //그 사이 일때
    else if(pos<lnumMax+1)
    {
        cout<<"\x1b[30m○  로그아웃 \n";
        ShowNotice(pos);
        cout<<"○  검색 > \x1b[m\n";
    }
    //lnumMax+1일때
    else if(pos==lnumMax+1)
    {
        cout<<"\x1b[30m○  로그아웃 \n";
        ShowNotice(pos);
        cout<<"\x1b[m●  검색 > \n";
    }
    cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
}
//초기 페이지 메인 프로세스
void InitPage::ProcessInit(void)
{
    srand(time(NULL));
    //일단 다른거 생각안하고 공고 랜덤으로 3~5개 출력되도록 --2~3개로 수정
    lnumMax = rand()%2+2; //목록 개수
    lnum.clear();
    unsigned short tmp;
    bool dup;
    for(int i=0;i<lnumMax;i++)
    {
        tmp=rand()%60+1;
        for(int j=0;j<i;j++) //중복 검사
        {   
            dup=lnum[j]==tmp;
            if(dup) //중복이면
            {
                tmp=rand()%60+1; j=-1;
                continue;
            }
        }
        lnum.push_back(tmp); //나중에 공고 개수 const로 뺄것
        //중복 지원해야함
    }
    while(true)
    {    
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
                    if(pos!=0) 
                    {
                        pos--;
                        system("clear");
                        ListforPos(pos);
                    }
                    break;
                case 66: //방향키 하
                    if(pos!=1+lnumMax) 
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
        if(pos==0) //로그아웃
        {
            cout<<"로그아웃을 진행합니다. \n";
            return;
        }
        else if(pos>0&&pos<lnumMax+1) //공고 상세 정보
        {
            //선택된 공고 번호 전달해야함
            DetailPage detail;
            detail.ProcessDetail(lnum[pos-1]);
        }
        else if(pos==lnumMax+1) //검색
        {
            SearchPage search;
            search.ProcessSearch();
            lnumMax = rand()%2+2; //목록 개수
            lnum.clear();
            unsigned short tmp;
            bool dup;
            for(int i=0;i<lnumMax;i++)
            {
                tmp=rand()%60+1;
                for(int j=0;j<i;j++) //중복 검사
                {   
                    dup=lnum[j]==tmp;
                    if(dup) //중복이면
                    {
                        tmp=rand()%60+1; j=-1;
                        continue;
                    }
                }
                lnum.push_back(tmp); //나중에 공고 개수 const로 뺄것
                //중복 지원해야함
            }
        }
    }
}
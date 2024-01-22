#include "CEOMode.h"
#include "Database.h"
#include "GetCh.h"



void CEOMode::ProgressCEOMode(void)
{
    SQLite db;
    std::string sqlTMP;
    db.DataBaseOpen("DB_Hin.db");
    system("clear");
    std::cout<<"\x1b[1;96m┌───────────────────────────────┐ \n"
          "│    |C||E||O|  |M||o||d||e|    │\n"
          "└───────────────────────────────┘ \x1b[m\n"
          "[ 이전화면으로 돌아가려면 x를 입력하세요 ]\n";
    while(true)
    {
        std::cout<<"아이디 > ";
        std::cin>>id;
        if(!id.compare("x")||!id.compare("X"))
        {
            std::cin.get();
            return;
        }
        std::cout<<"비밀번호 > ";
        std::cin>>pw;
        if(!pw.compare("x")||!pw.compare("X"))
        {
            std::cin.get();
            return;
        }
        sqlTMP="SELECT CPW FROM COMPANY_TB WHERE CID='"+id+"';";
        if(!db.ProcessCMP(sqlTMP.c_str(),pw))
        {
            std::cout<<"로그인에 성공하셨습니다! \n";
            break;
        }
        else
        {
            std::cout<<"존재하지 않는 아이디 혹은 PIN번호 입니다.\n";
        }
    }
    cnum=db.ProcessCMP_Return(("SELECT CNUM_PK,CID FROM COMPANY_TB WHERE CID='"+id+"';").c_str(),id)[0];
    db.DataBaseClose();
    //로그인 완료 되면...본인 회사의 공고 리스트와 등록되어있는 기업정보를 띄우고 수정할 정보 선택받기
    // db.DataBaseOpen("DB_Hin.db");
    // db.DataBaseClose();
    std::cin.get();
    ModifyInfo();
}
//정보 수정
void CEOMode::ModifyInfo(void)
{
    while(true)
    {
        unsigned short pos=0;
        bool quit=false;
        int input;

        ListforPos(pos);
        while(!quit)
        {
            input=getch();
            switch (input)
            {
            case 65:
                if(pos!=0)
                {
                    pos--;
                    ListforPos(pos);
                }
                break;
            case 66:
                if(pos!=hnumL.size()+1)
                {
                    pos++;
                    ListforPos(pos);
                }
                break;
            case 10:
                quit=true;
                break;
            default:
                break;
            }
        }
        if(pos<hnumL.size())
        {
            //공고 수정
            hnum=hnumL[pos];
            ModifyHireNotice();
            //검색 테이블에 적용하는것도 추가 가능하면 추가하기
            UpdateSearchTB();
        }
        else if(pos==hnumL.size())
        {
            //기업 정보 수정
            ModifyCompanyInfo();
        }
        else break;
    }
}
//커서에 따른 목록
void CEOMode::ListforPos(unsigned short pos)
{
    SQLite db;
    std::string sqlTMP;
    db.DataBaseOpen("DB_Hin.db");
    hnumL=db.ProcessCMP_Return(("SELECT HNUM_PK,CNUM FROM HIRE_TB WHERE CNUM="+std::to_string(cnum)+";").c_str(),std::to_string(cnum));
    system("clear");
    std::cout<<"\x1b[1;96m┌───────────────────────────────┐ \n"
          "│    |C||E||O|  |M||o||d||e|    │\n"
          "└───────────────────────────────┘ \x1b[m\n";
    std::cout<<"공고 목록 > \n";

    for(int i=0;i<hnumL.size();i++)
    {
        if(pos==i) std::cout<<"\x1b[m● ";
        else std::cout<<"○ ";
        sqlTMP="SELECT HTITLE AS '',CNAME AS '',HDATE AS '마감일',HSTATE AS '근무지',HCARR AS '경력',HEDU AS '학력' FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnumL[i])+";";
        db.DataBaseQuery(sqlTMP.c_str(),db.CallbackSelect);
        if(pos==i+1) std::cout<<"\x1b[30m";
    }
    if(pos==hnumL.size()) std::cout<<"\x1b[m●  기업 정보 수정 > \x1b[m\n";
    else std::cout<<"\x1b[30m○  기업 정보 수정 > \x1b[m\n";
    if(pos==hnumL.size()+1) std::cout<<"\x1b[m●  로그아웃 > \x1b[m\n";
    else std::cout<<"\x1b[30m○  로그아웃 > \x1b[m\n";

    db.DataBaseClose();
    std::cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
}
//공고 수정
void CEOMode::ModifyHireNotice(void)
{
    while(true)
    {
        unsigned short pos=0;
        bool quit=false;
        int input;

        NoticeforPos(pos);
        while(!quit)
        {
            input=getch();
            switch (input)
            {
            case 65:
                if(pos!=0)
                {
                    pos--;
                    NoticeforPos(pos);
                }
                break;
            case 66:
                if(pos!=16)
                {
                    pos++;
                    NoticeforPos(pos);
                }
                break;
            case 10:
                quit=true;
                break;
            case 'x':
            case 'X':
                return;
            default:
                break;
            }
        }
        std::string content;
        std::cout<<"내용을 입력하세요 (엔터 누르기 전까지의 내용이 적용됩니다.) > \n";
        std::getline(std::cin,content);
        SQLite db;
        db.DataBaseOpen("DB_Hin.db");
        std::string sql="UPDATE HIRE_TB SET "+HcolName[pos][0]+"='"+content+"' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
        db.DataBaseClose();
    }
}
//커서에 따른 공고
void CEOMode::NoticeforPos(unsigned short pos)
{
    system("clear");
    SQLite db;
    std::string sql;
    db.DataBaseOpen("DB_Hin.db");
    sql="SELECT ";
    for(int i=0;i<17;i++)
    {
        sql.append(HcolName[i][0]); //HTITLE
        if(pos==i) sql.append(" AS '●  "); 
        else sql.append(" AS '○  "); //HTITLE AS '○ /
        sql.append(HcolName[i][1]); //HTITLE AS '○ 제목/
        if(i<16) sql.append("',");
    }
    sql.append("' FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";");
    db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
    std::cout<<"바꿀 항목을 선택하세요 (이전으로 X)>\n";
    std::cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
    db.DataBaseClose();
}
//기업 정보 수정
void CEOMode::ModifyCompanyInfo(void)
{
    while(true)
    {
        unsigned short pos=0;
        bool quit=false;
        int input;

        InfoforPos(pos);
        while(!quit)
        {
            input=getch();
            switch (input)
            {
            case 65:
                if(pos!=0)
                {
                    pos--;
                    InfoforPos(pos);
                }
                break;
            case 66:
                if(pos!=8)
                {
                    pos++;
                    InfoforPos(pos);
                }
                break;
            case 10:
                quit=true;
                break;
            case 'x':
            case 'X':
                return;
            default:
                break;
            }
        }
        std::string content;
        std::cout<<"내용을 입력하세요 (엔터 누르기 전까지의 내용이 적용됩니다.) > \n";
        std::getline(std::cin,content);
        SQLite db;
        db.DataBaseOpen("DB_Hin.db");
        std::string sql="UPDATE COMPANY_TB SET "+CcolName[pos][0]+"='"+content+"' WHERE CNUM_PK="+std::to_string(cnum)+";";
        db.DataBaseQuery(sql.c_str());
        db.DataBaseClose();
    }
}
//커서에 따른 기업 정보
void CEOMode::InfoforPos(unsigned short pos)
{
    system("clear");
    SQLite db;
    std::string sql;
    db.DataBaseOpen("DB_Hin.db");
    sql="SELECT ";
    for(int i=0;i<9;i++)
    {
        sql.append(CcolName[i][0]); //HTITLE
        if(pos==i) sql.append(" AS '●  "); 
        else sql.append(" AS '○  "); //HTITLE AS '○ /
        sql.append(CcolName[i][1]); //HTITLE AS '○ 제목/
        if(i<8) sql.append("',");
    }
    sql.append("' FROM COMPANY_TB WHERE CNUM_PK="+std::to_string(cnum)+";");
    db.DataBaseQuery(sql.c_str(),db.CallbackSelect);
    std::cout<<"바꿀 항목을 선택하세요 (이전으로 X)>\n";
    std::cout<<"(이동: 방향키 상/ 하) (선택: 엔터) \n";
    db.DataBaseClose();
}
//검색 테이블 갱신 -- 노가다 가자아아ㅏ 머리 쓸 힘이 없어
void CEOMode::UpdateSearchTB(void)
{
    SQLite db;
    std::string sql;
    db.DataBaseOpen("DB_Hin.db");
    sql="SELECT HNUM_PK,HCARR FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";
    if(db.ProcessCMP(sql.c_str(),"무관",0))
    {
        sql="UPDATE SEARCH_TB SET SNULLC='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    sql="SELECT HNUM_PK,HCARR FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";
    if(db.ProcessCMP(sql.c_str(),"경력",0))
    {
        sql="UPDATE SEARCH_TB SET SOLDC='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    sql="SELECT HNUM_PK,HCARR FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";
    if(db.ProcessCMP(sql.c_str(),"신입",0))
    {
        sql="UPDATE SEARCH_TB SET SNEWC='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }

    sql="SELECT HNUM_PK,HEDU FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";
    if(db.ProcessCMP(sql.c_str(),"무관",0))
    {
        sql="UPDATE SEARCH_TB SET SEDU=0 WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    else if(db.ProcessCMP(sql.c_str(),"고교졸업",0))
    {
        sql="UPDATE SEARCH_TB SET SEDU=1 WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    else if(db.ProcessCMP(sql.c_str(),"대졸",0))
    {
        sql="UPDATE SEARCH_TB SET SEDU=2 WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
        sql="SELECT HNUM_PK,HEDU FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";
    }
    else if(db.ProcessCMP(sql.c_str(),"대졸(4",0))
    {
        sql="UPDATE SEARCH_TB SET SEDU=3 WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }

    std::string sqlR="SELECT * FROM HIRE_TB WHERE HNUM_PK="+std::to_string(hnum)+";";
    if(db.ProcessCMP(sqlR.c_str(),"서울",0))
    {
        sql="UPDATE SEARCH_TB SET SEOUL='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"경기",0))
    {
        sql="UPDATE SEARCH_TB SET GYEONGGI='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"대전",0))
    {
        sql="UPDATE SEARCH_TB SET DAEJEON='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"인천",0))
    {
        sql="UPDATE SEARCH_TB SET INCHEON='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"광주",0))
    {
        sql="UPDATE SEARCH_TB SET GWANGJU='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"C",0))
    {
        sql="UPDATE SEARCH_TB SET C='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"C++",0))
    {
        sql="UPDATE SEARCH_TB SET CPP='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"C#",0))
    {
        sql="UPDATE SEARCH_TB SET CSP='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"Python",0))
    {
        sql="UPDATE SEARCH_TB SET PYTHON='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }
    if(db.ProcessCMP(sqlR.c_str(),"JAVA",0))
    {
        sql="UPDATE SEARCH_TB SET JAVA='o' WHERE HNUM_PK="+std::to_string(hnum)+";";
        db.DataBaseQuery(sql.c_str());
    }

    
    db.DataBaseClose();
}
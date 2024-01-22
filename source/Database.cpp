#include "Database.h"

//검색된 내용과 비교 -- 일치하는 행의 PK 번호 반환 (받을 컬럼값 이름을 SELECT 첫번째 순서로 호출)
std::vector<int> SQLite::ProcessCMP_Return(const char* sql,std::string keyword)
{
    std::vector<int> pkList;
    sqlite3_stmt* res;
    std::string tmp;
    int pkNum;
    if(sqlite3_prepare_v2(db,sql,-1,&res,0)!=SQLITE_OK) //sql 쿼리 컴파일
    {
        std::cout<<"Failed to fetch data: "<<sqlite3_errmsg(db)<<std::endl;
        DataBaseClose();
        exit(1);
    }
    else //정상적으로 쿼리 실행 진행
    {
        while(sqlite3_step(res)==SQLITE_ROW)
        {
            pkNum=sqlite3_column_int(res,0);
            for(int i=1;i<sqlite3_column_count(res);i++)
            {   
                tmp.append((char*)sqlite3_column_text(res,i));
                // std::cout<<tmp<<std::endl;
                // if(tmp.find(keyword)!=std::string::npos)
                // {
                //     pkList.push_back(pkNum);
                //     // std::cout<<pkNum<<" "<<keyword<<" "<<tmp<<std::endl;
                //     // break; //--너가 문제였어..ㅠㅠ///???
                // }
                // if(keyword.find((const char*)sqlite3_column_text(res,i))!=std::string::npos) //일치하는것이 하나라도 있으면
                // {
                //     pkList.push_back(pkNum);
                //     break;
                // }
            }
            if(tmp.find(keyword)!=std::string::npos)
            {
                pkList.push_back(pkNum);
            }
            tmp.clear();
        }
        sqlite3_finalize(res); //컴파일된 쿼리 정리
    }
    return pkList;
}
// 검색된 내용과 비교 -- 완전 일치
bool SQLite::ProcessCMP(const char* sql,std::string input)
{
    bool result=true;
    sqlite3_stmt* res;
    if(sqlite3_prepare_v2(db,sql,-1,&res,0)!=SQLITE_OK) //sql 쿼리 컴파일
    {
        std::cout<<"Failed to fetch data: "<<sqlite3_errmsg(db)<<std::endl;
        DataBaseClose();
        exit(1);
    }
    else //정상적으로 쿼리 실행 진행
    {
        while(sqlite3_step(res)==SQLITE_ROW)
        {
            // std::cout<<sqlite3_column_text(res,0)<<std::endl;
            if(!input.compare((const char*)sqlite3_column_text(res,0))) //일치하는것이 있으면
            {
                result = false;
                break;
            }
            // std::cout<<strcmp((const char*)sqlite3_column_text(res,0),input.c_str())<<std::endl;
        }
        sqlite3_finalize(res); //컴파일된 쿼리 정리
    }
    return result;
}
// 검색된 내용과 비교 -- 부분 일치 input이 어디라도 있다면 true 반환
bool SQLite::ProcessCMP(const char* sql,std::string input,void* NotUsed)
{
    bool result=false;
    sqlite3_stmt* res;
    std::string tmp;
    if(sqlite3_prepare_v2(db,sql,-1,&res,0)!=SQLITE_OK) //sql 쿼리 컴파일
    {
        std::cout<<"Failed to fetch data: "<<sqlite3_errmsg(db)<<std::endl;
        DataBaseClose();
        exit(1);
    }
    else //정상적으로 쿼리 실행 진행
    {
        while(sqlite3_step(res)==SQLITE_ROW)
        {
            // std::cout<<sqlite3_column_text(res,0)<<std::endl;
            // if(!input.compare((const char*)sqlite3_column_text(res,0))) //일치하는것이 있으면
            for(int i=1;i<sqlite3_column_count(res);i++)
            {   
                tmp.append((char*)sqlite3_column_text(res,i));
            }
            if(tmp.find(input)!=std::string::npos)
            {
                result = true;
                break;
            }
            // std::cout<<strcmp((const char*)sqlite3_column_text(res,0),input.c_str())<<std::endl;
        }
        sqlite3_finalize(res); //컴파일된 쿼리 정리
    }
    return result;
}
//데이터베이스 파일 연결
void SQLite::DataBaseOpen(const char* fname)
{
    check = sqlite3_open(fname,&db);
    if(check!=SQLITE_OK)
    {
        std::cout<<"Cannot open database: "<<sqlite3_errmsg(db)<<std::endl;
        DataBaseClose();
        exit(1);
    }
    else
    {
        // std::cout<<"Success opening database \n"; //추적용 메시지
    } 
}
//데이터베이스 파일 연결 종료
void SQLite::DataBaseClose(void)
{
    // std::cout<<"Close database\n";
    sqlite3_close(db);
}
//데이터베이스 쿼리 실행
void SQLite::DataBaseQuery(const char* sql,int(*callback)(void*,int,char**,char**))
{
    check = sqlite3_exec(db,sql,callback,0,&errMSG);
    if(check!=SQLITE_OK)
    {
        std::cout<<"SQL error: "<<errMSG<<std::endl;
        sqlite3_free(errMSG);
        DataBaseClose();
        exit(1);
    }
    else
    {
        // std::cout<<"SQL committed \n";
    }
}
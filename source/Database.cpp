#include "Database.h"

// 검색된 내용과 비교
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
#include "Database.h"

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
        std::cout<<"Success opening database \n"; //추적용 메시지
    } 
}
//데이터베이스 파일 연결 종료
void SQLite::DataBaseClose(void)
{
    std::cout<<"Close database\n";
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
            std::cout<<"SQL committed \n";
        }
}
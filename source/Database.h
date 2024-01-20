#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <sqlite3.h>
#include <vector>

class SQLite
{
private:
    sqlite3* db; //데이터베이스 핸들(디스크립터)
    int check; //에러 체크 소자
    char* errMSG; //에러 메시지 주소값 저장
    // static std::vector<std::string> cmp; //비교 문자열
public:
    //SELECT구문 실행시 사용하는 콜백함수
    static int CallbackSelect(void* NotUsed,int argc,char** argv,char**azColName)
    {
        NotUsed = 0;
        for(int i=0;i<argc;i++)
        {
            //컬럼명, 값을 읽어온다 --읽을 값이 없을때까지 콜백 호출
            std::cout<<azColName[i]<<" "<<(argv[i]?argv[i]:0)<<std::endl;
        }
        std::cout<<std::endl;
        return 0;
    }
    //데이터베이스 파일 연결
    void DataBaseOpen(const char*);
    //데이터베이스 파일 연결 종료
    void DataBaseClose(void);
    //데이터베이스 쿼리 실행
    void DataBaseQuery(const char* sql,int(*callback)(void*,int,char**,char**)=0);
    //검색된 내용과 비교 -- 일치하면 0
    bool ProcessCMP(const char*,std::string);
    //검색된 내용과 비교 -- 일치하는 행의 PK 번호 반환
    std::vector<int> ProcessCMP_Return(const char*,std::string);
};
#endif
#ifndef LOGINPAGE_H_
#define LOGINPAGE_H_

class LoginPage
{
private:
    std::string id;     //아이디
    std::string pin;    //PIN번호
    std::string email;  //이메일
    std::string phone;  //휴대폰번호
public:
    //로그인 화면
    bool LoginScreen(void);
    //회원가입 화면
    void JoinScreen(void);
    //커서 위치에 따른 목록 출력
    void ListforPos(unsigned short);
    //로그인 페이지 메인 프로세스
    bool ProcessLogin(void);
};
#endif
#ifndef GAMEBOARDEXCEPTION_H
#define GAMEBOARDEXCEPTION_H

/*

GameBoardException was a basic exception to denote an instance of invalid user input when trying to initialize chutes or ladders, 
most of its purpose was for it to be handled, caught, and differentitated from other exceptions in the main program. So as you can see there is 
not much in terms of code, in reality you only need the header file to successfully build and use this class.

Just in the constructor do something kind of like this

public:
    GameBoardException(){
    };

*/
class GameBoardException
{
    public:
        GameBoardException();
    protected:
    private:
};

#endif // GAMEBOARDEXCEPTION_H

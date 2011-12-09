#ifndef CHESSEXCEPTION_H
#define CHESSEXCEPTION_H


struct ChessException{
    enum _type{
        /***ChessPiece Exceptions***/
        NullPiece,
        NullPath
    } PieceEnum;

    _type       type;
    std::string what;
    std::string why;
};

#endif // CHESSEXCEPTION_H

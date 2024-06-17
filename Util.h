// DNI 78008606N BIBILEISHVILI MAMALADZE, NIKOLOZ

#ifndef _UTIL_H_
#define _UTIL_H_


const int KMAXNAME = 20;

enum Exception {
  EXCEPTION_INFL_NOT_FOUND,
  EXCEPTION_WRONG_COMMISSION,
  EXCEPTION_UNKNOWN_SN,
  EXCEPTION_FILE
};



enum Error{
  ERR_DUPLICATED,
  ERR_NOT_FOUND,
  ERR_WRONG_SOCIALNETWORK,
  ERR_WRONG_COMMISSION,
  ERR_UNKNOWN_SN,
  ERR_FILE
};



class Util{
  public:
    // prints an error message
    static void error(Error e);

    // prints exception type (debug)
    static void debug(Exception e);
    
};

#endif

#ifndef ESSENTIALQTSO_MACROS_HPP
#define ESSENTIALQTSO_MACROS_HPP

#define QSTRINGBOOL(BOOL) QString(BOOL ? "true" : "false")
#define APPENDSTRPTR(STRPTR, MSG) if (STRPTR not_eq nullptr) \
{ \
    STRPTR->append(MSG); \
}
#define APPENDTEXTPTR(TEXTCOMPILATIONPTR, MSG) if (TEXTCOMPILATIONPTR not_eq nullptr) \
{ \
    TEXTCOMPILATIONPTR->append_f(MSG); \
}
#define IFERRORSTRPTRNOTEMPTYBREAK(STRPTR) if (not STRPTR->isEmpty()) \
{ \
    break; \
}
#define IFERRORTEXTPTRNOTEMPTYBREAK(TEXTPTR) if (not TEXTPTR->empty_f()) \
{ \
    break; \
}

#define DEBUGSOURCE QString(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) + " (" + QString(__func__) + ") "

#define DEBUGDATETIME QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ")

#define DEBUGDATETIMEANDSOURCE DEBUGDATETIME + DEBUGSOURCE

#define DEBUGFULL DEBUGDATETIMEANDSOURCE << "line: " << __LINE__ << " "

#define DEBUGFULLEND std::cout << DEBUGFULL << "END\n";

#endif // ESSENTIALQTSO_MACROS_HPP

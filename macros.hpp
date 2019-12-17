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

#endif // ESSENTIALQTSO_MACROS_HPP

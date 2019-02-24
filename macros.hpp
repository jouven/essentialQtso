#ifndef ESSENTIALQTSO_MACROS_HPP
#define ESSENTIALQTSO_MACROS_HPP

#define QSTRINGBOOL(BOOL) QString(BOOL ? "true" : "false")
#define APPENDSTRPTR(STRPTR, MSG) if (STRPTR not_eq nullptr) \
{ \
    STRPTR->append(MSG); \
}
#define IFERRORSTRPTRNOTEMPTYBREAK(STRPTR) if (not STRPTR->isEmpty()) \
{ \
    break; \
}

#endif // ESSENTIALQTSO_MACROS_HPP

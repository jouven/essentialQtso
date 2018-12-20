//because windows sucks...

#ifndef ESSENTIALQTSO_CROSSPLATFORMMACROS_HPP
#define ESSENTIALQTSO_CROSSPLATFORMMACROS_HPP

#include <QtCore/QtGlobal>

//remember to define this variable in the .pro file
#if defined(ESSENTIALQTSO_LIBRARY)
#  define EXPIMP_ESSENTIALQTSO Q_DECL_EXPORT
#else
#  define EXPIMP_ESSENTIALQTSO Q_DECL_IMPORT
#endif

#endif // ESSENTIALQTSO_CROSSPLATFORMMACROS_HPP

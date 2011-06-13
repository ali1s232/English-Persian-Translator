#pragma once
#ifndef TLMACROS_H_
#define TLMACROS_H_

#define tlPROPERTY(X,Y) private:X Y;public:inline void set##Y(X p##Y){Y=p##Y;}inline X get##Y()const {return Y;}
#define tlPROPERTY_NODEF(X,Y) private:X Y;public:inline void set##Y(X p##Y); inline X get##Y()const;
#endif

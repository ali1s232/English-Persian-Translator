#pragma once
#ifndef ttMACROS_H_
#define ttMACROS_H_

#define ttPROPERTY(X,Y) private:X m##Y;public:inline void set##Y(X p##Y){m##Y=p##Y;}inline X get##Y()const {return m##Y;}
#define ttPROPERTY_NODEF(X,Y) private:X m##Y;public: void set##Y(X p##Y); X get##Y()const;
#endif

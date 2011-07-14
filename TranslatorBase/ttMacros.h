#pragma once
#ifndef ttMACROS_H_
#define ttMACROS_H_

#define ttPROPERTY_PROTECTED(X,Y) protected:X m##Y;public:inline void set##Y(X p##Y){m##Y=p##Y;}inline X get##Y()const {return m##Y;}
#define ttPROPERTY_NODEF_PROTECTED(X,Y) protected:X m##Y;public: virtual void set##Y(X p##Y);virtual X get##Y()const;
#define ttPROPERTY(X,Y) private:X m##Y;public:inline void set##Y(X p##Y){m##Y=p##Y;}inline X get##Y()const {return m##Y;}
#define ttPROPERTY_NODEF(X,Y) private:X m##Y;public: virtual void set##Y(X p##Y);virtual X get##Y()const;

#define ttDeclareRTTI private: static const ttRTTI mRTTI;public: virtual const ttRTTI& getTypeInfo() const;static const ttRTTI& getStaticTypeInfo();
#define ttImplementRTTI(X) const ttRTTI X::mRTTI(new X,#X);const ttRTTI& X::getTypeInfo() const{return mRTTI;}const ttRTTI& X::getStaticTypeInfo(){return mRTTI;}

#endif

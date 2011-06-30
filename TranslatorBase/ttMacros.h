#pragma once
#ifndef ttMACROS_H_
#define ttMACROS_H_

#define ttPROPERTY_PROTECTED(X,Y) protected:X m##Y;public:inline void set##Y(X p##Y){m##Y=p##Y;}inline X get##Y()const {return m##Y;}
#define ttPROPERTY_NODEF_PROTECTED(X,Y) protected:X m##Y;public: virtual void set##Y(X p##Y);virtual X get##Y()const;
#define ttPROPERTY(X,Y) private:X m##Y;public:inline void set##Y(X p##Y){m##Y=p##Y;}inline X get##Y()const {return m##Y;}
#define ttPROPERTY_NODEF(X,Y) private:X m##Y;public: virtual void set##Y(X p##Y);virtual X get##Y()const;

#define ttDeclareRTTI public: virtual const char* getTypeInfo() const{return "ttObject";}
#define ttImplementRTTI(X) struct X##Intoducer{X##Intoducer(){TranslationTools::ttObjectPool::getInstance()->registerNewSample(new X);}}X##IntroducerVariable;

#endif
